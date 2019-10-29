#!/usr/bin/env python
# global imports
import os, sys, subprocess, tarfile, json
import filecmp
from pprint import pprint
from shutil import copyfile
import argparse

file_dir = os.path.dirname(os.path.realpath(__file__))  # xxx/src/
project_root_path = os.path.dirname(file_dir)  # xxx/helper_platform_detect

base_root = os.path.dirname(project_root_path)  # location where all projects reside
sys.path.append(base_root)

print sys.path

import shutil
import uuid
import platform as lPl  # pip
from Selector_OS_Platform.platform_detect import *
from flasher_autorun.src.flasher_autorun_main import *
from simpelTools.src.walking_merge import *
from SW_Test_flasher.src.test_dyn_cmd_line import *




from inspect import getframeinfo, currentframe  # line numbers etc

'''
Script preparing and running the romloadertest for windows and linux
if executet with argument install, a os-dependend installation is performed
if executed with a port (the conectionstring used by flasher for connecting to devices)
else returns a errorvalue.

For windows a dpinst installtion is performed
'''

# write file as intependend as possible. File location should not matter for execution.

version = "0.0.5"
print "program Version %s" % version
# --------------------------------------
# Changelog
# 0.0.5 Adding flasher 1.5.5
#       logging
#       batch
#       much more
# 0.0.4 Adding flasher 1.5.4
#       Added comments
# 0.0.3 Runthrou on remote linux manually (without jenkins)
#       runCommand, using default std.out, because seeing progress, adventage: no trouble with bufferoverflow with huge output
# 0.0.2 Now first successfull runthrough! (local)
# 0.0.1 Stripped from all old things
#       added verbosety functiiones
# 0.0.0 Taken sceleton from  HW_Config_v0_1_2_pirateV10.tar.gz/hwconfig/verification2/piratetest_hwconfig.py 97d6cd8a (Armin Ballmert 2018-08-27 17:20:48 +0200 675)


'''
# Content of zip-archive
romloader_test_0.0.037
-- [   34021761]  bootloader_windows_driver-2.4.6.zip
-- [   30050279]  flasher_cli-1.5.4.tar.gz
-- [       4096]  netxbins
----2000]  montest_netx10.bin
----1516]  montest_netx4000.bin
----2000]  montest_netx500.bin
----2016]  montest_netx50.bin
----2000]  montest_netx56.bin
----1448]  montest_netx90.bin
----1448]  montest_netx90_mpw.bin
-- [      14411]  module_XXX/src/pirate.py
-- [       7614]  module_XXX/src/platform_detect.py
-- [      21884]  test_romloader.lua

bootloader driver is for windows
flasher.tar.gz contains all zip-Archives, which contain the flasher data
*.bin are for the flasher_cli-N.N.N/netX of the extracted flasher version.
pirate.py for installing and running the tests
 - "install"
 - "port"
platform_detect.py is a helper retrieving infos about the os and plattform
test_romloader.lua will be placed in flashers root director. Test is executed with -p port
'''

# extract flasher
# copy binaries
# copy romloader.lua


# Merging
# file from (git clone --recursive  https://github.com/muhkuh-sys/org.muhkuh.lua-romloader.git)
# cp /lua_romloader/org.muhkuh.lua-romloader/plugins/romloader/_test/test_romloader.lua /flasher_cli-1.5.0/ # global for every version
#

# Global tool parameters
verbose = 2
printprefix = "pirate"

# insert here the relative position from file location to base of archive
# if the file is located in base/tam/MyFile
# /home/usr/HW_Config_v0_1_2/hwconfig/verification2 and the basefolder is HW_Config_v0_1_2
#  you should insert os.path.join("..","..") to go back to hwconfig to HW_Config_v0_1_2.


# Get plattform specific
Name, vLinux, bin = lPl.dist()
cOS, cPL, cThePlatform, cTheMachine = GetPlatformMatrixEntry()


# Global constants
gPathScriptFile = os.getcwd()
gPathScriptFile_precise = os.path.dirname(os.path.abspath(__file__))
gPath_flasher_root = os.path.dirname(gPathScriptFile_precise)  # in SW_Test_flasher
gPath_base_root = os.path.dirname(gPath_flasher_root)  # WB_Root

