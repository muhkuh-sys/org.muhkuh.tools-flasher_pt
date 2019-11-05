import unittest
import os, sys

file_dir = os.path.dirname(os.path.realpath(__file__))  # xxx/src/
base_root = os.path.dirname(file_dir)  # location where all projects reside

# print base_root
sys.path.append(base_root)

from ptb_api.SW_Test_flasher.src.class_dyntest import *
from ptb_api.simpelTools.src.filetools import *


class FltStandardSqiFlash(Flashertest):
    """
    define the standard tests
    """

    test_command_list = None

    binary_file_read_from_netx = None
    binary_file_write_to_netx = None

    def __init__(self):
        Flashertest.__init__(self)
        self.test_binary_size = 5*1024

    def pre_test_step(self):
        # Generate test-binary-files
        assert self.bool_logfiles_init
        self.binary_file_read_from_netx = os.path.realpath(os.path.join(self.logfiles_working_dir,
                                                       "test_%s_read_file_from_netx.bin" % self.__class__.__name__))
        self.binary_file_write_to_netx = os.path.realpath(os.path.join(self.logfiles_working_dir,
                                                       "test_%s_writefile_to_netx.bin" % self.__class__.__name__))
        generate_randome_file_by_size_and_name(self.binary_file_write_to_netx, self.test_binary_size)

    def init_command_array(self):
        enable_flasher = {"flasher": True}
        self.command_structure = [
            [enable_flasher, "cli_flash.lua", "-h"],
            [enable_flasher, "cli_flash.lua", "list_interfaces"],
            [enable_flasher, "cli_flash.lua", "detect_netx", self.plugin_name],
            [enable_flasher, "cli_flash.lua", "detect", self.bus_port_parameters_flasher, self.plugin_name],
            [enable_flasher, "cli_flash.lua", "erase", self.bus_port_parameters_flasher, "-l 0x%x" % self.test_binary_size, self.plugin_name],
            [enable_flasher, "cli_flash.lua", "flash", self.bus_port_parameters_flasher, self.plugin_name, self.binary_file_write_to_netx],
            [enable_flasher, "cli_flash.lua", "read", self.bus_port_parameters_flasher, "-l 0x%x" % self.test_binary_size, self.plugin_name,
             self.binary_file_read_from_netx],
            [enable_flasher, "cli_flash.lua", "verify", self.bus_port_parameters_flasher, self.plugin_name, self.binary_file_write_to_netx],
        ]


class FltStandardOtherFlash(Flashertest):
    """
    define the standard tests
    """

    test_command_list = None

    binary_file_read_from_netx = None
    binary_file_write_to_netx = None

    def __init__(self):
        Flashertest.__init__(self)
        self.test_binary_size = 5*1024

    def pre_test_step(self):
        # Generate test-binary-files
        assert self.bool_logfiles_init
        self.binary_file_read_from_netx = os.path.realpath(os.path.join(self.logfiles_working_dir,
                                                       "test_%s_read_file_from_netx.bin" % self.__class__.__name__))
        self.binary_file_write_to_netx = os.path.realpath(os.path.join(self.logfiles_working_dir,
                                                       "test_%s_writefile_to_netx.bin" % self.__class__.__name__))
        generate_randome_file_by_size_and_name(self.binary_file_write_to_netx, self.test_binary_size)
        shutil.copy(self.binary_file_write_to_netx, self.logfiles_last_run)

    def init_command_array(self):
       enable_flasher = {"flasher": True}
       self.command_structure = [
            [enable_flasher, "cli_flash.lua", "detect", self.bus_port_parameters_flasher, self.plugin_name],
            [enable_flasher, "cli_flash.lua", "flash", self.bus_port_parameters_flasher, self.plugin_name, self.binary_file_write_to_netx],
            [enable_flasher, "cli_flash.lua", "read", self.bus_port_parameters_flasher, "-l 0x%x" % self.test_binary_size, self.plugin_name,
             self.binary_file_read_from_netx],
            [enable_flasher, "cli_flash.lua", "verify", self.bus_port_parameters_flasher, self.plugin_name, self.binary_file_write_to_netx],
            [enable_flasher, "cli_flash.lua", "erase", self.bus_port_parameters_flasher, "-l 0x%x" % self.test_binary_size,
             self.plugin_name],
        ]


