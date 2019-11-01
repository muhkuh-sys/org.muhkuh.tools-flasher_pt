import unittest
import os, sys

file_dir = os.path.dirname(os.path.realpath(__file__))  # xxx/src/
base_root = os.path.dirname(file_dir)  # location where all projects reside

# print base_root
sys.path.append(base_root)

from ptb_api.SW_Test_flasher.src.class_dyntest import *
from ptb_api.simpelTools.src.filetools import *


class FltHash(Flashertest):
    """
    define the hash tests
    """

    test_command_list = None
    binary_file_read_from_netx = None
    binary_file_write_to_netx = None

    def __init__(self):
        Flashertest.__init__(self)
        self.test_binary_size = 11*1024

    def pre_test_step(self):
        # Generate test-binary-files
        assert self.bool_logfiles_init
        self.binary_file_write_to_netx = os.path.realpath(os.path.join(self.logfiles_working_dir,
                                                       "test_%s_writefile_to_netx.bin" % self.__class__.__name__))

        generate_randome_file_by_size_and_name(self.binary_file_write_to_netx, self.test_binary_size)

    def init_command_array(self):
        enable_flasher = {"flasher": True}
        self.command_structure = [
            # write binary file which will be hashed
            [enable_flasher, "cli_flash.lua", "flash", self.bus_port_parameters_flasher, self.plugin_name,
             self.binary_file_write_to_netx],
            # run test-functions
            [enable_flasher, "cli_flash.lua", "verify_hash", self.bus_port_parameters_flasher, self.plugin_name,
             self.binary_file_write_to_netx],  # compares with read file
            [enable_flasher, "cli_flash.lua", "hash", self.bus_port_parameters_flasher, "-l 0x%x" % self.test_binary_size,
             self.plugin_name],
            # [enable_flasher, "flash_serflash.lua", interface_to_test_embedd, path_generated_file]  # not working!
        ]