if (gPathScriptFile != gPathScriptFile_precise):
  print "[pirate][warning]: cwd is not same as scriptlocation, building rel path from scriptfile, assume WB-Structure"
  print "[pirate] cwd: %s" % (gPathScriptFile)
print "[pirate] loc: %s" % (gPathScriptFile_precise)
print("[pirate] gPath_flasher_root:", gPath_flasher_root)
print("[pirate] (WorkBench)gPath_base_root:", gPath_base_root)



json_file_name = "version.json"
json_file = os.path.join(gPath_base_root,json_file_name)
l.info('retrieving version infos from file: %s'%json_file)
try:
  if os.path.isfile(json_file):
    l.info('Found config file at: %s'%json_file)
  else:
    l.error('Expected configfile at: %s' % json_file)
    exit(91)
  json_data=open(json_file)
  JsonVersionInfo = json.load(json_data)
  pprint(JsonVersionInfo)
  json_data.close()
except Exception as e:
  l.error('Tried to retrieve version info from %s: %s' % (json_file_name, e))

# versions
try:
  vFlasher = JsonVersionInfo['VERSION_FLASHER']
  vDriverRomloaderWindows = JsonVersionInfo['VERSION_DRIVER_WIN_BOOTLOADER']
  vRomloader = JsonVersionInfo['VERSION_ROMLOADER_SINE']
  installApplyRomloaderPatch = JsonVersionInfo['APPLY_ROMLOADER_PATCH']  # old flasher, new romloader, apply changes
  installApplyRomloaderTest = JsonVersionInfo['APPLY_ROMLOADER_TEST']    # existing setup, add test for romloader
except Exception as e:
  l.error('Parsed %s: %s'%(json_file_name, e))

try:
  name_romloader_tar_source = JsonVersionInfo['NAME_TMP_FINAL_ROMLOADER_PLUGIN_TAR_GZ']
except Exception as e:
  l.error('Parsed %s: %s'%(json_file_name, e))



# logfiles
name_logfile_folder = 'logfiles'
gPath_logfile_folder = os.path.join(gPath_base_root,name_logfile_folder)
logfiles_subfolder_tmporary = 'logs_last_run'   # last run logs
logfiles_zipped = 'logs_final_zip'

path_abs_logfiles_temporary = os.path.join(gPath_logfile_folder, logfiles_subfolder_tmporary)
path_abs_logfiles_zipped = os.path.join(gPath_logfile_folder, logfiles_zipped)


# flasher
nLuaLin = "lua5.1.sh"
nLuaWin = "lua5.1.exe"
pathRel_flasher = 'flasher_cli-%s' % vFlasher  # path for extracting the flasher to (will be created by archive file)
nTarFlasher = "flasher_cli-%s.tar.gz" % (vFlasher)
gPathAbs_TarFlasher = os.path.join(gPath_base_root, nTarFlasher)
gpathAbs_flasher = os.path.join(gPath_base_root, pathRel_flasher)
nLuaFileRomloaderTest = "test_romloader.lua"   # placed beside lua.exe
gPath_LuafileRomloaderSource = os.path.join(gPath_base_root, nLuaFileRomloaderTest)
gPath_LuaFileRomloaderTarget = gpathAbs_flasher
name_flasher_plugin_folder = 'lua_plugins'
gPathAbs_flasher_luaplugin = os.path.join(gpathAbs_flasher,name_flasher_plugin_folder)
## subfolder
grelrelPath_binNetX = 'netx'  # in lua folder
grelrelPath_luaplugins = 'lua_plugins'


# netxbins
pathReg_binsNetX = 'netxbins' # from zip
gPath_binsNetxSource = os.path.join(gPath_base_root, pathReg_binsNetX)
wildcardMontestBins = 'montest_*.bin' # to copy all file at once
gPath_binsNetxSourceWild = os.path.join(gPath_binsNetxSource, wildcardMontestBins)
gPath_binsNetxTarget = os.path.join(gpathAbs_flasher, grelrelPath_binNetX)

# dpinst
grelrelPath_Dpinst = 'driver'
Name_Romloader_driver_zip = 'bootloader_windows_driver-%s.zip'%vDriverRomloaderWindows
gPath_dpinst_zip = os.path.join(gPath_base_root,Name_Romloader_driver_zip)
gPath_dpinst = os.path.join(gPath_base_root, grelrelPath_Dpinst)

