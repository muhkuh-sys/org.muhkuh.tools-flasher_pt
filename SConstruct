# -*- coding: utf-8 -*-
#-------------------------------------------------------------------------#
#   Copyright (C) 2011 by Christoph Thelen                                #
#   doc_bacardi@users.sourceforge.net                                     #
#                                                                         #
#   This program is free software; you can redistribute it and/or modify  #
#   it under the terms of the GNU General Public License as published by  #
#   the Free Software Foundation; either version 2 of the License, or     #
#   (at your option) any later version.                                   #
#                                                                         #
#   This program is distributed in the hope that it will be useful,       #
#   but WITHOUT ANY WARRANTY; without even the implied warranty of        #
#   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         #
#   GNU General Public License for more details.                          #
#                                                                         #
#   You should have received a copy of the GNU General Public License     #
#   along with this program; if not, write to the                         #
#   Free Software Foundation, Inc.,                                       #
#   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.             #
#-------------------------------------------------------------------------#


#----------------------------------------------------------------------------
#
# Set up the Muhkuh Build System.
#

SConscript('mbs/SConscript')
Import('env_default')

#----------------------------------------------------------------------------
# This is the list of sources. The elements must be separated with whitespace
# (i.e. spaces, tabs, newlines). The amount of whitespace does not matter.
flasher_sources_common = """
	src/cfi_flash.c
	src/delay.c
	src/spi_flash.c
	src/flasher_parflash.c
	src/flasher_spi.c
	src/i2c_hifsta.c
	src/init_netx_test.S
	src/main.c
	src/netx_consoleapp.c
	src/progress_bar.c
	src/rdyrun.c
	src/spansion.c
	src/spi_flash_types.c
	src/startvector.s
	src/strata.c
	src/systime.c
	src/units.c
	src/uprintf.c
	src/sha1_arm/sha1.c
	src/sha1_arm/sha1_arm.S
"""

flasher_sources_custom_netx500 = """
	src/netx500/board.c
	src/netx500/flasher_header.c
	src/netx500/netx500_io_areas.c
	src/drv_spi_hsoc_v1.c
"""


flasher_sources_custom_netx50 = """
	src/netx50/board.c
	src/netx50/flasher_header.c
	src/netx50/netx50_io_areas.c
	src/drv_spi_hsoc_v2.c
	src/mmio.c
"""


flasher_sources_custom_netx10 = """
	src/netx10/board.c
	src/netx10/flasher_header.c
	src/netx10/netx10_io_areas.c
	src/drv_spi_hsoc_v2.c
	src/drv_sqi.c
	src/mmio.c
"""

src_netx500 = Split(flasher_sources_common + flasher_sources_custom_netx500)
src_netx50  = Split(flasher_sources_common + flasher_sources_custom_netx50)
src_netx10  = Split(flasher_sources_common + flasher_sources_custom_netx10)


#----------------------------------------------------------------------------
#
# Create a special filter builder which includes the svnversion command.
#
env_default.SVNVersion('src/flasher_version.h', 'templates/flasher_version.h')


#----------------------------------------------------------------------------
#
# Create the compiler environments.
#

env_default.Append(CPPDEFINES = [['CFG_INCLUDE_SHA1', '1']])

env_netx500_default = env_default.CreateCompilerEnv('500', 'arm926ej-s')
env_netx500_default.Replace(LDFILE = File('src/netx500/netx500.ld'))
env_netx500_default.Append(CPPPATH = ['src', 'src/netx500', 'src/sha1_arm'])

env_netx50_default  = env_default.CreateCompilerEnv('50',  'arm966e-s')
env_netx50_default.Replace(LDFILE = File('src/netx50/netx50.ld'))
env_netx50_default.Append(CPPPATH = ['src', 'src/netx50', 'src/sha1_arm'])

