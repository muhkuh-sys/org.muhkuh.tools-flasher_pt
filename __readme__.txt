 netX flasher
--------------


*** WARNING ***
This document is hopelessly out of date, please ignore for now...
*** WARNING ***


About

The netX flasher writes data to flash or eeprom devices. It is a standalone application (i.e. it does not require an OS like rcX or WindowsCE) which  It's main use is writing bootable images to SPI or parallel flashes, but it can also be used to:

 * write flashdisk images or application specific data
 * erase a bootable image



Prerequisites

To compile the netX flasher you need the HiTOP GCC 4.0.3 toolchain[1] and the Freetype version of the jam tool[2]. The HiTOP GCC comes with a complete installer, this should be no problem. Freetype jam is just a single ".exe" file. Either copy it to one of your search paths (like "C:\Windows"), or copy it to the "source" directory of this distribution.


Check that the HiTOP GCC is installed correctly:
Open a command line window and execute the following line:

  %PATH_GNU_ARM%bin\arm-hitex-elf-gcc --version

This output will appear if the HiTOP GCC toolchain is installed correctly:

  c:\>%PATH_GNU_ARM%bin\arm-hitex-elf-gcc --version
  arm-hitex-elf-gcc (GCC) 4.0.3
  Copyright (C) 2006 Free Software Foundation, Inc.
  This is free software; see the source for copying conditions.  There is NO
  warranty; not even for MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.


Check that Freetype jam is installed correctly:
Open a command line window, change to the location where you extracted this distribution and enter the "source" directory. Now execute the following command:

  jam.exe -v

This output will appear if Freetype jam is installed correctly:

  c:\TEMP\flasher>cd source
  c:\TEMP\flasher\source>jam.exe -v
  Jam/MR  Version 2.3.2.  Copyright 1993, 2000 Christopher Seiwald.  OS=NT.



Compile

Shortcut:
Open a command line window and change to the "source" directory of this distribution. Execute the following command, and please note that the options are case sensitive, i.e. "Release" must have an upper case "R":

  jam.bat Release all

This is the output of a successful compilation:

  C:\TEMP\flasher\source>jam.bat Release all
  C:\TEMP\flasher\source>echo off
  Found the Gnu Compiler Environment Variable 'PATH_GNU_ARM'
  Compiler is GCC with Mingw
  using NetX toolchain
  Compile conditions: Release
  ...found 80 targets...
  ...updating 26 targets...
  MkDir1 Release
  Cc Release\CFIFlash.o
  Cc Release\delay.o
  Cc Release\Drv_SpiFlash.o
  Cc Release\flasher_ext.o
  Cc Release\flasher_i2c.o
  Cc Release\flasher_spi.o
  Cc Release\flasher_srb.o
  Cc Release\Hal_SPI.o
  Cc Release\main.o
  Cc Release\netx_consoleapp.o
  Cc Release\netx_io_areas.o
  Cc Release\parflash_common.o
  Cc Release\progress_bar.o
  Cc Release\rdyrun.o
  Cc Release\Spansion.o
  Cc Release\Strata.o
  Cc Release\uart.o
  Cc Release\uprintf.o
  As Release\init_netx_test.o
  ArmLink_Elf Release\flasher.elf
  File .\flasher.elf
          1 Datei(en) kopiert.
  File .\flasher.map
          1 Datei(en) kopiert.
  ArmObjCopy_Bin Release\flasher.bin
  File ..\bin\flasher.bin
          1 Datei(en) kopiert.
  ...updated 26 targets...
  *** OK ****

The directory "bin" contains the flasher binary "flasher.bin".


Some Details:
The jam tool can be compared to the "make" tools. It checks which sources must be compiled to link the complete binary. If the project has already been compiled, it checks which sources were changed and need to be rebuild. Therefore the jam tool needs to know some details about the project. They are configured in 2 files: "Jamfile" and "Jamrules". While the "Jamrules" contain general rules how to build things (e.g. linking object files to an elf file), the "Jamfile" lists up all components for a project. These are the components for the flasher project:

  # c sources, thumb mode
  NETX_CSRCARM =
          CFIFlash.c
          delay.c
          Drv_SpiFlash.c
          flasher_ext.c
          flasher_i2c.c
          flasher_spi.c
          flasher_srb.c
          Hal_SPI.c
          main.c
          netx_consoleapp.c
          netx_io_areas.c
          parflash_common.c
          progress_bar.c
          rdyrun.c
          Spansion.c
          Strata.c
          uart.c
          uprintf.c
  ;

To add a new source which should be compiled and linked, just add your sourcefile to this list:

  # c sources, thumb mode
  NETX_CSRCARM =
          CFIFlash.c
...
          uprintf.c
          my_new_sourcefile.c
  ;

The wrapper "jam.bat" has 2 arguments. The first one is the buildmode, which is followed by the target.
The buildmode selects the compiler, assembler and linker settings. Please note that this option is case sensitive. It can be one of the following:

  Debug
  DebugRel
  Release

The "Debug" mode has no optimization ("-O0 -gdwarf-2") and contains debug information in the ".elf" file. "DebugRel" is optimized for size and still contains debug info ("-Os -gdwarf-2"). "Release" is optimized with "-O3" and contains no more debug info. "Debug" should be used while development, "Release" for the final distribution.