# flasher config files
gPath_flasher_test_config = os.path.join(gPath_base_root)

# Romloaderplugin
#name_romloader_tar_source='romloader-%s_altered.tar.gz'%vRomloader

gPath_romloader_tar_source=os.path.join(gPath_base_root,name_romloader_tar_source)


# Argparse




# force 32bit




def checkFileExisting(arrFilesToCheck):
  success = 1
  for file in arrFilesToCheck:
    if os.path.isfile(file):
      print "[pirate] OK: %s" % (file)
    else:
      success = 0
      print "[pirate] MISSING: %s" % (file)
  return success


def GetLinenumber():
  frameinfo = getframeinfo(currentframe())
  print frameinfo.filename, frameinfo.lineno


# creating folder (non recursive),
# but skipping if existing
def mkdirSkipExistence(strFolder):
  success = 1
  try:
    os.mkdir(strFolder)
  except OSError as e:
    if e.errno == 17:
      pass
    else:
      print "[pirate]: Error in creating folder for final extract binary."
      print str(e)
      success = 0
  return success


# brief wrapper for executing a command string.
# details printing stdout/stderr,
# param arg command to be executed
# param stage string embedded in print-message
def runCommand(arg, stage):
  success = 1
  print "[pirate] Run Command:\n%s" % (arg)
  # p = subprocess.Popen(arg, shell=True, stdout=subprocess.PIPE, stderr=subprocess.PIPE)
  p = subprocess.Popen(arg,
                       shell=True)  # not sure, if shell true is neceassary. necessary for 'cp', 'mv' etc. or so. but 'python mypython.py' will work.
  strStdout, strStderr = p.communicate()  # necessary for the wait status! Otherwise will return none!

  # get output
  if strStdout:
    print "[pirate]stdout:\n%s" % (strStdout)
  if strStderr:
    print "[pirate]stderr:\n%s" % (strStderr)
  RetVal = p.returncode

  if RetVal is None:
    success = 0
    print  '[pirate] fatal error: ' + stage
    print "Process is still running, no retrunvalue, use p.communicate()!"
  elif (RetVal is not 0):
    success = 0
    print  '[pirate] failed: %s with RetVal: %d' % (stage, RetVal)
  else:
    print  '[pirate] success: ' + stage

  return success


# brief 	Executes a binary from ist location
# details 	The current working directory (CWD) is switched to binary path
#			After execution, the CWD is switched back
# param arg	cmd arg to be executed
# param stage string to be used in errormessage
# return 1 if succcess
def runCommandFromSource(arg, stage, location=None):
  if location == None:
    location = arg
  print("incomming to location: <%s>" % location)
  backup_cwd = os.getcwd()
  location = os.path.dirname(location)
  print("change to location: <%s>" % location)
  os.chdir(location)
  print os.getcwd()
  success = runCommand(arg, stage)
  os.chdir(backup_cwd)
  return success


import zipfile


# extract has no return value
def extractZip(sourceZipFile, TargetFolder):
  zip_ref = zipfile.ZipFile(sourceZipFile, 'r')
  zip_ref.extractall(TargetFolder)
  zip_ref.close()
  return 0


# Extract given *.tar.gz to destination directory
# warning this function is temporarely changing the current working directory!
# source: http://code.activestate.com/recipes/442503-extracting-targz-files-in-windows/
# param tarGzFile Tararchive
# param destDir Dir where to extract the tar-file to
def extractTarGz(tarGzFile, destdir):
  dirBackup = os.getcwd()

  iErr = 0
  try:
    os.chdir(destdir)
    tar = tarfile.open(tarGzFile, 'r:gz')
    for item in tar:
      # print "[unzip]: %s" % (item)
      tar.extract(item)
    l.info('Unzipped all!')
  except IndexError, e:
    l.info("Error: %s\n Have you specified a file to untar?" % (e))
    iErr = 1
  except Exception, e:
    l.info("Error: %s" % (e))
    name = os.getcwd()
    l.info(name[:name.rfind('.')], '<filename>')
    iErr = 1
  os.chdir(dirBackup)
  return iErr


