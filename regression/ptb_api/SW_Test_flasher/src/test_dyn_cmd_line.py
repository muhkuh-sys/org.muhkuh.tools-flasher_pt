import json, os

from simpelTools.src.logging_default import *



config_string = """
{
  "test_config": [
    {
      "chip_on_board": "netX42",
      "board_id": "123456789",
      "has_hash":0,
      "board_name":"nxhx42JTAG",
      "storage_default":"IFLASH0",
      "storage_available": [
        {
          "select_code": {
            "u": 0,
            "b": 2,
            "cs": 5
          },
          "name": "SQI_flash",
          "storage_type": "eMMC",
          "name_in_flasher": "SQI1"
        },
        {
          "name": "Internal Flash",
          "name_in_flasher": "IFLASH0",
          "select_code": {
            "u": 0,
            "b": 9,
            "cs": 5
          }
        }
      ],
      "chip": {
        "interfaces": [
          "uart",
          "jtag",
          "RS232"
        ]
      }
    }
  ],
  "test_version": "v0.0.1"
}
"""
name_testdescription = 'testdesc.json'
test_definitions = """{
  "name_test": "General Flasher Test",
  "version": "0.0.1",
  "parameters": {
    "perform_cli_test":0,
    "perform_cli_test":"If a long cli thest should be added to the commands",
    "test_range": "_default",
    "_test_range": ["_full","_default","name_in_flasher"],
    "test_binary_size_byte":1024
  }
}
"""


final_json = 'not_set'
final_config = 'not_set'

def init_test_environment():
  # https://realpython.com/python-json/
  with open(name_cfg_file, "wb") as write_file:
    json.dump(json.loads(config_string), write_file, indent=4)
  with open(name_testdescription, "wb") as write_file:
    json.dump(json.loads(test_definitions), write_file, indent=4)


def init_json_files():
  global name_cfg_file, final_json, final_config
  # files are expected to be in this very folder where this file resides!
  abs_path_local_file = os.path.dirname(__file__)
  name_cfg_file = "Board_config_flasher_test_cor.json"
  name_test_desc = "testdesc.json"
  path_cfg_file = os.path.join(abs_path_local_file, name_cfg_file)
  path_test_desc = os.path.join(abs_path_local_file, name_test_desc)
  with open(path_cfg_file, "rb") as read_file:
    final_json = json.load(read_file)
    # print(json.dumps(final_json, indent=2))
  with open(path_test_desc, "rb") as read_file:
    final_config = json.load(read_file)
    # print(json.dumps(final_json, indent=2))
  return final_json,final_config




# read json file

## find name default


def json_append_parameters(storage):
  """
  Input:
  "select_code": {
    "u": 0,
    "b": 2,
    "cs": 5
  },
  function generates from given json a list of command line parameters.
  :param parameters: storage["select_code"]
  :return: -cs 5 -b 9 -u 0
  """
  tmp_parameters = ''
  global ele
  for ele in storage["select_code"]:
    tmp_parameters += ("-%s %d " % (ele, storage["select_code"][ele]))
  return tmp_parameters


def get_select_code_from_strorage_by_name(board, tmp_name_storage_default):
  for storage in board["storage_available"]:
    if storage['name_in_flasher'] == tmp_name_storage_default:
      print("found default storage for: %s(%s) name: %s" % (
        storage['name'], storage['name_in_flasher'], tmp_name_storage_default))
      tmp_parameters = json_append_parameters(storage)
      return tmp_parameters
  else:
    print("default parameter is not part auf storage: %s", tmp_name_storage_default)
    return None


def get_default_select_code_from_storage(board):
  """
  Input the board, output the default command code of the storage
  {
      "chip_on_board": "netX42",
      "board_id": "12345678...

  :param board: The json describing the board
  :return: The code for the default storage
  """
  tmp_name_storage_default = board["storage_default"]
  ## Search the default storage
  return get_select_code_from_strorage_by_name(board, tmp_name_storage_default)

def get_all_select_code_from_storage(board):
  """
  All caodes of every storage of a board a generated ans presented as a list. This list is ready
  to be included in the command line of the flasher
  {
      "chip_on_board": "netX42",
      "board_ ...
  :param board: board config
  :return: -cs 5 -b 9 -u 0
  """
  codes_of_storage = []
  for storage in board["storage_available"]:
    codes_of_storage.append(json_append_parameters(storage)) # eigneltich nur ueber storage iterieren
  return codes_of_storage








