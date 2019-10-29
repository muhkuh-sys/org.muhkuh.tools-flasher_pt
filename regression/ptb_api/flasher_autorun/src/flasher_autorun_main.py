'''
This project aims to find all attached netX to the host
todo: check if all flaggs are set
todo: get xml description from host side an generate equal xml. This info cozuld be merged in CI like: 1939:0021 detected as netX 51/52
todo: check if pilepath for std::out exists
todo: set default file path for std::out, also add a flag then.
todo: make prio of the options more clear. probably just define values so that only one can be selected?
todo: align stdout/stderror to only one function with different parameters to reduce the redundant mess.

todo: init globals dynamic
todo: input flasher command with all parameters as a function call by pirate.py
todo: probably add the stuff to a class. INit class with flasher binary path.
todo: add parameter: flush errors/stdout from file or variable if exist. (separate calls)
'''

# works for pycharm and commandline

import sys, os
import re

file_dir = os.path.dirname(os.path.realpath(__file__))  # xxx/src/
project_root_path = os.path.dirname(file_dir)  # xxx/helper_platform_detect

base_root = os.path.dirname(project_root_path)  # location where all projects reside
print ("root:",base_root)
sys.path.append(base_root)

# for python
from Selector_OS_Platform.platform_detect import *
from simpelTools.src.command_carrier import *    # the command Carrierr executing the scripts
from simpelTools.src.logging_default import *    # Default logger used by all subsystems


l.critical("test log 'critical'")
l.info("test log 'info'")
l.debug("test log 'debug'")
l.error("test log error")

# needed from the outside:
# - get available netX
#   - flasher Binary
#   return avariable netX as list
# - run command on netX
#   - flasher Binary
#   - command file
#   - netX (connectionstring)
#   return command structure

name_file_cliFlash = 'cli_flash.lua'
command_flasher_listInterfaces = "list_interfaces"
command_flasher_detectNetx = "detect_netx"


def gen_helper_get_binpath(path_to_binary):
  '''
  Return the path of the binary, useful for accessing scriptfiles relative to binary
  :param path_to_binary: path to the flasher biary including bin name
  :return: absolute path
  '''
  folder_from_binary = os.path.dirname(path_to_binary)
  return folder_from_binary



def gen_list_interfaces(path_flasher_bin):
  '''
  Assuming cli_flash.lua in default place, generating path from given lua binary path
  :return: run_command_flasher_listInterfaces
  '''
  tmp_path_flasher_root=gen_helper_get_binpath(path_flasher_bin)
  tmp_path_flasher_cli =  os.path.join(tmp_path_flasher_root,name_file_cliFlash)
  run_command_flasher_listInterfaces = "%s %s %s"%(path_flasher_bin, tmp_path_flasher_cli , command_flasher_listInterfaces)
  return run_command_flasher_listInterfaces


def gen_detect_netX(path_flasher_bin, port):
  '''
  generating string for detecting netX
  :param path_flasher_bin: path to binary, preferable absolute. including .sh or .exe, no more, no less
  :param port: the port lik uart_romloader_...
  :return: the full command
  '''
  
  tmp_path_flasher_root = gen_helper_get_binpath(path_flasher_bin)
  tmp_path_flasher_cli = os.path.join(tmp_path_flasher_root,name_file_cliFlash)
  run_command_flasher_base_detectNetx = "%s %s %s -p %s" % ( path_flasher_bin, tmp_path_flasher_cli, command_flasher_detectNetx,port)  # add port name like "romloader_uart_ttyACM0"
  return run_command_flasher_base_detectNetx


class c_netx:

  def __init__(self):
    print('init netX-class')
  # properties retrieved from stringparse of the list_interface output
  it = ''      # position of element in list
  port = ''    # the -p parameter for later tests (most important)
  type = ''    # Additional info about the type of device, which is detected

  # set during detect_netx phase
  accessible = False
  tested = False

  # infos retrieved from detect_netx
  str_num_netX  = ''
  str_name_netX = ''


  def info(self):
    print(self.it,self.port,self.type)