# waring only useable with linux
# warning destinationfolder must exist
def extractTarXzLinux(PathToArchive, PathToDestination):
  success = 1
  command_base_Extract_gx = 'tar fvxJ '
  command_extractOocd = command_base_Extract_gx + PathToArchive + " -C " + PathToDestination
  success = runCommand(command_extractOocd, "extract OOCDfile")
  if success is not 1:
    print "extracting failed\nof: %s\nto: %s failed" % (PathToArchive, PathToDestination)
  return success


# brief copies wildcard like the command shell
# param nameFileWildcard locationstring, producing list of files/folders
# param dest_dir Destination dir or file
def copyfileByWildcard(nameFileWildcard, dest_dir):
  import glob
  import shutil
  iErr = 0
  # (https://stackoverflow.com/questions/18371768/python-copy-files-by-wildcards)
  globExpression = r'%s' % nameFileWildcard
  for file in glob.glob(globExpression):
    l.info("copy file: <%s> to <%s>" % (file, dest_dir))
    try:
      shutil.copy(file, dest_dir)
    except Exception as e:
      l.info(e)
      iErr = 56
      break
  return iErr


def evaluate(iErr):
  # sys.stdout=stdout_save
  if (iErr == 0):
    print '==========================='
    print '= Arrrrr.... priate good! ='
    print '==========================='
  else:
    print '==========================='
    print '= Arrrr!!!   FAILED       ='
    print '==========================='


# brief Removes all folders with all subdirs in provided list
# param rootFolderToBeRemoved folder which will be removed including all subdirectories. !iter object
def removeFolderTree(rootFolderToBeRemoved):
  # Clear hboot_images, register_dumps, compare

  for folder in rootFolderToBeRemoved:
    try:
      shutil.rmtree(folder)
    except Exception as e:
      print "[rmtree exception]:"
      print e
    os.mkdir(folder)


def run_dpinst(pathToDpinst, cPL, cOS):
  # Put in here the commands depending on the architecture
  binaryMatrix = [[''] * 2 for x in range(2)]
  binaryMatrix[enWin][enx86] = os.path.join(pathToDpinst, "dpinst32.exe /q /s /f")
  binaryMatrix[enWin][enx64] = os.path.join(pathToDpinst, "dpinst64.exe /q /s /f")
  binaryMatrix[enLin][enx86] = 'Error: No dpinst for linux'
  binaryMatrix[enLin][enx64] = 'Error: No dpinst for linux'

  print("Command: %s" % (binaryMatrix[cOS][cPL]))
  print("[pirate] run: %s" % (binaryMatrix[cOS][cPL]))
  iRet = runCommand(binaryMatrix[cOS][cPL], "dpinst")
  if (iRet == 1):
    # Error Occured
    # any other ret-value is not a error!!!
    iErr = 63
  else:
    iErr = 0
  return iErr




def runInstallation(force32=False, InstallRomloaderPlugin=True, ApplyTestRomloader=True):
  '''
  expect to have the Flasher archive which contains the flasher for all OS in one single folder in the root of archive
  :param force32: forces the 32bit version of the flasher to be installed
  :return:
  '''
  iErr = 1
  for _ in (1,):
    nameFlasherArchive = ''

    # in case you want to run a 32bit installation on 64bit, which is possible (does not choos a other driver)
    if (force32):
      flasher_version_to_install = 'x86'
    else:
      flasher_version_to_install = cTheMachine

    if cOS is enLin:
      nameFlasherArchive = 'flasher_cli-%s-ubuntu%s_%s.tar.gz' % (vFlasher, vLinux, flasher_version_to_install)
    else:
      nameFlasherArchive = 'flasher_cli-%s-windows_%s.zip' % (vFlasher, flasher_version_to_install)

    l.debug("[pirate][debug]: base root %s" % gPath_base_root)

    l.info("[pirate][install][extract]: OS-Independend flasher archive <%s> to <%s>" % (gPathAbs_TarFlasher, gPath_base_root))
    iErr = extractTarGz(gPathAbs_TarFlasher,
                        gPath_base_root)  # flasherzip is already containing a subfolder with version name, so ectract into the main archive
    if iErr != 0:
      l.info("[pirate][install][extract]: Failed extrction code: %d"%iErr)
      break


    iErr = install_flasher_version_unpack(iErr, nameFlasherArchive)
    if iErr != 0:
      l.info("[pirate][install] retrunValue extract: %d" % iErr)
      break

    # copy binaries
    if ApplyTestRomloader:
      iErr = apply_test_romloader()
    if iErr != 0:
      l.info("[pirate][install][cp][failed]: code %d"%iErr)
      break

    # patch with romloader plugin
    ## this overwrites existing files in the flasher.
    if InstallRomloaderPlugin:
      iErr = install_romloader_plugin()

      if iErr != 0:
        l.error("[install][romloader_plugin]: While copy files")
        break

    # install dpinst
    if cOS == enWin:
      iErr = install_dpinst_romloader_driver()
      if iErr != 0:
        l.error("[install][dpinst]: Failed")
        break
  else:
    iErr = 0
    l.info("[install]: Successful")


  return iErr


