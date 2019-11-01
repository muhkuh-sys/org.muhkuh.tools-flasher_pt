import unittest
import os, sys

file_dir = os.path.dirname(os.path.realpath(__file__))  # xxx/src/
base_root = os.path.dirname(file_dir)  # location where all projects reside

sys.path.append(base_root)

from ptb_api.SW_Test_flasher.src.class_dyntest import *


class NxtFlasher_51(Flashertest):
    """
    verify, that the flasher does not start any SW at the netX
		NXHX51-ETM board
		JTAG port of netX 51
		SQI flash required
    """

    test_command_list = None

    binary_file_read_from_netx = None
    binary_file_write_to_netx = None

    def __init__(self):
        Flashertest.__init__(self)

    def pre_test_step(self):
        pass

    def init_command_array(self):
        test_file = os.path.join(file_dir, "kk_image.bin")

        enable_flasher = {"flasher": True}

        self.command_structure = [
            [enable_flasher, "cli_flash.lua", "flash", self.plugin_name, "%s %s" % (self.bus_port_parameters_flasher, test_file)],
            [enable_flasher, "cli_flash.lua", "verify", self.plugin_name, "%s %s" % (self.bus_port_parameters_flasher, test_file)],
        ]

