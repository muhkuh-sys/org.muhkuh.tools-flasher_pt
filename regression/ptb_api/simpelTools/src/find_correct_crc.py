#!/usr/bin/env python
# -*- coding: utf-8 -*-
#DIN1 = {iflash_din3_val, iflash_din2_val}
from __future__ import print_function
from __future__ import unicode_literals

import numpy as np

#input
DIN0=[None]*64
#output

def bin_array(num, m):
  """Convert a positive integer num into an m-bit bit vector"""
  result = np.array(list(np.binary_repr(num).zfill(m))).astype(np.int8)
  inverted_result = []
  for bit in reversed(result):
    inverted_result.append(bit)
  return inverted_result


def calc_rarety(DIN0):
  """
  Der Verilogcode geht davon aus, dass ich mit DIN0[0] das LSB bekomme.
  Die Zahl funf wird representiert als
  DIN[0] = 1
  DIN[1] = 0
  DIN[2] = 1
  DIN[3] = 0

  numpy gibt die bits in umgekehrter rheinfolge in pythonischer weise aus.

      np.array(list(np.binary_repr(5).zfill(4))).astype(np.int8)
      array([0, 1, 0, 1], dtype=int8)
  also:
  DIN[0]=0
  ...
  :param DIN0:
  :return:
  """
  parity_enc_a0 = [None] * 8
  parity_enc_a0[0] = DIN0[0] ^ DIN0[1] ^ DIN0[3] ^ DIN0[4] ^ DIN0[6] ^ DIN0[8] ^ DIN0[10] ^ DIN0[11] ^ DIN0[13] ^ DIN0[
    15] ^ DIN0[17] ^ DIN0[19] ^ DIN0[21] ^ DIN0[23] ^ DIN0[25] ^ DIN0[26] ^ DIN0[28] ^ DIN0[30] ^ DIN0[32] ^ DIN0[34] ^ \
                     DIN0[36] ^ DIN0[38] ^ DIN0[40] ^ DIN0[42] ^ DIN0[44] ^ DIN0[46] ^ DIN0[48] ^ DIN0[50] ^ DIN0[52] ^ \
                     DIN0[54] ^ DIN0[56] ^ DIN0[57] ^ DIN0[59] ^ DIN0[61] ^ DIN0[63]

  parity_enc_a0[1] = DIN0[0] ^ DIN0[2] ^ DIN0[3] ^ DIN0[5] ^ DIN0[6] ^ DIN0[9] ^ DIN0[10] ^ DIN0[12] ^ DIN0[13] ^ DIN0[
    16] ^ DIN0[17] ^ DIN0[20] ^ DIN0[21] ^ DIN0[24] ^ DIN0[25] ^ DIN0[27] ^ DIN0[28] ^ DIN0[31] ^ DIN0[32] ^ DIN0[35] ^ \
                     DIN0[36] ^ DIN0[39] ^ DIN0[40] ^ DIN0[43] ^ DIN0[44] ^ DIN0[47] ^ DIN0[48] ^ DIN0[51] ^ DIN0[52] ^ \
                     DIN0[55] ^ DIN0[56] ^ DIN0[58] ^ DIN0[59] ^ DIN0[62] ^ DIN0[63]

  parity_enc_a0[2] = DIN0[1] ^ DIN0[2] ^ DIN0[3] ^ DIN0[7] ^ DIN0[8] ^ DIN0[9] ^ DIN0[10] ^ DIN0[14] ^ DIN0[15] ^ DIN0[
    16] ^ DIN0[17] ^ DIN0[22] ^ DIN0[23] ^ DIN0[24] ^ DIN0[25] ^ DIN0[29] ^ DIN0[30] ^ DIN0[31] ^ DIN0[32] ^ DIN0[37] ^ \
                     DIN0[38] ^ DIN0[39] ^ DIN0[40] ^ DIN0[45] ^ DIN0[46] ^ DIN0[47] ^ DIN0[48] ^ DIN0[53] ^ DIN0[54] ^ \
                     DIN0[55] ^ DIN0[56] ^ DIN0[60] ^ DIN0[61] ^ DIN0[62] ^ DIN0[63]

  parity_enc_a0[3] = DIN0[4] ^ DIN0[5] ^ DIN0[6] ^ DIN0[7] ^ DIN0[8] ^ DIN0[9] ^ DIN0[10] ^ DIN0[18] ^ DIN0[19] ^ DIN0[
    20] ^ DIN0[21] ^ DIN0[22] ^ DIN0[23] ^ DIN0[24] ^ DIN0[25] ^ DIN0[33] ^ DIN0[34] ^ DIN0[35] ^ DIN0[36] ^ DIN0[37] ^ \
                     DIN0[38] ^ DIN0[39] ^ DIN0[40] ^ DIN0[49] ^ DIN0[50] ^ DIN0[51] ^ DIN0[52] ^ DIN0[53] ^ DIN0[54] ^ \
                     DIN0[55] ^ DIN0[56]

  parity_enc_a0[4] = DIN0[11] ^ DIN0[12] ^ DIN0[13] ^ DIN0[14] ^ DIN0[15] ^ DIN0[16] ^ DIN0[17] ^ DIN0[18] ^ DIN0[19] ^ \
                     DIN0[20] ^ DIN0[21] ^ DIN0[22] ^ DIN0[23] ^ DIN0[24] ^ DIN0[25] ^ DIN0[41] ^ DIN0[42] ^ DIN0[43] ^ \
                     DIN0[44] ^ DIN0[45] ^ DIN0[46] ^ DIN0[47] ^ DIN0[48] ^ DIN0[49] ^ DIN0[50] ^ DIN0[51] ^ DIN0[52] ^ \
                     DIN0[53] ^ DIN0[54] ^ DIN0[55] ^ DIN0[56]

  parity_enc_a0[5] = DIN0[26] ^ DIN0[27] ^ DIN0[28] ^ DIN0[29] ^ DIN0[30] ^ DIN0[31] ^ DIN0[32] ^ DIN0[33] ^ DIN0[34] ^ \
                     DIN0[35] ^ DIN0[36] ^ DIN0[37] ^ DIN0[38] ^ DIN0[39] ^ DIN0[40] ^ DIN0[41] ^ DIN0[42] ^ DIN0[43] ^ \
                     DIN0[44] ^ DIN0[45] ^ DIN0[46] ^ DIN0[47] ^ DIN0[48] ^ DIN0[49] ^ DIN0[50] ^ DIN0[51] ^ DIN0[52] ^ \
                     DIN0[53] ^ DIN0[54] ^ DIN0[55] ^ DIN0[56]

  parity_enc_a0[6] = DIN0[57] ^ DIN0[58] ^ DIN0[59] ^ DIN0[60] ^ DIN0[61] ^ DIN0[62] ^ DIN0[63]

  parity_enc_a0[7] = DIN0[0] ^ DIN0[1] ^ DIN0[2] ^ DIN0[4] ^ DIN0[5] ^ DIN0[7] ^ DIN0[10] ^ DIN0[11] ^ DIN0[12] ^ DIN0[
    14] ^ DIN0[17] ^ DIN0[18] ^ DIN0[21] ^ DIN0[23] ^ DIN0[24] ^ DIN0[26] ^ DIN0[27] ^ DIN0[29] ^ DIN0[32] ^ DIN0[33] ^ \
                     DIN0[36] ^ DIN0[38] ^ DIN0[39] ^ DIN0[41] ^ DIN0[44] ^ DIN0[46] ^ DIN0[47] ^ DIN0[50] ^ DIN0[51] ^ \
                     DIN0[53] ^ DIN0[56] ^ DIN0[57] ^ DIN0[58] ^ DIN0[60] ^ DIN0[63]
  return parity_enc_a0