def install_dpinst_romloader_driver():
  """
  Installation is only a extraction of the driver, not a installation,
  because automisation is not possible. throws errors and does not install!
  :return: 0 in case of success
  """
  l.info("[pirate][install][dpinst]: detected windows, installing driver")
  extractZip(gPath_dpinst_zip, gPath_base_root)
  l.info('[install][dpinst]: Install skipped, because dpinst is not able to be installed by commandline.')
  iErr = 0
  #iErr = run_dpinst(gPath_dpinst, cPL, cOS)
  if iErr != 1:
    l.info("[pirate][install][dpinst][error]: code %d" % iErr)
  return iErr


def apply_test_romloader():
  """
  Patch flasher with files necessary for the test_romloader.lua.
  :return: 0 in case of success
  """
  iErr = copyfileByWildcard(gPath_binsNetxSourceWild, gPath_binsNetxTarget)
  if iErr != 0:
    l.error("[pirate][install][error](%d): Faild to copy binary files! <%s><%s>" % (
    iErr, gPath_binsNetxSourceWild, gPath_binsNetxTarget))
  else:
    l.info("[pirate][install][cp]: test_romloader.lua %s -> %s"%(gPath_LuafileRomloaderSource,gPath_LuaFileRomloaderTarget))
    try:
      shutil.copy(gPath_LuafileRomloaderSource, gPath_LuaFileRomloaderTarget)
    except Exception as e:
      l.info("%s", e)
      l.info("copy of <%s>to<%s> " % (gPath_LuafileRomloaderSource, gPath_LuaFileRomloaderTarget))
      iErr = 64
  return iErr


def install_flasher_version_unpack(nameFlasherArchive, path_tmp_zip_os_flasher):
  # unpack correct version of the flasher
  l.info("[pirate][install][extract]: OS-Flasher")
  l.info("[pirate][install][extract]: TarFlasher: <%s> to <%s>" % (nameFlasherArchive, gPath_base_root))
  if cOS == enLin:
    iErr = extractTarGz(path_tmp_zip_os_flasher, gPath_base_root)
  else:
    iErr = extractZip(path_tmp_zip_os_flasher, gPath_base_root)
  return iErr


