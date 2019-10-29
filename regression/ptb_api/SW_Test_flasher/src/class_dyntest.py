import sys, os
from abc import abstractmethod
import uuid
import shutil

from simpelTools.src.logging_default import *
from simpelTools.src.command_carrier import command_carrier, batch_command_base, eval_batch_result
from simpelTools.src.filetools import *
from Selector_OS_Platform.platform_detect import *
# todo: write batch command base into class off comman carrier, e.g. write a class "command_crrier"


# todo: monday compose tests
#  -loop
#  - detect netX, import from Framework
#  -detect-netX + json-routines (keep them in separate to keep them reuseable)
#  -maybe have a look at the python 3 standard fo os-detect, etc
#  -double check the command carrier with python 3
#  -generate 3.8 environment?
# todo: implement the json file script-handling
# todo: general parates to pass
# todo: Set input / output file for generation etc.
#  build in binary file match
#  find os-dependend build path from flasher relativ to file location
#  - result as a json document, stating with a dictionary
## later totos:
#   - logfiles are archived together with all other tests at the end.
#    - subfolder with enumerator and cclassname for every run
#    - Probably total result log?
#    - Log in json? put logfile path into json?
#    - think at managing UUID's


print(sys.executable)
print(sys.version)


# to be exported to some more useful place:



class Dyntest:
    """
    todo: set UUID from the outside world

    Behaviour:
    create object, "prepare", run the test, leave the test result as the purpose of this class.
    not intended to repeat a single step. only intended to encapsulate the tests and make them more readable!

    Note:
        Do not include the `self` parameter in the ``Args`` section.

    Args:
        msg (str): Human readable string describing the exception.
        code (:obj:`int`, optional): Error code.

    Attributes:
        testresult (dict): Tracing of test results
        path_folder_test_env (string): A working directory for test binaries
    """


    additional_info_to_logfile = ""     # some logfile info more
    bool_logfiles_init = False

    # arround test config
    testintensety = 'quick'

    # generated psth
    path_folder_test_env = None
    logfiles_last_run = None
    logfiles_archived = None
    logfiles_working_dir = None
    numErrors = 0
    numErrors_a = []

    def __init__(self):

        self.logfile_prefix = ""  # for normal the UUID of he test
        self.uuid_test = str(uuid.uuid4())
        pass

    @abstractmethod
    def run_test(self):
        pass

    @abstractmethod
    def pre_test_step(self):
        """
        sets up test environment. probably generating binary files etc.
        :return: nothing
        """
        # todo: probably move down
        pass

    @classmethod
    def init_logfiles(cls, path_folder_test_env):
        """
        Run this method to init the logfile folders. this is creating those folders as given in the parameter.
        will create 3 directories in path_folder_test_env_
        - last_run (place for all logffiles from the latest started run)
        - archived (for all older runs. The zipped last run folder)
        - working_dir ( the place where to generate e.g. binary files )
        :param path_folder_test_env: Root path for creating the logfiles
        :return: nothing
        """
        cls.path_folder_test_env = path_folder_test_env
        cls.bool_logfiles_init = True

        # generate path of sub folders
        cls.logfiles_last_run = os.path.join(cls.path_folder_test_env, 'last_run')
        cls.logfiles_archived = os.path.join(cls.path_folder_test_env, 'archived')
        cls.logfiles_working_dir = os.path.join(cls.path_folder_test_env, 'working_dir')  # for testfiles etc.

        # checking log files possibilities
        create_a_folder_if_not_existing(cls.path_folder_test_env)
        create_a_folder_if_not_existing(cls.logfiles_last_run, "last_run")
        create_a_folder_if_not_existing(cls.logfiles_archived, "archived")
        create_a_folder_if_not_existing(cls.logfiles_working_dir, "logfiles_working_dir")

        # now check if they are empty.^^ (what ever works, there might be a more easy way outside...)
        delete_all_files_in_folder(cls.logfiles_last_run)
        delete_all_files_in_folder(cls.logfiles_working_dir)

    def set_additional_logfile_info(self, additional_info_to_logfile):
        self.logfile_prefix = self.__class__.__name__
        self.additional_info_to_logfile = additional_info_to_logfile

    def archive_logs(self):
        cOS, cPL, cThePlatform, cTheMachine = GetPlatformMatrixEntry()
        Name, vLinux, bin = platform.dist()
        iErr = -1
        # generate path
        if cOS is enLin:
            name_logfile_archive = 'log_%s_%s_%s_%s' % (self.__class__.__name__, self.uuid_test, vLinux, cTheMachine)
        else:
            name_logfile_archive = 'log_%s_%s_%s' % (self.__class__.__name__, self.uuid_test, cTheMachine)
        path_logfile_archive = os.path.join(self.logfiles_archived, name_logfile_archive)

        # compressing...
        if os.path.exists(self.logfiles_archived):
            l.info('Compress to archive: %s' % name_logfile_archive)
            l.info("Compressing logfiles to %s(.zip)" % path_logfile_archive)
            # remove files which a zipped, when no error occured during compressing!
            try:
                shutil.make_archive(path_logfile_archive, 'zip', self.logfiles_last_run)
                iErr = 0
            except BaseException as e:
                l.error("Compressing files from %s to %s failed" % (self.logfiles_last_run, path_logfile_archive))
                l.error("Reason: >%s<" % e)
        else:
            l.error("Path to logfiles does not exist, cant archive logfiles! %s" % self.logfiles_last_run)
        return iErr