The 2nd argument is the target. This can be "all" or "clean". "all" builds the "elf" and "bin" files, while "clean" deletes all compiled objects (".o" files) and the "elf" and "bin" file.



Using the flasher

Using the flasher as a standalone application:

1) Download the flasher to the netx with the HiTOP debugger or the netxusbmon tool. The load address is 0x8000.
2) Write the parameters for your flash operation to a free place in the IntRam (like 0x00018000). They include:

 * device to flash the data to (Spi flash, parallel flash, etc...)
 * size of the data to flash (in bytes)
 * offset in this device (in bytes)

Below is an example for the parameters.

3) Download your data to a free ram area in the netX, preferably the SDRam. Please don't forget to set up the SDRam controller first.

4) Execute the flasher and pass the address of the parameters in the register R0. The result of the flash operation is written to the parameter field (see below), progress output is on Uart0 with 115.2k, 8N1. The execution address is 0x8000 (same as the load address).


Parameter details:
All parameters are 32 bit values (dwords). The first part of the parameter block is a general header, the second part contain the flash specific settings:

Header:
 Offset/ Meaning
 bytes
   0     Return value, 0 means success, failure otherwise (should be cleared with 0xffffffff before start)
   4     Address of the flash specific parameters.
   8     Reserved (init with 0x00000000)

Flash specific settings:
 Offset/ Meaning
 bytes
   0     parameter version
   4     operation mode
   8     start address of the data
  12     size (in bytes) of the data
  16     device typ
  20     device offset (in bytes)


Parameter Version:

The current version of the parameter block is 1.0 . The version number before the dot is the major, the part behind
the dot is the minor, so 1.0 has a major of 1 and a minor of 0. The version number is encoded in a dword as

 major * 65536 + minor

or in C terms: (major<<16)|minor
The version number 1.2 is encoded as 0x00010002.


Device Typ:

   0     reserved
   1     parallel flash on sram bus
   2     SPI flash
   3     I2C eeprom
   4     reserved
   5     reserved
   6     reserved
   7     reserved


Operation Mode:

The operation mode selects the action which is executed by the flasher tool:

 OperationMode_Flash  = 0     flash data to the device
 OperationMode_Erase  = 1     erase a region of (or the complete) the device
 OperationMode_Read   = 2     read the contents of the device
 OperationMode_Verify = 3     compare the device contents with provided data

/ clear return value
data.set 0x00018000 %LONG 0xffffffff
// set input parameter address of flasher parameter block)
data.set 0x00018004 %LONG 0x0001800c
// clear return message
data.set 0x00018008 %LONG 0x00000000

// param version
data.set 0x0001800C %LONG 0x00010000
// operation mode is flash
data.set 0x00018010 %LONG 0
// data pointer
data.set 0x00018014 %LONG 0x80000000
// data byte size
data.set 0x00018018 %LONG &binfile_size
// source type is SPI
data.set 0x0001801C %LONG &BootBlockSrcType_SPI
// dst dev offset
data.set 0x00018020 %LONG 0


Example for the parameters:
A data block of 0x3000 bytes should be flashed to the beginning of the SPI flash. The data is downloaded to the start of the SDRam. The parameter header is written to 0x00018000, the flash specific settings are placed right behind the header (0x0001800c).

    Address       Value  Meaning
 0x00018000  0xffffffff  clear return value
 0x00018004  0x0001800c  address of the flash specific parameters
 0x00018008  0x00000000  clear return message

 0x0001800c  0x00010000  parameter version is 1.0
 0x00018010  0x00000000  set operation mode to "flash data"
 0x00018014  0x80000000  pointer to the start of the data
 0x00018018  0x00003000  size of the data in bytes
 0x0001801c  0x00000002  device typ is SPI flash
 0x00018020  0x00000000  start offset in the SPI flash

After both the flasher and your data is downloaded to the netX memory and the parameters are set, load the address of the parameter block (in this example 0x00018000) into the CPU register R0 and execute the flasher at address 0x8000. When the call returns, the first entry of the parameters (the return value) contains the result of the operation. A 0 means success, other values indicate a failure. For detailed messages, connect Uart0 of the netX with a "Nullmodem Cable" to your PC and configure your COM port to 115.2K, 8 databits, no parity and 1 Stopbit (8N1).
The output of a successful flash operation looks like this:

  . *** Flasher start ***
  . Data pointer:    0x00018000
  . Init parameter:  0x0001800C

  . Application parameters:
  . data start:    0x80000000
  . data size:     0x00006020
  . boot type:     0x00000002
  . device offset: 0x00000000

  . Boot type :SPI flash
  . Detecting SPI flash...
  . ok, found AT45DB321B
  . Check size...
  . data size:  0x00006020
  . flash size: 0x00420000
  . ok, data fits into flash
  . Erase flash...
  . erase done
  . Write data...
  % 00000000/0000002F
  % 00000026/0000002F
  % 0000002F/0000002F
  . write done
  . Verify data...
  % 00000000/00000061
  % 00000061/00000061
  . verify ok
  * OK *



Contact

cthelen@hilscher.com
---
[1] HiTOP GCC 4.0.3 toolchain, download: http://www.hitex.com/download/free_software/gnu_compiler/con_gnu_compiler.html
[2] Freetype jam, download: http://www.freetype.org/jam/index.html