def install_romloader_plugin():
  """
  Patches a old flasher with new romloader files.
  This procedure can be necessary when a new romloader is out, but no new flasher release.
  Existing files will be overwritten, new files will be added, otheres remain untouched
  because it is causing some problems to extract xz with python, the archive must contain already extracted folders!
  The name of the Folder is
  :return: 0 in case of success
  """

  iErr = 1
  if cOS is enLin:
    name_folder_OS_romloader_plugin = 'folder_lua5.1-romloader-%s-ubuntu_%s_%s.tar.xz' % (vRomloader, vLinux, cTheMachine)
  else:
    name_folder_OS_romloader_plugin= 'folder_lua5.1-romloader-%s-windows_%s.tar.xz' % (vRomloader, cTheMachine)

  for _ in [1]:
    # extract to romloader_plugin
    name_romloader_plugin_folder = 'romloader_plugin'
    gPath_romloader_plugin_extract = os.path.join(gPath_base_root, name_romloader_plugin_folder)
    l.info("[install][romloader_plugin][prep]: remove & create & extract to: %s"%gPath_romloader_plugin_extract)
    iErr = shutil.rmtree(gPath_romloader_plugin_extract, ignore_errors=True)
    if iErr:
      l.error("[install][romloader_plugin][prep]: remove old folder")
      break
    iErr = os.mkdir(gPath_romloader_plugin_extract)
    if iErr:
      l.error("[install][romloader_plugin][prep]: Creating folder")
      break
    l.info("[install][romloader_plugin][extract]: from: %s"%gPath_romloader_tar_source)
    l.info("[install][romloader_plugin][extract]: to: %s"%gPath_romloader_plugin_extract)
    iErr = extractTarGz(gPath_romloader_tar_source, gPath_romloader_plugin_extract) # extract the full archive with content of all romloader archives for different OS
    if iErr:
      l.error("[install][romloader_plugin][extract]: error no %d"%iErr)
      break
    # copy all files from this folder and overwrite the following location

    pathAbs_tmp_folder_src_romloader_plugin = os.path.join(gPath_romloader_plugin_extract,
                                                           name_folder_OS_romloader_plugin)
    l.info("[install][romloader_plugin][copy]: from %s"%pathAbs_tmp_folder_src_romloader_plugin)
    l.info("[install][romloader_plugin][copy]: to %s"%gpathAbs_flasher)
    try:
      iErr = overwrite_merge_Tree(pathAbs_tmp_folder_src_romloader_plugin, gpathAbs_flasher)
    except IOError as ie:
      l.error("[install][romloader_plugin][copy]: %s"%(ie))
      iErr = 69
    if iErr:
      l.error("[install][romloader_plugin][copy]: during final copy")
      break
  else:
    l.info("[install][romloader_plugin]: Success!")
    iErr = 0

  return iErr

def generate_full_flasher_command(parameter_commandline):
  '''
  Generates the testcommand for the romloader test.
  Output is separated into flasher binary and into command line arguments.
  The split was necessary to use the advanced flasher functions.
  :return: tuple(path_bin_flasher, parameter_commandline), the binary and the command line arguments without -p.
  '''

  if cOS == enLin:
    name_lua_bin = nLuaLin
  else:
    name_lua_bin = nLuaWin

  path_bin_flasher = os.path.join(gpathAbs_flasher,name_lua_bin)

  return path_bin_flasher, parameter_commandline



def helper_check_binary_file(binary_fiel_from_test, binary_file_read_from_netx):
  int_ierr = 1
  l.info("compare binary files from netX with origiginal one")
  if os.path.isfile(binary_file_read_from_netx):
    # check size of files
    size_orig = os.path.getsize(binary_fiel_from_test)
    size_uploaded = os.path.getsize(binary_fiel_from_test)
    if (size_orig != size_uploaded):
      l.error("File Size does not match")
    else:
      compare_result = filecmp.cmp(binary_fiel_from_test, binary_file_read_from_netx)
      if not compare_result:
        l.error("Binary file content does not match")
      else:
        l.info("Binary files are the same")
        int_ierr = 0
  return int_ierr

def ptbt_flasher_v1(path_logfile="./"):
  '''
  Generates and runns command able to test the flasher.
  A full series of tests is executed, without abortiang after a failed test.
  If all tests succeed, 0 is returened else 1.
  :return: number of failed commands
  '''

  if not os.path.exists(path_logfile):
    os.makedirs(path_logfile)

  logfile_praefix = "flashtest"
  flasher_binary = generate_full_flasher_command("")[0]


  list_possible_netx = identify_connected_netx(flasher_binary)
  if len(list_possible_netx) == 0:
    # no netX could be identified
    l.error("no netX could be identified!")
    numErrors = -1
  else:
    port_of_netX = list_possible_netx[0].port
    assert(port_of_netX != 1) # more then one netX or 0 netX connected

    name_generated_binary_file_given = "binary_random_data.bin"
    binary_file_read_from_netx = os.path.join(gPath_binsNetxTarget, "read_back_file.bin")
    path_generated_file = os.path.join(gPath_binsNetxTarget, name_generated_binary_file_given)


    interface_to_test = port_of_netX

    final_json,final_config = init_json_files()
    die_config=final_json["test_config"]
    file_prefix = gPath_LuaFileRomloaderTarget

    #todo short this call
    # handling json input parameters from the config files
    test_command_list_final = generate_command_list(flasher_binary,binary_file_read_from_netx,file_prefix,final_config, "netX90", die_config, interface_to_test,path_generated_file)


    # Commands are generated, now generated, now run them!
    # todo: write global function for creating a logfile according to the job
    numErrors = 0

    default_carrier = command_carrier()
    default_carrier.change_dir_to_bin = True  # relevant for executing flasher with linux correct
    l.info("Execute generated commands abouve!")
    carrier_result = batch_command_base(default_carrier, test_command_list_final, path_logfile, logfile_praefix)
    binary_check_error = helper_check_binary_file(path_generated_file, binary_file_read_from_netx)
    if binary_check_error:
      l.error("binary files do not match!")
      numErrors = 1
      additional_info = 'binary files do NOT match!'
    else:
      additional_info = 'binary files match!'

    # todo: add infos about the tested netX to the logfile. Wirte global finction generating ogfiles. use existing
    numErrors += eval_batch_result(carrier_result, path_logfile, logfile_praefix, additional_info)

    l.info("Number of errors equals %d"%numErrors)

  return numErrors





