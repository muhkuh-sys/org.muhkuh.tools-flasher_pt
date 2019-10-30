
import unittest

import os, sys

file_dir = os.path.dirname(os.path.realpath(__file__))  # xxx/src/
# project_root_path = os.path.dirname(os.path.dirname(file_dir))  # xxx/helper_platform_detect

base_root = os.path.join(file_dir, "ptb_api")
sys.path.append(base_root)

from ptb_api.SW_Test_flasher.src.class_dyntest import *
from NXTFLASHER_51.tc_nxtflasher_51 import NxtFlasher_51
from FLT_STANDARD.tc_flt_standard import FltStandard
from FLT_HASH.tc_flt_hash import FltHash



class UnitTestFlasherTest(unittest.TestCase):

    def setUp(self):
        # parameter provided by the higher level to qualify the test suite

        #self.plugin_name = {"plugin_name": "romloader_jtag_netX_ARM966@NXJTAG-USB@1:2", "netx_port": "JTAG", "netx_protocol": "JTAG", "netx_chip_type": 7, "netx_chip_type_id": "netx51_52_stepB"}
        self.plugin_name = {"plugin_name": "romloader_jtag_netX90_COM@NXJTAG-USB@1:2", "netx_port": "JTAG", "netx_protocol": "JTAG", "netx_chip_type": 14, "netx_chip_type_id": "netx90_rev1"}

        #self.memories_to_test = [{"b": 1, "u": 0, "cs": 0, "name": "SQI-Flash Winbond ABC", "size": 4*1024*1024}]

        self.memories_to_test = [{"b": 1, "u": 0, "cs": 0, "name": "SQI-Flash Winbond ABC", "size": 4*1024*1024},
                                 {"b": 2, "u": 0, "cs": 0, "name": "INT flash 0", "size": 512 * 1024},
                                 {"b": 2, "u": 1, "cs": 0, "name": "INT flash 1", "size": 512 * 1024},
                                 {"b": 2, "u": 2, "cs": 0, "name": "INT flash 2", "size": 512 * 1024},
                                 {"b": 2, "u": 3, "cs": 0, "name": "INT flash 0/1", "size": 1024 * 1024}]

        # test group
        # short
        self.testGroup = ["short", "special"]

        self.path_flasher_binary = os.path.realpath("C:\\Daten_local_only\\Tools\\Hilscher\\flasher\\flasher_cli-1.5.8-windows_x86_BETA2_build101\\flasher_cli-1.5.8\\lua5.1.exe")
        self.path_flasher_files = os.path.realpath("C:\\Daten_local_only\\Tools\\Hilscher\\flasher\\flasher_cli-1.5.8-windows_x86_BETA2_build101\\flasher_cli-1.5.8")
        self.path_logfiles = os.path.join(file_dir, "log")

        Flashertest.init_logfiles(self.path_logfiles)


    # what ever name follows test_*(): doesn't matter.
    def test_Standard(self):
        """
        Testdescription
        flasher CLI standard tests

        :return:
        """

        num_bytes_to_test = 1024 * 1024

        # loop over all available flashes
        test_results = 0
        for memory_to_test in self.memories_to_test:
            tc = FltStandard()
            tc.init_params(self.plugin_name, memory_to_test,
                           num_bytes_to_test,
                           self.path_flasher_files,
                           self.path_flasher_binary)
            tc.run_test()
            test_result = tc.numErrors_a[-1]
            # collect all test results
            test_results += test_result[1]

        self.assertEqual(0, test_results)

    def test_hash(self):
        """
        Testdescription
        flasher CLI HASH tests

        :return:
        """

        # skip for netX90, because the flasher for netX 90 does not implement the hash function
        if self.plugin_name["netx_chip_type"] in [10, 13, 14]:
            self.skipTest("not supported for netX 90")


        num_bytes_to_test = 1024 * 1024

        # loop over all available flashes
        test_results = 0
        for memory_to_test in self.memories_to_test:

            tc = FltHash()
            tc.init_params(self.plugin_name, memory_to_test ,
                           num_bytes_to_test,
                           self.path_flasher_files,
                           self.path_flasher_binary)
            tc.run_test()
            test_result = tc.numErrors_a[-1]
            # collect all test results
            test_results += test_result[1]

        self.assertEqual(0, test_results)


    def test_NXTFLASHER_51(self):
        """
        Testdescription

        :return:
        """

        # execute only for netX56B
        if self.plugin_name["netx_chip_type"] in [7]:
            pass
        else:
            self.skipTest("Test NXTFLASHER_51 only for netX56B")



        # loop over all available flashes
        test_results = 0
        # store information, if a test was executed
        test_started = 0
        for memory_to_test in self.memories_to_test:

            # test requires external SQI flash
            if (memory_to_test["b"] in [1] and
                    memory_to_test["u"] in [0] and
                    memory_to_test["cs"] in [0] and
                    memory_to_test["size"] > 1*1024*1024):
                test_started = 1
            else:
                # skip the sub test
                continue

            tc = NxtFlasher_51()
            tc.init_params(self.plugin_name, memory_to_test ,
                           "",
                          self.path_flasher_files,
                          self.path_flasher_binary)
            tc.run_test()
            test_result = tc.numErrors_a[-1]
            # collect all test results
            test_results += test_result[1]

        if test_started == 1:
            self.assertEqual(0, test_results)
        else:
            self.skipTest("Test only for netX56B with external SQI flash")




if __name__ == '__main__':
    unittest.main()