# coding=utf-8
import subprocess, sys, datetime, os, copy, time, re

from simpelTools.src.logging_default import *
import platform as lPl  # pip
from Selector_OS_Platform.platform_detect import *
from simpelTools.src.magic_strings import strip_command_arguments, helper_type_conversion

'''
this module is intendet to run commands on a command line.
It is designed to make it easy for the programmer to control the
os.execute commands. In Principle just set up the structure,
pass it to the executor, and ook again in the structure to see
the result auf the executed command.
This version favours the storage of the output to stdout direct,
to a python variable or to a file.
'''


def slugify(value):
  """
  Normalizes string, converts to lowercase, removes non-alpha characters,
  and converts spaces to hyphens.
  https://stackoverflow.com/questions/295135/turn-a-string-into-a-valid-filename
  """
  import unicodedata
  value = unicodedata.normalize('NFKD', value).encode('ascii', 'ignore')
  value = unicode(re.sub('[^\w\s-]', '', value).strip().lower())
  value = unicode(re.sub('[-\s]+', '-', value))
  return value


class command_carrier:
  ID = None # a ID used for the command to be executed.
  time_start = None
  time_end = None
  time_execute = None

  def time_calc(self):
    self.time_execute = self.time_end - self.time_start

  cmd = ''  # command to be executed
  executed = False
  change_dir_to_bin = False

  ret_val = None  # returnvalue of executed program
  str_stdout = ''  # if used, will return the output string of the program
  str_stderr = ''  # if used, will return the output string of the program

  # (prio 1) dirct log to upper consol
  direct_out = False  # activates direct stdout/err for seeing the progress, but not capturing it.
  direct_err = False

  # (prio 2) path for output files
  path_stdout = None  # path for storing logmessages from stdout (if set will not print them)
  path_stderr = None  # path for storing logmessages from stderr (if set will not print them)

  # (prio 3) structure internal string is filled

  # info:
  # direct:
  #  + you see the progress
  #  - you can't use it in the calling python script
  # path:
  #  + you have a file containing the output. more easy to copy, parse, universal, good for large output
  #  - you do not have the file in the program. Maintain location overwrite and old files etc.
  # subprocess.PIPE (default)
  # + You have the output returned in a variable useable in python
  # + recommanded way for small output (some 100 lines)
  # - heavy for huge outputs, don't know if safe against bufferoverflow

  # used in function
  stream_stdout = None  # stream to used for communication. may be default stdx or a file to write to.
  stream_stderr = None  # stream to used for communication. may be default stdx or a file to write to.


def helper_gen_headder(cmd_carry, form):
  tmp = "%s\n[pirate][file][%s][cmd]: %s\n\n---BEGIN LOG---\n" % (
  datetime.datetime.now().strftime('%Y-%m-%d %H:%M:%S'), form, cmd_carry.cmd)
  tmp_str = str(tmp)
  return tmp_str

def helper_gen_footer(cmd_carry, form):
  tmp = "---END LOG---\n\n%s\n[pirate][file][%s][cmd]: %s\nReal runtime: %fs\nReturn value: %d" % (
  datetime.datetime.now().strftime('%Y-%m-%d %H:%M:%S'), form, cmd_carry.cmd,cmd_carry.time_execute,cmd_carry.ret_val)
  tmp_str = str(tmp)
  return tmp_str