def generate_full_romloader_command(parameter_commandline):
  '''
  Generates the testcommand for the romloader test.
  Output is separated into flasher binary and into command line arguments.
  The split was necessary to use the advanced flasher functions.
  :return: tuple(path_bin_flasher, parameter_commandline), the binary and the command line arguments without -p.
  '''

  return generate_full_flasher_command(parameter_commandline)









def logfiles_folder_reset_create():
  # remove old logfiles from folder
  old_logfiles = None
  try:
    old_logfiles = os.listdir(path_abs_logfiles_temporary)
  except BaseException as e:
    l.error("Looks like there is no heraci to reset! %s"%e)
  if old_logfiles:
    for f in old_logfiles:
      l.info("remove old file: %s" % f)
      try:
        os.remove(os.path.join(path_abs_logfiles_temporary, f))
      except BaseException as e:
        l.info(e)
  try:
    os.mkdir(path_abs_logfiles_temporary)
    os.mkdir(path_abs_logfiles_zipped)
  except OSError as e:
    if e.args == (17, 'File exists'):
      l.info('Skip logfile folder creation, folder exists')
    else:
      l.error("Can't create folder for logfiles %s or subfolders. Resaon: %s" % (gPath_logfile_folder, e.strerror))


def archive_logs(uuid_of_session,folder_source,folder_target):
  iErr = -1
  # generate path
  if cOS is enLin:
    logfile_archive = 'logfiles_%s_%s_%s' % (uuid_of_session, vLinux, cTheMachine)
  else:
    logfile_archive = 'logfiles_%s_%s' % (uuid_of_session, cTheMachine)
  path_logfile_archive = os.path.join(folder_target,logfile_archive)

  # compressing...
  if os.path.exists(folder_source):
    l.info('Compress to archive: %s' % logfile_archive)
    l.info("Compressing logfiles to %s(.zip)" % path_logfile_archive)
    # remove files which a zipped, when no error occured during compressing!
    try:
      shutil.make_archive(path_logfile_archive, 'zip', folder_source)
      iErr = 0
    except BaseException as e:
      l.error("Compressing files from %s to %s failed"%(folder_source,path_logfile_archive))
      l.error("Reason: >%s<"%e)
  else:
    l.error("Path to logfiles does not exist, cant archive logfiles! %s" % folder_source)
  return iErr


def ptbt_romloader_v1(logfile_path,blacklist, uuid_of_session, whitemask):
  command_to_test = 'test_romloader.lua'
  praefix_bin, suffix_arguments = generate_full_flasher_command(command_to_test)
  list_result = run_flasher_command_for_the_one_netx(praefix_bin, suffix_arguments, logfile_path,
                                                     uuid_of_session, whitemask, blacklist)
  if list_result[0] == 0:
    l.info('[pirate][result]: Err: %s, netX: %s [%s] cmd: %s' % (
    list_result[0], list_result[2], list_result[3], list_result[1]))
    iErr = 0
  else:
    appended = ""
    for ele in list_result:
      appended += "%s "%ele
    l.info('Err: %s'%appended)
    iErr = -94
  return iErr