def re_retrive_ports_from_list(str_list_interface_ouput):
  '''
  Expected is a string formatted as below with non leading width spaces.
  The string may contain other characters, but must contain a line with the content
  'START LIST NOT USED INTERFACES' and 'END LIST INTERFACES'. It is not controlled at which
  position this content is placed or how many additional characters are used. The head and the tail and
  the second and prelast line are discarded. The remaining lines have to be a match to avoid a assertion.

  Retrieved is the position, the 'Name' referenced as port an the Typ referenced as type.

      START LIST NOT USED INTERFACES (5 Interfaces found)

      1 : Name:romloader_usb_01_07            Typ: romloader_usb
      2 : Name:romloader_uart_ttyS0           Typ: romloader_uart
      3 : Name:romloader_uart_ttyS4           Typ: romloader_uart
      4 : Name:romloader_uart_ttyACM0         Typ: romloader_uart
      5 : Name:romloader_jtag_netX90_MPW_COM@NXJTAG-USB@1:2 Typ: romloader_jtag

      END LIST INTERFACES
  todo: you could control the number of interfaces found with the actual match. Be more precise with the regex
  :param output_list_interface: a multi line string containing the output from list_interfaces
  :return: array of class netX with found devices
  '''

  list = str_list_interface_ouput.split('\n')
  assert list
  idx_line_start = None
  idx_line_end   = None

  name_idx_start = 'START LIST NOT USED INTERFACES'
  name_idx_end = 'END LIST INTERFACES'

  # circel relevant entries
  for i,item in enumerate(list):
    l.debug("check: [%03d] %s"%(i,item))
    if name_idx_start in item:
      assert idx_line_start is None
      idx_line_start = i

    if name_idx_end in item:
      assert idx_line_end is None
      idx_line_end = i
  if idx_line_start is None or idx_line_end is None:
    l.error("Error looking for indexes: %s / %s"%(name_idx_start, name_idx_end))
    l.error("List output:\n%s"%str_list_interface_ouput)
    assert idx_line_start is not None
    assert idx_line_start is not None

  all_netx = []

  #1 : Name:romloader_usb_01_07            Typ: romloader_usb
  #5 : Name:romloader_jtag_netX_ARM966@NXJTAG-USB@1:2 Typ: romloader_jtag
  re_pattern_flasher_listInterfaces = '(\d+) : Name:([\w@\-:\./]+)\s+Typ: (\w+)'
  l.debug("Done got line %d to %d"%(idx_line_start,idx_line_end))

  l.debug("Asimilate Result")
  tmp_loop_begin = idx_line_start+2
  for i,sorted_line in enumerate(list[tmp_loop_begin:idx_line_end-1]): # remove leading and trailing line
    l.info("[% 3d] %s"%(tmp_loop_begin+i,sorted_line))
    tmatch = re.match(re_pattern_flasher_listInterfaces,sorted_line)
    if tmatch is None:
      l.error("unrecognised pattern in list: %s does not match %s"%(sorted_line, re_pattern_flasher_listInterfaces))
    m_netx = c_netx()
    try:
      m_netx.it = tmatch.group(1)
      m_netx.port = tmatch.group(2)
      m_netx.type = tmatch.group(3)
    except IndexError as ie:
      print(ie,'\n[pirate][error][%d]: string had not expected pattern: %s'%(i,sorted_line))
      assert False
    all_netx.append(m_netx)

  l.info("All netX:")
  for netx in all_netx:
    netx.info()

  return all_netx



def re_retrive_netxProperties_from_list(str_output_detect_netX, netx_Under_test):
  '''
  retraversing over given output, because the part will be at the end.
  Stringcompare is used for retrieving the right line and re for extraction.
  It fails if the string compare functions determins the wrong line. one shot only.

  Will analyse the output of detect netx and tries to retrieve more information about it.
  :param str_output_detect_netX:
  :return: -1 in case of error
  '''

  #Chip type: (10) netX90MPW
  re_pattern_netX_Type = 'Chip type:\s\((\d+)\)\s(.*)'
  tmp_list = str_output_detect_netX.split('\n')
  for line in reversed(tmp_list):
    if 'Chip type: (' in line:
      tmatch = re.match(re_pattern_netX_Type, line)
      if tmatch:
        try:
          netx_Under_test.str_num_netX  = tmatch.group(1)
          netx_Under_test.str_name_netX = tmatch.group(2)
        except IndexError as ie:
          l.error("Half recognised line %s"%line)
          l.error(ie)
      break

  assert (netx_Under_test.str_name_netX != '')
  assert (netx_Under_test.str_num_netX  != '')