def gen_final_commands(parameters, binary_file_read_from_netx, port_to_test, test_binary_size, path_generated_file, has_hash=0, has_test_cli=0, list_of_final_command_entries=None):
  """
  Generates a list of commands depending oon input parameters
  :param parameters: "-" parameters to select the correct storage
  :param test_binary_size: the size of testpackages which should be written down and loaded up
  :param path_generated_file: the file path for the temporary file which ill be compared with the original after upload
  :param has_hash: If True, hasfunctions will be added to the list of commands
  :param has_test_cli: If true the long cli-Test commands will be added too.
  :return: A list of lists. sub list contains the command line in tuples
  """

  # take json-arguments as the dict it is, probably make a checkoup when retriving the data from json befor test
  #  even starts?
  port_to_test = "-p %s" % port_to_test
  if not list_of_final_command_entries:
    list_of_final_command_entries = []
  test_command_list = [
    ["cli_flash.lua", "-h"],
    ["cli_flash.lua", "detect_netx", port_to_test],
    ["cli_flash.lua", "erase", parameters, "-l 0xffffffff", port_to_test],
    ["cli_flash.lua", "flash", parameters, port_to_test, path_generated_file],
    ["cli_flash.lua", "read", parameters, "-l 0x%x" % test_binary_size, port_to_test, binary_file_read_from_netx],
    ["cli_flash.lua", "flash", parameters, port_to_test, path_generated_file],
    ["cli_flash.lua", "verify", parameters, port_to_test, path_generated_file],
  ]
  list_of_final_command_entries.extend(test_command_list)

  if has_hash:
    hash_commands = [
      ["cli_flash.lua", "verify_hash", parameters, port_to_test, path_generated_file],  # compares with read file
      ["cli_flash.lua", "hash", parameters, "-l 0x%x" % test_binary_size, port_to_test]
      # ["flash_serflash.lua", interface_to_test_embedd, path_generated_file]  # not working!
    ]
    list_of_final_command_entries.extend(hash_commands)

  if has_test_cli:
    cli_commands=[
      ["cli_flash.lua", "testcli", parameters, port_to_test],  ## lansam, weil jeds mal ein neuer flasher heruntergeladen wird. (once every plattform)
      ["cli_flash.lua", "test", parameters, port_to_test],      # wait until final release
    ]
    list_of_final_command_entries.extend(cli_commands)

  return list_of_final_command_entries




def gen_roling_write_frame_final_commands(parameters, port_to_test, path_generated_file):
  """
   Generates a list of commands depending on input parameters

   :param parameters: "-" parameters to select the correct storage
   :param test_binary_size: the size of testpackages which should be written down and loaded up
   :param path_generated_file: the file path for the temporary file which ill be compared with the original after upload
   :param has_hash: If True, hasfunctions will be added to the list of commands
   :param has_test_cli: If true the long cli-Test commands will be added too.
   :return: A list of lists. sub list contains the command line in tuples
   """

  # generate seeded binary file
  # todo: ommit binary file match


  # static values
  buffersize_of_flasher = 0x11abc
  binary_size = buffersize_of_flasher*3 + 61  # has to be greater then buffer size of flash plus a good prime number

  generate_randome_file_by_size_and_name(path_generated_file, binary_size)

  port_to_test = "-p %s" % port_to_test

  # loop values
  ## Range in which the start offset travels
  base_offset = 4096
  half_range = 16
  rel_start = -half_range
  rel_end = +half_range
  #rest = buffersize_of_flasher % (binary_size+half_range)  # {[rest...][size.....]}|blockend[....continue....size]

  start_offset = base_offset + rel_start
  end_offset =   base_offset + rel_end

  final_test_commands = []
  data = []

  ##---
  # negative test:
  tmp_offset = 0x3000
  binary_size = 434668
  generate_randome_file_by_size_and_name(path_generated_file, binary_size)
  final_test_commands.append( ["cli_flash.lua", "flash", parameters, "-s 0x%x" % tmp_offset, port_to_test, path_generated_file])
  data.append([tmp_offset,binary_size])
  # failed offset: [0x00038030] = 229424

  ##___
  # variate in parameters to get the range:
  for tmp_offset in range(start_offset, end_offset):
    # offset is the s-parameter
    tmp_command_line = ["cli_flash.lua", "flash", parameters, "-s 0x%x" % tmp_offset, port_to_test, path_generated_file]
    data.append([tmp_offset, binary_size])
    final_test_commands.append(tmp_command_line)

  for ele in data:
    print("offset %d binsize %d"%(ele[0], ele[1]))

  return final_test_commands



def convert_final_command_entries_to_commands(list_of_final_command_entries,file_prefix,flasher_binary):
  test_command_list_final = []
  print("Generate commands:")
  for idx, ele in enumerate(list_of_final_command_entries):

    # make full file path
    tmp_full_file_path = os.path.join(file_prefix, ele[0])
    list_of_final_command_entries[idx][0] = tmp_full_file_path
    # concat all to one string
    tmp_final_test_command = flasher_binary
    for int_ele in ele:
      tmp_final_test_command += " %s" % int_ele
    # append
    test_command_list_final.append(tmp_final_test_command)
    print(test_command_list_final[-1])

  return test_command_list_final


def get_hash_capeabilety(board):
  """
  Returns if a selected board ( netX) supports hash
  :param board:  a description of a single board
  :return: the value. should 0 in case no support and 1 in case of support
  """
  has_hast = board['has_hash']
  return has_hast

def get_status_long_test(final_config):
   use_cli_test = final_config["parameters"]["perform_cli_test"]
   return use_cli_test