def generate_CRC_from_input_int(input_int):
  size=64
  binary_inverse_representation = bin_array(input_int, size)

  CRC = calc_rarety(binary_inverse_representation)

  return CRC




def compare_two_crcs_good(CRC_A,CRC_B):
  """
  Find combinations which pass the CRC test
  :param CRC_A: first checksum
  :param CRC_B: second checksum
  :return: 0 in case this test is passed!
  """

  assert len(CRC_A) == len(CRC_B)

  for idx, ele in enumerate ( CRC_A):


    A = CRC_A[idx]
    B = CRC_B[idx]
    #if CRC_A[idx] != CRC_B[idx]:   # Hard dependency
    #if CRC_A[idx] == 0 and CRC_B[idx] == 1:  # Soft dependence, which will be tolerated by flash behaviour
    if CRC_A[idx] == 0 and CRC_B[idx] == 1:
      # this simulates a faulty bitflip from 0 back to one which can't be executed in a flash!
      return -1
  else:
    return 0

def compare_two_crcs(CRC_previous, CRC_next):
  """
  Find combinations which will fail every CRC-Test
  :param CRC_A: first checksum
  :param CRC_B: second checksum
  :return: 0 in case this test is passed!
  """
  qualety = 0
  assert len(CRC_previous) == len(CRC_next)

  for idx, ele in enumerate(CRC_previous):

    A = CRC_previous[idx]
    B = CRC_next[idx]
    if CRC_previous[idx] == 0 and CRC_next[idx] == 1:
      # if we have at least one "wrong" bitflip from 0 -> 1 this is a good binary example
      qualety +=1
      if qualety >2:
        return 0
  else:
    return -1

  #----