def run_command_flasher_helper(str_command_flasher,log_file_name=None,path_logfile=None, UUID=''):
  '''
  Expects a command like below. A absoulte path to the binary and the lua-script-file is recommanded.
  A relative path might be possible, but is not tested.

  This function changes the execution directory to the directory where the binary resides.

      /home/aballmert/tmp/flasher/flasher_cli-1.5.4/lua5.1.sh /home/aballmert/tmp/flasher/flasher_cli-1.5.4/cli_flash.lua list_interfaces


  :warning: Do not use this for extra long test output. It is not researched, but it might cause a buffer overflow.
            better is to provide a file where to put the output.

  :param str_command_flasher: command as specified abouve
  :return: carrier_command wit the result of the command as a string.
  '''

  cmdcarry_flasher = command_carrier()
  cmdcarry_flasher.cmd = str_command_flasher
  cmdcarry_flasher.change_dir_to_bin = True
  if log_file_name:
    if path_logfile is None:
      l.error("[run_cmd_flash_helper]: logfile name provided, but no path!")
      return 1
    cmdcarry_flasher.path_stdout = helper_logfile_gen_path(path_logfile,"stdout",0,UUID,log_file_name)
    cmdcarry_flasher.path_stderr = helper_logfile_gen_path(path_logfile,"stderr",0,UUID,log_file_name)
    l.info('logging to %s and %s'%(cmdcarry_flasher.path_stdout,cmdcarry_flasher.path_stderr))

  l.info("run command: %s"%cmdcarry_flasher.cmd)
  runCommandBase(cmdcarry_flasher)

  return cmdcarry_flasher






def identify_connected_netx(path_flasher_binary,whitemask=[],blacklist=[]):

  '''
  development function
  The output of those commands is used to identify the netX. It is more easy to retrive the output from a variable
  instead of retriving it from a special file.
  :argument path_flasher_binary:
  :return: a list of the detected netX, if none are detected, list will be len([]) == 0
  '''

  tmp_run_command_flasher_listInterfaces = gen_list_interfaces(path_flasher_binary)
  car_list_interfaces = run_command_flasher_helper(tmp_run_command_flasher_listInterfaces)
  accessable_netX = [] # final list which contains the nbetX which have responded posetive
  if car_list_interfaces.ret_val:
    l.error("List command failed with retval != 0 [%d]"%car_list_interfaces.ret_val)
    l.error("\tcmd: %s" % car_list_interfaces.cmd)
    if car_list_interfaces.str_stderr:
      l.error("\tstderr: %s" % car_list_interfaces.str_stderr)
    if car_list_interfaces.str_stdout:
      l.error("\tstdout: %s" % car_list_interfaces.str_stdout)
  else:
    #success, we shoul have a list
    all_netx = re_retrive_ports_from_list(car_list_interfaces.str_stdout)

    if len(all_netx) == 0:
      l.error("no netX found")
    else:

      # apply the black and white mask before even touching the netX
      list_black_white = apply_whitemask_blacklist(blacklist, all_netx, whitemask)


      for netx_under_test in list_black_white:

        #run_command_detect_netx = "%s %s"%(run_command_flasher_base_detectNetx, netx_under_test.port )
        run_command_detect_netx = gen_detect_netX(path_flasher_binary,netx_under_test.port)
        tmp_car_detect_netx = run_command_flasher_helper(run_command_detect_netx)

        if(tmp_car_detect_netx.ret_val == 0):
          # will add name and detected type of the netX to the structure.
          re_retrive_netxProperties_from_list(tmp_car_detect_netx.str_stdout, netx_under_test)
          accessable_netX.append(netx_under_test)
          l.info("\t[%s] (%s) netX Type: %s "%(netx_under_test.port,netx_under_test.str_num_netX ,netx_under_test.str_name_netX))
        else:
          # no netX found, display log of detext_netX
          l.info("log from detect_netx: \nstdout: %s \n stderr:\n%s"%(tmp_car_detect_netx.str_stdout, tmp_car_detect_netx.str_stderr))
  return accessable_netX








def test_ports_from_list():
  str_input ='''
(\d+) : Name:([\w@\-:]+) Typ: (\w+) // full

-romloader_jtag_provider::DetectInterfaces(): sizEntries=1

START LIST NOT USED INTERFACES (5 Interfaces found)

1 : Name:romloader_usb_01_0c            Typ: romloader_usb            
2 : Name:romloader_uart_ttyS0           Typ: romloader_uart           
3 : Name:romloader_uart_ttyS4           Typ: romloader_uart           
4 : Name:romloader_uart_ttyACM0         Typ: romloader_uart           
5 : Name:romloader_jtag_netX_ARM966@NXJTAG-USB@1:2 Typ: romloader_jtag           

END LIST INTERFACES
  '''
  re_retrive_ports_from_list(str_input)