def get_board_by_flasher_name(board_name, boards):
  """
  Input the board name and the list of boards.
  :param board_name: the flasher name of the bo
  :param boards: JSON description of all boards
  :return:
  """

  for tmp_board in boards:
    #todo: do it right with "boardname"
    name_to_check = tmp_board["chip_on_board"]
    print("Check: %s" % tmp_board)
    if name_to_check == board_name:
      board = tmp_board
      break
  else:
    print("error, no board found with expected name: %s" % board_name)
  return board

  ##

  # Sezenario 1
  # testbinary generieren
  # - folder for test binaries
  # commands generieren
  # - command list
  # - zu testzeile convertieren
  # ausfuhren
  # ergebnisse bewerten
  # result struktur muss es geben.
  # test a, b, c passed






def generate_command_list(flasher_binary,binary_file_read_from_netx,file_prefix,final_config,board_name,boards,port_to_test,path_generated_file):
  """
  todo: description
  :param flasher_binary: Path to flasher binary
  :param binary_file_read_from_netx: Name of a file, which is generated during test, where data is read to from netX mem
  :param file_prefix: logfile prefix
  :param final_config: dict representing the config json of the test
  :param board_name: here the name of the netX
  :param boards: dict representation of the avariable bords (json)
  :param port_to_test: the port, saying uart_romloader jtag_...
  :param path_generated_file: Path of binary file which is written down to test.
  :return: a array of commands
  """

  board = get_board_by_flasher_name(board_name, boards)
  has_hash = get_hash_capeabilety(board)
  use_cli_test = get_status_long_test(final_config)

  parameters = get_default_select_code_from_storage(board)
  try:
    test_name = final_config["name_test"]
    test_version = final_config["version"]
  except BaseException as e:
    l.error("Failed to retrieve test details from test-config-json")
    l.error(e)
    return -3
  
  l.info("running >%s< with version >%s<"%(test_name,test_version))
  test_binary_size = final_config["parameters"]["test_binary_size_byte"]

  # Generates a binary file on N kb's
  #todo: it does not fit super correct in here...
  # Retrieve the parameters form the dict in a region, then run the generation of commands and binary file.
  generate_randome_file_by_size_and_name(path_generated_file, test_binary_size)
  # this will execute the normal flasher routins for a general test
  # todo: add the dynamic test function somewhere, with a parameter? or so?
  # todo: add he file size for a test according to keywords: small,normal, extensive
  list_of_final_command_entries = gen_final_commands(parameters,binary_file_read_from_netx,port_to_test, test_binary_size, path_generated_file, has_hash, use_cli_test)

  test_command_list_final = convert_final_command_entries_to_commands(list_of_final_command_entries,file_prefix, flasher_binary)
  return test_command_list_final


  """
  This can be compared, also merged:
  def generate_command_list(flasher_binary,binary_file_read_from_netx,file_prefix,final_config,board_name,boards,port_to_test,path_generated_file):
  

  :param flasher_binary: Path to flasher binary
  :param binary_file_read_from_netx: Name of a file, which is generated during test, where data is read to from netX mem
  :param file_prefix: logfile prefix
  :param final_config: dict representing the config json of the test
  :param board_name: here the name of the netX
  :param boards: dict representation of the avariable bords (json)
  :param port_to_test: the port, saying uart_romloader jtag_...
  :param path_generated_file: Path of binary file which is written down to test.
  :return: a array of commands
  


  iErr = 0
  #todo: nicer!
  #todo, messae of ignoring size.
  has_hash, parameters, test_name, test_version, use_cli_test, special_test = retrieve_values_from_config_jsons(board_name, boards,
                                                                                                  final_config)

  l.info("running >%s< with version >%s<"%(test_name,test_version))
  test_binary_size = final_config["parameters"]["test_binary_size_byte"]

  if special_test:
    list_of_final_command_entries = gen_roling_write_frame_final_commands(parameters, port_to_test, path_generated_file)
  else:
    list_of_final_command_entries = gen_final_commands(parameters,binary_file_read_from_netx,port_to_test, test_binary_size, path_generated_file, has_hash, use_cli_test)

  test_command_list_final = convert_final_command_entries_to_commands(list_of_final_command_entries,file_prefix, flasher_binary)
  return test_command_list_final


def retrieve_values_from_config_jsons(board_name, boards, final_config):
  board = get_board_by_flasher_name(board_name, boards)
  has_hash = get_hash_capeabilety(board)
  use_cli_test = get_status_long_test(final_config)
  parameters = get_default_select_code_from_storage(board)
  try:
    test_name = final_config["name_test"]
    test_version = final_config["version"]
    is_special_test = final_config["parameters"]["is_special_test"]
  except BaseException as e:
    l.error("Failed to retrieve test details from test-config-json")
    l.error(e)
    assert(False)
    iErr = -3
  return has_hash, parameters, test_name, test_version, use_cli_test, is_special_test

"""




if __name__ == "__main__":
  init_json_files()
  path_generated_file = "/my/path/to/file/"
  test_command_list_final = generate_command_list(flasher_binary,final_config, "netX10", final_json["test_config"],"nen_uart_port",path_generated_file)
  print("Final commands:")
  print(test_command_list_final)


