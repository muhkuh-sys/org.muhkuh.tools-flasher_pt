# coding=utf-8
import os
from simpelTools.src.logging_default import *



def strip_command_arguments(str_command_line_arguments):
  single_arguments = str_command_line_arguments.split()
  stripped_string = ''
  for ele in single_arguments:
    stripped_string += " %s"%os.path.basename(ele)

  return stripped_string[1:]


def test_strip_command_arguments():
  full = "/my/bin/path.bin  /may/file/path/my.file -p 1234_.ksdnb -b0"

  stripped = strip_command_arguments(full)

  print(">%s<"%stripped)

  assert("path.bin my.file -p 1234_.ksdnb -b0" == stripped)


def helper_type_conversion(input_string):
  test1 = 'äöü'
  test2 = b'\xe4\xf6\xfc'
  test3 = u'äöü'
  """
  Converts every input to unicode. tested with testcases abouve!
  :param input_string: may be a string or unicode or bytes.
  :return: returns unicode
  """

  l.debug("type: %s\n message:%s" % (type(input_string), input_string))
  if type(input_string) is not unicode:
    # i don't need to decode unicode. because it already is!
    output_string = input_string.decode("utf-8")  # converts bytes to unicode
  else:
    output_string = input_string
  return output_string



"""
python 3 version by (https://codereview.stackexchange.com/questions/229909/universal-string-conversion)
def all_eating_unicode_converter(input_string):
   
    Converts every input to unicode.
    :param input_string: may be a string or unicode or bytes.
    :return: returns unicode

    Tested with: 'äöü', b'\xc3\xa4\xc3\xb6\xc3\xbc', u'äöü'
   
    if isinstance(input_string, bytes):
        return input_string.decode("utf-8")
    return input_string"""


if __name__ == "__main__":
  test_strip_command_arguments()