def runCommandBase(cmd_carry):
  '''
  Basic function for executing a externl programm.

  This does not alter a thing, justrun end return all values
  :param cmd_carry: Structure carrying several infos around the executed programm
  :return: class command_carrier Representation of command and result
  :waring: for large outputs please provide a file to pipe to.
  '''

  tmp_localwork_dir = os.getcwd()  # backup path
  if cmd_carry.change_dir_to_bin:
    tmp_command_list = cmd_carry.cmd.split()
    tmp_binary = os.path.dirname(tmp_command_list[0])
    os.chdir(tmp_binary)

  cmd_carry.executed = True

  # stdout:
  if cmd_carry.direct_out:
    cmd_carry.stream_stdout = sys.stdout  # send directly to consol p.communicate is empty + shell = True
  elif cmd_carry.path_stdout:
    # there is a path given where to redirect stdout to.
    cmd_carry.stream_stdout = open(os.path.realpath(cmd_carry.path_stdout), 'wb', 0)
    cmd_carry.stream_stdout.write(
      str.encode(helper_gen_headder(cmd_carry, 'stdout')))  # write headline to file containing command call
  else:
    # will be loaded after execution is done. Stored in variable
    cmd_carry.stream_stdout = subprocess.PIPE  # use the popen.PIPE This is a constant

  # stderr:
  if cmd_carry.direct_err:
    cmd_carry.stream_stdout = sys.stdout  # send directly to consol p.communicate is empty + shell = True
  elif cmd_carry.path_stderr:
    # there is a path given where to redirect stdout to.
    cmd_carry.stream_stderr = open(cmd_carry.path_stderr, 'wb', 0)
    cmd_carry.stream_stderr.write(str.encode(helper_gen_headder(cmd_carry, 'stderr')))
    # cmd_carry.stream_stderr.write(helper_gen_headder(cmd_carry, 'stderr'))
  else:
    # cmd_carry.stream_stderr = sys.stderr # send directly o python stdout without using communicate
    cmd_carry.stream_stderr = subprocess.PIPE  # use the popen.PIPE This is a constant
  cmd_carry.time_start = time.time()
  p = subprocess.Popen(cmd_carry.cmd,
                       stdout=cmd_carry.stream_stdout,
                       stderr=cmd_carry.stream_stderr,
                       shell=True)  # looks like shell True is for the return value, also opens a new shell as in stead inheriting the old window

  # comming functions returns when process has finished
  b_stdout, b_stderr = p.communicate()  # retrieve returnvalues if none
  cmd_carry.time_end = time.time()
  cmd_carry.time_calc()
  cmd_carry.executed = True # just mark the command as executed. For future use
  cmd_carry.ret_val = p.returncode

  # finish logfiles:
  if cmd_carry.path_stderr:
    # there is a path given where to redirect stdout to.
    # cmd_carry.stream_stderr = open(cmd_carry.path_stderr, 'wb', 0)
    cmd_carry.stream_stderr.write(str.encode(helper_gen_footer(cmd_carry, 'stderr')))
    cmd_carry.stream_stderr.close()
  if cmd_carry.path_stdout:
    # there is a path given where to redirect stdout to.
    #cmd_carry.stream_stdout = open(cmd_carry.path_stdout, 'wb', 0)
    cmd_carry.stream_stdout.write(
      str.encode(helper_gen_footer(cmd_carry, 'stdout')))  # write headline to file containing command call
    cmd_carry.stream_stdout.close()

  if b_stdout:
    cmd_carry.str_stdout = helper_type_conversion(b_stdout)
  if b_stderr:
    cmd_carry.str_stderr = helper_type_conversion(b_stderr)
    # import chardet): chardet.detect(open(in_file, 'rb').read())['encoding']
    # https://stackoverflow.com/questions/3323770/character-detection-in-a-text-file-in-python-using-the-universal-encoding-detect/3323810#3323810


  if cmd_carry.change_dir_to_bin:
    os.chdir(tmp_localwork_dir)

  return cmd_carry.ret_val


def helper_logfile_gen_path(path_logfile,strem,idx,logfile_prefix,cmd):
  """
  Takes a base path and several parameters for the logfilename.
  Returns a finnished path.
  slugify() is used to reduce the given string by non conform characters of filesystems
  :param path_logfile: Path to folder where logfile should reside
  :param strem: stderr or stdout
  :param idx: some index UUID or waht ever
  :param logfile_prefix: some specific name you want to share too
  :param cmd: command beeing executed. (will be stripped in file name)
  :return: Generated path to from a logfile.
  """
  # ---

  Name, vLinux, bin = lPl.dist()
  cOS, cPL, cThePlatform, cTheMachine = GetPlatformMatrixEntry()
  # ___
  if vLinux:
    version_string =  "%s_%s_%s"%(Name,vLinux,cTheMachine)
  else:
    version_string = "%s_%s"%(platform.platform(),cTheMachine)
  full_path = os.path.join(path_logfile, "%s.log" % slugify(u"%s_%d_%s" % (logfile_prefix, idx, strem)))
  return full_path

def batch_command_base(cmd_carry_default, array_command, path_logfile = '.', logfile_prefix = 'log'):
  """
  Provide a sequence with commands. Every single command will be invoked after each other.
  the result is an array consinting of the command carriers used for running every command.
  The logfile will look like Logfileprefix_AIndex_TheOutPipe_TheCommand.log
  The command is reduced to a character set which is accepted by all filesystems(in theory).
  :param cmd_carry_default: The default command carrier, which must be provided. It's taken as default setting.
  :param array_command: The array containing the commands as one string per command line
  :param path_logfile: a existing folder where to store the logfiles.
  :param logfile_prefix: The prefix with which every filename starts. Say a ID, or the name of the test.
  :return: An integer Error or a array.
  """

  # check
  if os.path.isdir(path_logfile) is False:
    l.error("Provided path for logfiles does not exist. exit cause of error!")
    return 42

  l.info("logging to %s"%helper_logfile_gen_path(path_logfile, 'stream', 42, logfile_prefix, "theCommand -param1 @ |\\?/ > log.123"))
  result = []
  l.info("Representation of executed commands are reduced by the absoulte path. Only filename and binary are displayed!")
  for idx, cmd in enumerate(array_command):

    l.info("[% 2d]run %s"%(idx, strip_command_arguments(cmd)))
    tmp_batch_cpy = copy.deepcopy(cmd_carry_default)
    tmp_batch_cpy.cmd = cmd
    tmp_batch_cpy.ID = idx


    command_representation = strip_command_arguments (tmp_batch_cpy.cmd).replace(' ','_')
    tmp_batch_cpy.path_stdout = helper_logfile_gen_path(path_logfile, 'stdout', idx, logfile_prefix, command_representation)
    tmp_batch_cpy.path_stderr = helper_logfile_gen_path(path_logfile, 'stderr', idx, logfile_prefix, command_representation)
    runCommandBase(tmp_batch_cpy)
    result.append(tmp_batch_cpy)
    l.info("[% 2d]    return value: %s" % (idx, tmp_batch_cpy.ret_val))

  return result


