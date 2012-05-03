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
	src/drv_spi_hsoc_v1.c
"""


flasher_sources_custom_netx56 = """
	src/netx56/board.c
	src/netx56/flasher_header.c
	src/drv_spi_hsoc_v2.c
	src/drv_sqi.c
	src/mmio.c
"""


flasher_sources_custom_netx50 = """
	src/netx50/board.c
	src/netx50/flasher_header.c
	src/drv_spi_hsoc_v2.c
	src/mmio.c
"""


flasher_sources_custom_netx10 = """
	src/netx10/board.c
	src/netx10/flasher_header.c
	src/drv_spi_hsoc_v2.c
	src/drv_sqi.c
	src/mmio.c
"""

src_netx500 = flasher_sources_common + flasher_sources_custom_netx500
src_netx56  = flasher_sources_common + flasher_sources_custom_netx56
src_netx50  = flasher_sources_common + flasher_sources_custom_netx50
src_netx10  = flasher_sources_common + flasher_sources_custom_netx10


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

env_netx500_default = env_default.CreateCompilerEnv('500', ['arch=armv5te'])
env_netx500_default.Replace(LDFILE = File('src/netx500/netx500.ld'))
env_netx500_default.Append(CPPPATH = ['src', 'src/netx500', 'src/sha1_arm'])

env_netx56_default  = env_default.CreateCompilerEnv('56',  ['arch=armv5te'])
env_netx56_default.Replace(LDFILE = File('src/netx56/netx56.ld'))
env_netx56_default.Append(CPPPATH = ['src', 'src/netx56', 'src/sha1_arm'])

env_netx50_default  = env_default.CreateCompilerEnv('50',  ['arch=armv5te'])
env_netx50_default.Replace(LDFILE = File('src/netx50/netx50.ld'))
env_netx50_default.Append(CPPPATH = ['src', 'src/netx50', 'src/sha1_arm'])

env_netx10_default  = env_default.CreateCompilerEnv('10',  ['arch=armv5te'])
env_netx10_default.Replace(LDFILE = File('src/netx10/netx10.ld'))
env_netx10_default.Append(CPPPATH = ['src', 'src/netx10', 'src/sha1_arm'])


#----------------------------------------------------------------------------
#
# Build the netX10 flasher with the old netX50 console io interface.
#
env_netx10_oldio_nodbg = env_netx10_default.Clone()
env_netx10_oldio_nodbg.Replace(LDFILE = File('src/netx10/netx10_oldio.ld'))
env_netx10_oldio_nodbg.Append(CPPDEFINES = [['CFG_DEBUGMSG', '0']])
src_netx10_oldio_nodbg = env_netx10_oldio_nodbg.SetBuildPath('targets/netx10_oldio_nodbg', 'src', src_netx10)
elf_netx10_oldio_nodbg = env_netx10_oldio_nodbg.Elf('targets/oldio/flasher_netx10.elf', src_netx10_oldio_nodbg)
bin_netx10_oldio_nodbg = env_netx10_oldio_nodbg.ObjCopy('targets/oldio/flasher_netx10.bin', elf_netx10_oldio_nodbg)

env_netx10_oldio_dbg = env_netx10_default.Clone()
env_netx10_oldio_dbg.Replace(LDFILE = File('src/netx10/netx10_oldio.ld'))
env_netx10_oldio_dbg.Append(CPPDEFINES = [['CFG_DEBUGMSG', '1']])
src_netx10_oldio_dbg = env_netx10_oldio_dbg.SetBuildPath('targets/netx10_oldio_dbg', 'src', src_netx10)
elf_netx10_oldio_dbg = env_netx10_oldio_dbg.Elf('targets/oldio/flasher_netx10_debug.elf', src_netx10_oldio_dbg)
bin_netx10_oldio_dbg = env_netx10_oldio_dbg.ObjCopy('targets/oldio/flasher_netx10_debug.bin', elf_netx10_oldio_dbg)


#----------------------------------------------------------------------------
#
# Build the flasher without debug messages.
#
env_netx500_nodbg = env_netx500_default.Clone()
env_netx500_nodbg.Append(CPPDEFINES = [['CFG_DEBUGMSG', '0']])
src_netx500_nodbg = env_netx500_nodbg.SetBuildPath('targets/netx500_nodbg', 'src', src_netx500)
elf_netx500_nodbg = env_netx500_nodbg.Elf('targets/flasher_netx500.elf', src_netx500_nodbg)
bin_netx500_nodbg = env_netx500_nodbg.ObjCopy('targets/flasher_netx500.bin', elf_netx500_nodbg)

env_netx56_nodbg = env_netx56_default.Clone()
env_netx56_nodbg.Append(CPPDEFINES = [['CFG_DEBUGMSG', '0']])
src_netx56_nodbg = env_netx56_nodbg.SetBuildPath('targets/netx56_nodbg', 'src', src_netx56)
elf_netx56_nodbg = env_netx56_nodbg.Elf('targets/flasher_netx56.elf', src_netx56_nodbg)
bin_netx56_nodbg = env_netx56_nodbg.ObjCopy('targets/flasher_netx56.bin', elf_netx56_nodbg)

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

env_netx56_dbg = env_netx56_default.Clone()
env_netx56_dbg.Append(CPPDEFINES = [['CFG_DEBUGMSG', '1']])
src_netx56_dbg = env_netx56_dbg.SetBuildPath('targets/netx56_dbg', 'src', src_netx56)
elf_netx56_dbg = env_netx56_dbg.Elf('targets/flasher_netx56_debug.elf', src_netx56_dbg)
bin_netx56_dbg = env_netx56_dbg.ObjCopy('targets/flasher_netx56_debug.bin', elf_netx56_dbg)

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
doc = env_default.Asciidoc('targets/doc/flasher.html', 'doc/flasher.txt')


#----------------------------------------------------------------------------
#
# Build the distribution.
#

tArcList = env_default.ArchiveList('zip')

tArcList.AddFiles('bin/',
	bin_netx500_nodbg,
	bin_netx56_nodbg,
	bin_netx50_nodbg,
	bin_netx10_nodbg)

tArcList.AddFiles('bin/debug/',
	bin_netx500_dbg,
	bin_netx56_dbg,
	bin_netx50_dbg,
	bin_netx10_dbg)

tArcList.AddFiles('doc/',
	doc)

tArcList.AddFiles('lua/',
	'testbench/cli_flash.lua',
	'testbench/flasher.lua',
	'testbench/demo_getBoardInfo.lua',
	'testbench/erase_complete_flash.lua',
	'testbench/erase_first_flash_sector.lua',
	'testbench/flash_parflash.lua',
	'testbench/flash_serflash.lua',
	'testbench/flasher_test.lua',
	'testbench/get_erase_areas_parflash.lua',
	'testbench/identify_parflash.lua',
	'testbench/identify_serflash.lua',
	'testbench/is_erased_parflash.lua')

tArc = env_default.Archive('targets/flasher.zip', None, ARCHIVE_CONTENTS=tArcList)


#----------------------------------------------------------------------------
#
# Create the artifact list.
#

strPomGroupID    = 'net.sourceforge.muhkuh'
strPomArtifactID = 'flasher'
strPomPackaging  = 'zip'

# Add the LUA file to the list of artifacts.
env_default.AddArtifact(tArc, strPomGroupID, strPomArtifactID, strPomPackaging)

tArtifacts = env_default.Artifact('targets/artifacts.xml', None)