def flasher_run_batch(arg_flasher_binary, list_flasher_parameters, path_logfile, logfile_preafix=None):
  """
  runns all commands provided for the flasher.
  has some lines from run_flasher_command_for_the_one_netx() highjackt!
  :param arg_flasher_binary: Path to a flasher binary to check out the correct netx
  :param array_commands: commans for the flasher binary (without the flasher binary)
  :param path_logfile: Path where all logffiles from stdout/stderr/summary are stored
  :param logfile_preafix: A sequence of alphanumeric, leading th log file name
  :return: Number of commands not returned with error. Or -1 in case of a major error
  """
  l.info('[batch][test]: checking for netX')
  list_possible_netx = identify_connected_netx(arg_flasher_binary,path_logfile)
  ll = len(list_possible_netx)
  l.info('[batch][test]: num netX found: %d'%ll)
  if ll != 1:
    if ll == 0 or ll is None:
      l.error("No netX found, aborting")
      return 1
    else:
      l.error("more then one netX is found, this test expects precisely one netX!, no futher command will be invoked!")
      return 2
  else:
    # display used netX
    l.info("[batch]: Found netx: {0} at port: {1}".format(list_possible_netx[0].type,list_possible_netx[0].port))
    l.info('[batch][execute]: generate command carrier for final command')

    # gnerate default command carrier
    default_carrier = command_carrier()
    default_carrier.change_dir_to_bin = True  # relevant for executing flasher with linux correct

    # merge flasher commands with flasher binary
    array_composed_commands = []
    for flash_parameter in list_flasher_parameters:
      array_composed_commands.append("%s %s -p %s" % (arg_flasher_binary, flash_parameter, list_possible_netx[0].port))
    assert (len(list_flasher_parameters) == len(array_composed_commands))

    # execute commands
    carrier_result = batch_command_base(default_carrier, array_composed_commands, path_logfile, logfile_preafix)
    numErrors = eval_batch_result(carrier_result, path_logfile, logfile_preafix)

    if numErrors < 0:
      l.error('major error in Trst structure')
    elif numErrors > 0:
      l.error('(%d/%d) Test have faild.'%(numErrors,len(carrier_result)))
    else:
      l.info('batch has passed!')
    return numErrors


def test_def_flasher_run_batch():

  path_to_binary = '/home/aballmert/Downloads/flasher_cli-1.5.5/lua5.1.sh'
  path_to_loglocation = '/tmp/log'
  logfile_praefix = 'plog'
  array_commands = ['info','detect_netx', 'list_interfaces']

  assert(os.path.isfile(path_to_binary))
  assert(os.path.isdir(path_to_loglocation))

  numErrors = flasher_run_batch(path_to_binary, array_commands, path_to_loglocation, logfile_praefix)

  if numErrors:
   l.error("Test Faild, for normal all tests should have succeeded!")
  else:
    l.info("Test Passed!")