def run_search():

  count_founds = 0
  count_misses = 0
  count_seed2_found = 0
  count_total = 0

  #seed_range = range(0, 0x100)
  seed_range = range(0x12, 0x100)

  #for seed1 in seed_range:
  for seed1 in seed_range:
    # gen input:
    input1 = 0xFFFFFF00 | seed1
    CRC1 = generate_CRC_from_input_int(input1)

    for seed2 in seed_range:
      #print("1(%d)" % seed1, end='')
      input2 = 0xFFFF0000 | seed2 << 8 | seed1
      CRC2 = generate_CRC_from_input_int(input2)
      count_total += 1
      if 0 == compare_two_crcs(CRC1,CRC2):
        count_seed2_found += 1
        #continue # enable for only one iteration

        #print("- 2(%d)" % seed2, end='')
        for seed3 in seed_range:
          input3 = 0xFF000000 | seed3 << 16 | seed2 << 8 | seed1
          CRC3 = generate_CRC_from_input_int(input3)

          if 0 == compare_two_crcs(CRC2, CRC3):
            #print("- 3(%d)"%seed3, end='')
            for seed4 in seed_range:
              input4 = seed4 << 24 | seed3 << 16 | seed2 << 8 | seed1
              CRC4 = generate_CRC_from_input_int(input4)

              if 0 == compare_two_crcs(CRC3, CRC4):
                count_founds += 1
                #print("- 4(%d) - found!" % seed3)
                print("[%06x]Found 0x %02x %02x %02x %02x" % (count_founds,seed4, seed3, seed2, seed1))
                print("input1 0x%x" % input1, CRC1)
                print("input2 0x%x" % input2, CRC2)
                print("input3 0x%x" % input3, CRC3)
                print("input4 0x%x" % input4, CRC4)


            else:
              #print("- nope 4")
              a=1
          #print("- scip 3")
        else:
          a = 1
          #print("- nope 3")
      #print("- scip 2")
    else:
      a = 1
      #print("- nope 2")

  print("Found %d hashes"%count_founds)
  print("Count seed 2 found %d"%count_seed2_found)
  print("Count total %d"%count_total)


def generate_binary_file():
  """
  At least 3 bits flipping out!
  [000005]Found 0x 38 31 1e 13
  input1 0xffffff13 [0, 0, 1, 0, 1, 0, 0, 1]
  input2 0xffff1e13 [1, 1, 0, 1, 0, 0, 0, 0]
  input3 0xff311e13 [0, 0, 1, 1, 1, 0, 0, 1]
  input4 0x38311e13 [1, 1, 1, 1, 1, 1, 0, 1]
  :return:
  """

  array_of_bytes = bytearray(reversed([0x38, 0x31, 0x1e, 0x13]))
  newFile = open("filename_reverse.txt", "wb")
  blocksize_flash = 0x11abc
  for _ in range(0,blocksize_flash):
    newFile.write(array_of_bytes)


generate_binary_file()
#run_search()





  # take seed
  # 0xFFFFFF00|seed
  # It 1:
  # run -> CRC1
  # It 2:
  # 0xFFFF0000 | (seed & 0x000000FF) | (seed2<<8*it)