def main():
  '''
  Executing test, un with install32 and instead with the version related to the plattform of the host the
  installation will be forced to generate the 32bit flasher.
  if minimal is in the string, the romloader will not be patced, this can be useful for final packages.
  Also dpinst is not instaled but delivered and extracted. reason: no autoinstall of dpinst!
  :todo: Black/White Mask does not apply to flasher test!
  :return:
  '''
  iErr = -1
  ScriptProgramm = ''

  try:
    ScriptProgramm = sys.argv[1]
  except IndexError as e:
    print("Please provide a command line argument ('install' for installsetup any other name for a module)  <%s>" % e)
    exit(-43)

  try:
    uuid_of_session = sys.argv[2]
    l.info("Running under inherited UUID: %s"%uuid_of_session)
  except IndexError as e:
    uuid_of_session =  str(uuid.uuid4())
    l.info("Running under locally generated UUID: %s" % uuid_of_session)




  if ScriptProgramm:  # check if plugin is set
    if  'install' in ScriptProgramm:
      if '32' in ScriptProgramm:
        l.info("Installing 32 bit version of Flasher")
        force_32_bit_exec = True
      else:
        l.info("Installing os conform version of Flasher")
        force_32_bit_exec = False
      l.info("Performing installation")


      # overwrites the existing romloader plugin of a old flasher with a new romloader plugin
      if installApplyRomloaderPatch:
        # skip installation of romloader, because system might already be patched
        InstallRomloaderPlugin = True  # will not copy the binaries contained in the netx/montest_binaries.bin
      else:
        InstallRomloaderPlugin = False

      # Adds all necassary testfiles for the test_romloader.lua
      if installApplyRomloaderTest:
        ApplyTestRomloader = True
      else:
        ApplyTestRomloader = False


      iErr = runInstallation(force_32_bit_exec,InstallRomloaderPlugin, ApplyTestRomloader)


    elif 'ptbt' in ScriptProgramm:

      l.info("Perform Test with plugin <%s>" % (ScriptProgramm))

      # input plugin name here
      # run_flasher_command_for_the_one_netx(str_full_absolute_commandstring)
      whitemask=[]#['romloader_usb','romloader_uart'] # will only use for device selection romloader_usb
      blacklist=[]#['romloader_uart']

      logfiles_folder_try_creation()
      logfiles_folder_reset_create()

      # Romloader test

      if 'test_romloader' in ScriptProgramm:
        iErr = ptbt_romloader_v1( path_abs_logfiles_temporary , blacklist, uuid_of_session, whitemask)
      elif 'test_flasher' in ScriptProgramm:
        # Warning, blacklist/whitemask do not apply for test_flasher!!!
        iErr = ptbt_flasher_v1(path_abs_logfiles_temporary)
      else:
        iErr = -5
        l.error("No test named: %s"%ScriptProgramm)
      if iErr == -1:
        l.error("invalid command for specifying test: %s"%ScriptProgramm)
      archive_logs(uuid_of_session,path_abs_logfiles_temporary,path_abs_logfiles_zipped)



  else:
    iErr = -93
    l.info("Please provide as first and only command line argument 'install' or 'ptbt_test_flasher/romloader'")

  evaluate(iErr)
  return iErr


def wrapper_for_flasher_only():
  '''
  Executing test, un with install32 and instead with the version related to the plattform of the host the
  installation will be forced to generate the 32bit flasher.
  if minimal is in the string, the romloader will not be patced, this can be useful for final packages.
  Also dpinst is not instaled but delivered and extracted. reason: no autoinstall of dpinst!
  :todo: Black/White Mask does not apply to flasher test!
  :return:
  '''

  uuid_of_session =  str(uuid.uuid4())

  l.info("Running under locally generated UUID: %s" % uuid_of_session)

  #todo: black/whit- mask from romloader test integrate

  # generate logfile folder
  logfiles_manage_init()

  iErr = ptbt_flasher_v1(path_abs_logfiles_temporary)

  archive_logs(uuid_of_session,path_abs_logfiles_temporary,path_abs_logfiles_zipped)

  evaluate(iErr)
  return iErr


def logfiles_manage_init():
  logfiles_folder_try_creation()
  logfiles_folder_reset_create()


def logfiles_folder_try_creation():
  try:
    os.mkdir(gPath_logfile_folder)
  except OSError as e:
    if e.args == (17, 'File exists'):
      l.info('Skip logfile folder creation, folder exists')
      e.strerror
    else:
      l.error("Can't create folder for logfiles %s or subfolders. Reason %s" % (gPath_logfile_folder, e.strerror))






if __name__ == "__main__":
  exit(main())