env_netx10_default  = env_default.CreateCompilerEnv('10',  'arm966e-s')
env_netx10_default.Replace(LDFILE = File('src/netx10/netx10.ld'))
env_netx10_default.Append(CPPPATH = ['src', 'src/netx10', 'src/sha1_arm'])


#----------------------------------------------------------------------------
#
# Build the flasher without debug messages.
#
env_netx500_nodbg = env_netx500_default.Clone()
env_netx500_nodbg.Append(CPPDEFINES = [['CFG_DEBUGMSG', '0']])
src_netx500_nodbg = env_netx500_nodbg.SetBuildPath('targets/netx500_nodbg', 'src', src_netx500)
elf_netx500_nodbg = env_netx500_nodbg.Elf('targets/flasher_netx500.elf', src_netx500_nodbg)
bin_netx500_nodbg = env_netx500_nodbg.ObjCopy('targets/flasher_netx500.bin', elf_netx500_nodbg)

env_netx50_nodbg = env_netx50_default.Clone()
env_netx50_nodbg.Append(CPPDEFINES = [['CFG_DEBUGMSG', '0']])
src_netx50_nodbg = env_netx50_nodbg.SetBuildPath('targets/netx50_nodbg', 'src', src_netx50)
elf_netx50_nodbg = env_netx50_nodbg.Elf('targets/flasher_netx50.elf', src_netx50_nodbg)
bin_netx50_nodbg = env_netx50_nodbg.ObjCopy('targets/flasher_netx50.bin', elf_netx50_nodbg)

env_netx10_nodbg = env_netx10_default.Clone()
env_netx10_nodbg.Append(CPPDEFINES = [['CFG_DEBUGMSG', '0']])
src_netx10_nodbg = env_netx10_nodbg.SetBuildPath('targets/netx10_nodbg', 'src', src_netx10)
elf_netx10_nodbg = env_netx10_nodbg.Elf('targets/flasher_netx10.elf', src_netx10_nodbg)
bin_netx10_nodbg = env_netx10_nodbg.ObjCopy('targets/flasher_netx10.bin', elf_netx10_nodbg)


#----------------------------------------------------------------------------
#
# Build the flasher with debug messages.
#

env_netx500_dbg = env_netx500_default.Clone()
env_netx500_dbg.Append(CPPDEFINES = [['CFG_DEBUGMSG', '1']])
src_netx500_dbg = env_netx500_dbg.SetBuildPath('targets/netx500_dbg', 'src', src_netx500)
elf_netx500_dbg = env_netx500_dbg.Elf('targets/flasher_netx500_debug.elf', src_netx500_dbg)
bin_netx500_dbg = env_netx500_dbg.ObjCopy('targets/flasher_netx500_debug.bin', elf_netx500_dbg)

env_netx50_dbg = env_netx50_default.Clone()
env_netx50_dbg.Append(CPPDEFINES = [['CFG_DEBUGMSG', '1']])
src_netx50_dbg = env_netx50_dbg.SetBuildPath('targets/netx50_dbg', 'src', src_netx50)
elf_netx50_dbg = env_netx50_dbg.Elf('targets/flasher_netx50_debug.elf', src_netx50_dbg)
bin_netx50_dbg = env_netx50_dbg.ObjCopy('targets/flasher_netx50_debug.bin', elf_netx50_dbg)

env_netx10_dbg = env_netx10_default.Clone()
env_netx10_dbg.Append(CPPDEFINES = [['CFG_DEBUGMSG', '1']])
src_netx10_dbg = env_netx10_dbg.SetBuildPath('targets/netx10_dbg', 'src', src_netx10)
elf_netx10_dbg = env_netx10_dbg.Elf('targets/flasher_netx10_debug.elf', src_netx10_dbg)
bin_netx10_dbg = env_netx10_dbg.ObjCopy('targets/flasher_netx10_debug.bin', elf_netx10_dbg)


#----------------------------------------------------------------------------
#
# Build the documentation.
#
env_default.Asciidoc('targets/doc/flasher.html', 'doc/flasher.txt')
