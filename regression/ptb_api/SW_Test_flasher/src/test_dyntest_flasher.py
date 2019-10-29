import unittest
import os, sys

file_dir = os.path.dirname(os.path.realpath(__file__))  # xxx/src/
project_root_path = os.path.dirname(file_dir)  # xxx/helper_platform_detect

base_root = os.path.dirname(project_root_path)  # location where all projects reside
sys.path.append(base_root)


from SW_Test_flasher.src.class_dyntest import *




class UnitTestFlasherTest(unittest.TestCase):

    def setUp(self):
        self.netX_chip = "netx90"
        self.netX_netx_interface = "interface"
        self.netX_Memory = ["SQI flash", "parflash", "intflash", "SD_card"]
        self.netX_TestGruppe = "mini" # normal, extended

        # memory_to_test = [{"b": "1", "u": "0"}, {"b": "1", "u": "0"}]
        self.memory_to_test = [{"b": "1", "u": "0"}]
        num_bytes_to_test = 1024*1024
        port_to_test = "romloader_jtag_netX_ARM966@NXJTAG-USB@1:2"
        self.path_flasher_binary = os.path.realpath("C:\\Daten_local_only\\Tools\\Hilscher\\flasher\\flasher_cli-1.5.8-windows_x86_BETA2_build101\\flasher_cli-1.5.8\\lua5.1.exe")
        self.path_flasher_files = os.path.realpath("C:\\Daten_local_only\\Tools\\Hilscher\\flasher\\flasher_cli-1.5.8-windows_x86_BETA2_build101\\flasher_cli-1.5.8")
        self.path_logfiles = os.path.realpath("C:\\Daten\\working\\test\\GDo\\log")

        Flashertest.init_logfiles(self.path_logfiles)
        
        
        self.parameter_port_to_test = "-p %s" % port_to_test


    # what ever name follows test_*(): doesent matter.
#    def test_Standard(self):
#        self.standard.run_test()
#        test_result = self.standard.numErrors_a[-1]
#        self.assertEqual(0, test_result[1])

#    def test_hash(self):
#        self.hash.run_test()
#        test_result = self.hash.numErrors_a[-1]
#        self.assertEqual(0, test_result[1])

#   def test_cli_test(self):
#        #self.cli_test.run_test()
#        #test_result = self.cli_test.numErrors_a[-1]
#        self.assertEqual(True, True)





if __name__ == '__main__':
    unittest.main()