def eval_batch_result(array_command_carry,path_logfile=None,logfile_prefix=None,additional_info=None):
  """
  displaying infos from all tests in a kind of tabular
  :param array_command_carry: A array consisting of command carriers
  :return: 0 in case of that all commands had returnvalue == 0, else number failed commands. -1 in case of a error.
  """
  count_failed_commands = 0
  h_summary = None
  # open summary
  if path_logfile:
    if os.path.isdir(path_logfile):
      summary_file = helper_logfile_gen_path(path_logfile,'sumary',0,logfile_prefix,'')
      l.info("write summary to %s"%summary_file)
      # open lo
      h_summary = open(summary_file, 'wb', 0)
    else:
      l.error("provided path for batch summary does not exist! %s"%path_logfile)
      return -1


  for entry in array_command_carry:

    res = ''
    if entry.ret_val:
      count_failed_commands += 1
      res = 'Err: %03d'%entry.ret_val
    else:
      res = '  OK    '
    line = "[%s][R:%s][%s](t:%f): %s"%(entry.ID,entry.ret_val,res,entry.time_execute,entry.cmd)
    l.info(line)
    if h_summary:
      tmp = ''
      if type(line) is type(u''):
        tmp = line
      else:
        tmp = str.encode("%s" % line)
      h_summary.write(u"%s\n"%tmp)# write

  # write additional info
  tmp = ''
  if type(additional_info) is type(u''):
    tmp = line
  else:
    tmp = str.encode("%s" % additional_info)
  h_summary.write(u"%s\n" % tmp)  # write


  # close summary

  if h_summary:
    h_summary.close()
  return count_failed_commands




def test_batch_command_base():
  cmd_carry_default = command_carrier()
  log_path = '/tmp/log'

  array_command = ['uname','sleep 0.001','rm hallo','ls hallo', 'touch hallo', 'ls hallo']

  result = batch_command_base(cmd_carry_default, array_command,log_path)

  i = eval_batch_result(result,log_path,'summaryPreafix')

  if i == 0:
    l.error("Upper commands should have caused a error!")
  else:
    l.info("simple test logging passed!")



def test_run_command_Base():
  test_ret_val = 42
  cmd_to_test_stdout_stderr = 'echo "stdoutmessage"  && (>&2 echo "error_message") && exit %d' % test_ret_val

  test_command = command_carrier()
  test_command.cmd = cmd_to_test_stdout_stderr
  runCommandBase(test_command)

  for i in range(1):
    assert i == 0
    x = 0
    if test_command.str_stdout.strip() != b'stdoutmessage':
      print("failed 1")
      x = 1
    if test_command.str_stderr.strip() != b'error_message':
      print("failed 2")
      x = 1
    if x == 1:
      break
  else:
    print("[TB][simple IO]: everything ok!")

  print("Delaytest")

  '''
  Delaytest:
  should print following sequence in a time difference of 5sec

      Delaytest
      wait 5 sec
      Output 1
      Output 2
      Output END

  '''
  sec_to_wait = 2
  delay_test = "echo 'Following messages should appear in distance of {0} sec' && sleep {0} && echo 'Output 1' && sleep {0} && echo 'Output 2' && sleep {0} && echo 'Output END'".format(
    sec_to_wait)
  test_delay = command_carrier()
  test_delay.cmd = delay_test
  test_delay.direct_out = True
  runCommandBase(test_delay)

  stdout_file = 'stdout.txt'
  stderr_file = 'stderr.txt'

  test_file = command_carrier()
  test_file.path_stdout = stdout_file
  test_file.path_stderr = stderr_file
  test_file.cmd = cmd_to_test_stdout_stderr
  runCommandBase(test_file)

  for i in range(1):
    assert i == 0
    x = 0
    if test_file.str_stdout != None:
      print("failed 1")
      x = 3
    if test_file.str_stderr != None:
      print("failed 2")
      x = 4
    if test_file.ret_val != test_ret_val:
      print("failed 2")
      x = 5
    if x == 1:
      break
  else:
    print("[TB][file IO]: everything ok! (please check ffor file existence and content)")

  '''
  err.file:

    2019-04-25 12:32:39
    [pirate][file][stderr][cmd]: echo "stdoutmessage"  && (>&2 echo "error_message") && exit 42

    error_message

  out.file:

    2019-04-25 12:32:39
    [pirate][file][stdout][cmd]: echo "stdoutmessage"  && (>&2 echo "error_message") && exit 42

    stdoutmessage

  '''

  print("Done")



if __name__ == "__main__":
  # exit(test_batch_command_base())
  exit(test_batch_command_base())