"""
parity_enc_a1[0] = DIN1[0] ^ DIN1[1] ^ DIN1[3] ^ DIN1[4] ^ DIN1[6] ^ DIN1[8] ^ DIN1[10] ^ DIN1[11] ^ DIN1[13] ^ DIN1[
  15] ^ DIN1[17] ^ DIN1[19] ^ DIN1[21] ^ DIN1[23] ^ DIN1[25] ^ DIN1[26] ^ DIN1[28] ^ DIN1[30] ^ DIN1[32] ^ DIN1[34] ^ \
                   DIN1[36] ^ DIN1[38] ^ DIN1[40] ^ DIN1[42] ^ DIN1[44] ^ DIN1[46] ^ DIN1[48] ^ DIN1[50] ^ DIN1[52] ^ \
                   DIN1[54] ^ DIN1[56] ^ DIN1[57] ^ DIN1[59] ^ DIN1[61] ^ DIN1[63]

parity_enc_a1[1] = DIN1[0] ^ DIN1[2] ^ DIN1[3] ^ DIN1[5] ^ DIN1[6] ^ DIN1[9] ^ DIN1[10] ^ DIN1[12] ^ DIN1[13] ^ DIN1[
  16] ^ DIN1[17] ^ DIN1[20] ^ DIN1[21] ^ DIN1[24] ^ DIN1[25] ^ DIN1[27] ^ DIN1[28] ^ DIN1[31] ^ DIN1[32] ^ DIN1[35] ^ \
                   DIN1[36] ^ DIN1[39] ^ DIN1[40] ^ DIN1[43] ^ DIN1[44] ^ DIN1[47] ^ DIN1[48] ^ DIN1[51] ^ DIN1[52] ^ \
                   DIN1[55] ^ DIN1[56] ^ DIN1[58] ^ DIN1[59] ^ DIN1[62] ^ DIN1[63]

parity_enc_a1[2] = DIN1[1] ^ DIN1[2] ^ DIN1[3] ^ DIN1[7] ^ DIN1[8] ^ DIN1[9] ^ DIN1[10] ^ DIN1[14] ^ DIN1[15] ^ DIN1[
  16] ^ DIN1[17] ^ DIN1[22] ^ DIN1[23] ^ DIN1[24] ^ DIN1[25] ^ DIN1[29] ^ DIN1[30] ^ DIN1[31] ^ DIN1[32] ^ DIN1[37] ^ \
                   DIN1[38] ^ DIN1[39] ^ DIN1[40] ^ DIN1[45] ^ DIN1[46] ^ DIN1[47] ^ DIN1[48] ^ DIN1[53] ^ DIN1[54] ^ \
                   DIN1[55] ^ DIN1[56] ^ DIN1[60] ^ DIN1[61] ^ DIN1[62] ^ DIN1[63]

parity_enc_a1[3] = DIN1[4] ^ DIN1[5] ^ DIN1[6] ^ DIN1[7] ^ DIN1[8] ^ DIN1[9] ^ DIN1[10] ^ DIN1[18] ^ DIN1[19] ^ DIN1[
  20] ^ DIN1[21] ^ DIN1[22] ^ DIN1[23] ^ DIN1[24] ^ DIN1[25] ^ DIN1[33] ^ DIN1[34] ^ DIN1[35] ^ DIN1[36] ^ DIN1[37] ^ \
                   DIN1[38] ^ DIN1[39] ^ DIN1[40] ^ DIN1[49] ^ DIN1[50] ^ DIN1[51] ^ DIN1[52] ^ DIN1[53] ^ DIN1[54] ^ \
                   DIN1[55] ^ DIN1[56]

parity_enc_a1[4] = DIN1[11] ^ DIN1[12] ^ DIN1[13] ^ DIN1[14] ^ DIN1[15] ^ DIN1[16] ^ DIN1[17] ^ DIN1[18] ^ DIN1[19] ^ \
                   DIN1[20] ^ DIN1[21] ^ DIN1[22] ^ DIN1[23] ^ DIN1[24] ^ DIN1[25] ^ DIN1[41] ^ DIN1[42] ^ DIN1[43] ^ \
                   DIN1[44] ^ DIN1[45] ^ DIN1[46] ^ DIN1[47] ^ DIN1[48] ^ DIN1[49] ^ DIN1[50] ^ DIN1[51] ^ DIN1[52] ^ \
                   DIN1[53] ^ DIN1[54] ^ DIN1[55] ^ DIN1[56]

parity_enc_a1[5] = DIN1[26] ^ DIN1[27] ^ DIN1[28] ^ DIN1[29] ^ DIN1[30] ^ DIN1[31] ^ DIN1[32] ^ DIN1[33] ^ DIN1[34] ^ \
                   DIN1[35] ^ DIN1[36] ^ DIN1[37] ^ DIN1[38] ^ DIN1[39] ^ DIN1[40] ^ DIN1[41] ^ DIN1[42] ^ DIN1[43] ^ \
                   DIN1[44] ^ DIN1[45] ^ DIN1[46] ^ DIN1[47] ^ DIN1[48] ^ DIN1[49] ^ DIN1[50] ^ DIN1[51] ^ DIN1[52] ^ \
                   DIN1[53] ^ DIN1[54] ^ DIN1[55] ^ DIN1[56]

parity_enc_a1[6] = DIN1[57] ^ DIN1[58] ^ DIN1[59] ^ DIN1[60] ^ DIN1[61] ^ DIN1[62] ^ DIN1[63]

parity_enc_a1[7] = DIN1[0] ^ DIN1[1] ^ DIN1[2] ^ DIN1[4] ^ DIN1[5] ^ DIN1[7] ^ DIN1[10] ^ DIN1[11] ^ DIN1[12] ^ DIN1[
  14] ^ DIN1[17] ^ DIN1[18] ^ DIN1[21] ^ DIN1[23] ^ DIN1[24] ^ DIN1[26] ^ DIN1[27] ^ DIN1[29] ^ DIN1[32] ^ DIN1[33] ^ \
                   DIN1[36] ^ DIN1[38] ^ DIN1[39] ^ DIN1[41] ^ DIN1[44] ^ DIN1[46] ^ DIN1[47] ^ DIN1[50] ^ DIN1[51] ^ \
                   DIN1[53] ^ DIN1[56] ^ DIN1[57] ^ DIN1[58] ^ DIN1[60] ^ DIN1[63]
"""