class Flashertest(Dyntest):
    """
    Basic Flashtest
    don't know if this class is necessary or just useful for herachical stageing.
    maybe this is the collectionmechanisem for the results? Argparse etc?
    """

    bool_params_init = False
    plugin_name = None
    bus_port_parameters_flasher = None
    flasher_binary = None
    path_lua_files = None





    # Handling command path
    command_structure = None  # representing parameters

    def __init__(self):
        Dyntest.__init__(self)
        self.test_binary_size = None
        self.command_strings = []  # strings generated from command array abouve

    def run_test(self):
        l.info("# run %s with uuid: %s" % (self.__class__.__name__, self.uuid_test))
        assert self.bool_params_init
        assert self.bool_logfiles_init
        self.pre_test_step()
        self.init_command_array()
        self.convert_final_command_entries_to_commands()
        self.run_batch_commands()
        self.archive_logs()
        l.info("# finished %s with uuid: %s" % (self.__class__.__name__, self.uuid_test))
        l.info("# Return for PyCharm")


    def init_params(self, plugin_name, memory_to_test, test_binary_size, path_lua_files, flasher_binary):

        # todo: should be more a temporary solution for debugging, not for testing
        self.plugin_name = "-p %s" % plugin_name["plugin_name"]
        self.bus_port_parameters_flasher = "-b %s -u %s -cs %s" % (memory_to_test["b"], memory_to_test["u"], memory_to_test["cs"])

        # test binary size has to be smaller or equal to the physically available size
        if test_binary_size <= memory_to_test["size"]:
            self.test_binary_size = test_binary_size
        else:
            self.test_binary_size = memory_to_test["size"]

        self.flasher_binary = flasher_binary
        self.path_lua_files = path_lua_files
        self.bool_params_init = True

    @abstractmethod
    def init_command_array(self):
        """
        the command array is the part of a sub sub class which makes the difference.
        So every class has to care for it on its own. will set: command_structure
        """
        pass

    @abstractmethod
    def pre_test_step(self):
        """
        Must be executed before "init_command_array()"
        :return:
        """
        raise NotImplementedError('Please provide a preparation method fro class >%s<, even if it is "pass"!' %
                                  self.__class__.__name__)

    def convert_final_command_entries_to_commands(self):
        if self.command_strings:
            assert True

        l.info("Generate commands:")
        for idx, ele in enumerate(self.command_structure):

            # make full file path
            tmp_full_file_path = os.path.join(self.path_lua_files, ele[0])
            self.command_structure[idx][0] = tmp_full_file_path
            # concat all to one string
            tmp_final_test_command = self.flasher_binary
            for int_ele in ele:
                tmp_final_test_command += " %s" % int_ele
            # append
            self.command_strings.append(tmp_final_test_command)
            #todo: later: this should be also a json tolerant structure, combining input and output.
            l.info(self.command_strings[-1])

    def run_batch_commands(self):
        default_carrier = command_carrier()
        default_carrier.change_dir_to_bin = True  # relevant for executing flasher with linux correct
        l.info("Execute generated commands above!")
        # todo: rework the command carrier, this is kind of not cool. (redundant code)
        # inert here final commands!
        carrier_result = batch_command_base(default_carrier, self.command_strings, self.logfiles_last_run, self.logfile_prefix)
        self.numErrors += eval_batch_result(carrier_result, self.logfiles_last_run, self.logfile_prefix, self.additional_info_to_logfile)
        self.numErrors_a.append([self.uuid_test, self.numErrors, self.__class__.__name__,len(self.command_strings)])

    @abstractmethod
    def check_additional_command(self):
        """
        Command for checking the binary files for example
        :return:
        """
        pass