def run_flasher_command_for_the_one_netx(arg_flasher_binary, arg_flasher_parameter,path_to_logfile_folder=None,UUID="",whitemask=[],blacklist=[]):
  """
  The aim is to run the provided command for the only avariable netX.
  Background is the usage in the Pirate Test Bay, where only one device at one point in time is connected to one
  virtual machine.
  The provided command is a full command for the flasher with a absolute path. The scematic assumes, that there is no
  -p parameter yet entered. So this cycle adds in the end of the provided command line a ' -p interface_to_use'.
  During this functions all for the flasher avariable interfaces are checked. For the to the path of the flasher binary is needed.
  at the same location of the binary the cli_flash.lua file is expected which is used to retrieve the avariable interfaces.

  for now use std.out (direct), so output is directly send to console of the pipelinescript.

  The returnvalue is a 4Tuple out of:
  - ret_val from script
  - cmd_carr.cmd: the executed command
  - port: the port of the netX
  - type: also the netX type

  :argument arg_flasher_binary: >[/path/to/binary.bin]< /path/to/scriptfile -b x -other parameter -p PordAddedAutoFunction)
  binary and file is recommanded.
  :argument arg_flasher_parameter: (/path/to/binary.bin) >[/path/to/scriptfile -b x -other parameter]< (-p PordAddedAutoFunction)
  :return: [0]==0 if success (commmand operation successful and only one netx detected) otherwise !=0
  """

  l.info('[test]: checking for netX')
  list_black_white_netx = identify_connected_netx(arg_flasher_binary,whitemask ,blacklist)

  #final_list = apply_whitemask_blacklist(blacklist, list_possible_netx, whitemask)

  ll = len( list_black_white_netx )
  l.info('[test]: num netX found: %d' % ll)
  if ll != 1:
    if ll == 0 or ll is None:
      l.error("No netX found, aborting")
      return [2,0]
    else:
      l.error("more then one netX is found, this test expects precisely one netX!, no futher command will be invoked!")
      for netx in list_black_white_netx:
        l.info("... found %s at %s"%(netx.str_name_netX,netx.port))
      return [2,0]
  else:
    #there is, as expectd, only one netX, perform the command!
    l.info("Found netx: {0} at port: {1}".format(list_black_white_netx[0].type,list_black_white_netx[0].port))
    l.info('[execute]: generate command carrier for final command')

    cmd_flasher_test = "%s %s -p %s"%(arg_flasher_binary,arg_flasher_parameter,list_black_white_netx[0].port)
    l.info('[execute]: run command from command carrier')
    l.info('[execute]: %s' % cmd_flasher_test)
    l.info('[execute]: %s at port: %s '%(list_black_white_netx[0].str_name_netX,list_black_white_netx[0].port))
    LogFilePraefix = "%s_%s"%(list_black_white_netx[0].str_name_netX,list_black_white_netx[0].port)
    cmd_carr = run_command_flasher_helper(cmd_flasher_test,LogFilePraefix,path_to_logfile_folder,UUID)
    l.info('[execute][output]:')
    print(cmd_carr.str_stdout)
    if cmd_carr.ret_val:
      l.error('[execute][error]: Command returned with error %d'%cmd_carr.ret_val)
    else:
      l.info('[execute][done]: Successfully executed the command!')
    return cmd_carr.ret_val, cmd_carr.cmd, list_black_white_netx[0].port, list_black_white_netx[0].type


def apply_whitemask_blacklist(blacklist, list_possible_netx, whitemask):
  # kicks all, what is not contained in the mask
  if whitemask:
    reduced_list = []
    for netx in list_possible_netx:
      for white in whitemask:
        if white == netx.type:
          l.info("[selection][whitemask][%s] keep interface [%s]: %s" % (
            netx.str_name_netX, whitemask, netx.type))
          reduced_list.append(netx)
          break
      else:
        l.info("[selection][whitemask][%s] 'Remove' interface because is not in white mask [%s]: %s" % (
        netx.str_name_netX, whitemask, netx.type))
    working_list = reduced_list
  else:
    working_list = list_possible_netx
  # kicks all out, what is in the list
  if blacklist:
    list_black_survivers = []
    for netx in working_list:
      for black in blacklist:
        if black == netx.type:
          l.info("[selection][blacklist][%s][%s] Removed interface  because of blacklist : %s" % (
          netx.str_name_netX, netx.type, netx.type))
        else:
          l.info("[selection][blacklist][%s][%s]: keep  " % (netx.str_name_netX, netx.type))
          list_black_survivers.append(netx)
    final_list = list_black_survivers
  else:
    final_list = working_list
  return final_list


if __name__ == "__main__":

  test_def_flasher_run_batch()
  exit()

  '''
  Does do detect all netX on the mchine, retruns with error if there are num netX uneven one.
  checks the netX with list interfaces and every interface with detect.
  Afterwards it performs the command given as first command line argument.
  '''
  debug = 1
  if debug:
    exit(run_flasher_command_for_the_one_netx("/home/aballmert/Downloads/flasher_cli-1.5.4/lua5.1.sh", "/home/aballmert/Downloads/flasher_cli-1.5.4/cli_flash.lua detect_netx"  )[0])
  if len(sys.argv) != 2:
    print("[pirate][assumtion]: There is only one interface of one netX connected to the host.")
    print("[pirate][usage]: Provide as first command line argument the command you would like to execute with the flasher")
    print(
      "[pirate][usage]: this tool adds the parameter '-p port' to the command. The 'port' is retrived by checking all netX")
    exit(1)
  else:
    the_arg_flasher_binary = sys.argv[1] # first argument
    arg_flasher_parameter = sys.argv[2] # parameter ( abs/path/scriptfile -b option -other_options ... but not -p )
    exit(run_flasher_command_for_the_one_netx( the_arg_flasher_binary, arg_flasher_parameter)[0])