# -*- coding: utf-8 -*-

# TODO:
#  * more than one system include dir (for arg parsing etc)
#  * set a default location for the compiler dir (but where could this be?)
#
# Done:
#  * print help even if the site dir for the compiler stuff is missing.
#  * generate relocated sources from list of real locations
#  * set compiler flags from build properties
#  * show command line summary (e.g. "Cc blah.o") for the actions, but show complete line if the command failed.
#  * accept 'clean' target like make
#  * auto dependency for LDFILE
#

import scons_common
import build_properties
import svnversion
import uuencode

build_properties.Read()

#----------------------------------------------------------------------------
#
# set help text
#
Help("""
	Set the compiler dir with all the gcc_*.py files with --site-dir=path .
	Example: The compiler dir is usually in the folder '.ant' in the users home directory.
	This expands for the user 'brunhild' to '/home/brunhild/.ant'.

	Type: 'scons --site-dir=compiler_dir' to build the production program,
	      'scons --site-dir=compiler_dir clean' to clean everything.
""")

build_properties.GenerateHelp()


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
	src/mmio.c
	src/netx_consoleapp.c
	src/progress_bar.c
	src/rdyrun.c
	src/spansion.c
	src/spi_flash_types.c
	src/startvector.s
	src/strata.c
	src/systime.c
	src/uprintf.c
"""


flasher_sources_custom_netx500 = """
	src/netx500/board.c
	src/netx500/flasher_header.c
	src/netx500/hal_spi.c
	src/netx500/netx500_io_areas.c
"""


flasher_sources_custom_netx50 = """
	src/netx50/board.c
	src/netx50/flasher_header.c
	src/netx50/hal_spi.c
	src/netx50/netx50_io_areas.c
"""


flasher_sources_custom_netx10 = """
	src/netx10/board.c
	src/netx10/drv_spi.c
	src/netx10/drv_sqi.c
	src/netx10/flasher_header.c
	src/netx10/spi.c
	src/netx10/netx10_io_areas.c
"""

src_netx500 = Split(flasher_sources_common + flasher_sources_custom_netx500)
src_netx50  = Split(flasher_sources_common + flasher_sources_custom_netx50)
src_netx10  = Split(flasher_sources_common + flasher_sources_custom_netx10)


default_ccflags = """
	-ffreestanding
	-mlong-calls
	-Wall
	-Wextra
	-Wconversion
	-Wshadow
	-Wcast-qual
	-Wwrite-strings
	-Wcast-align
	-Wpointer-arith
	-Wmissing-prototypes
	-Wstrict-prototypes
	-mapcs
	-g3
	-gdwarf-2
	-std=iso9899:1999
	-pedantic
"""

#----------------------------------------------------------------------------
# Only execute this part if the help text is not requested.
# This keeps the help message functional even if no include path for the
# compiler definitions was specified.
if not GetOption('help'):
	# Show summary of the build properties.
	build_properties.PrintSummary()
	
	
	#----------------------------------------------------------------------------
	#
	# Import the tool definitions.
	#
	# NOTE: it would be possible to use execfile instead of import here. This
	gcc_arm_elf_4_3_3_3 = scons_common.get_compiler('gcc_arm_elf_4_3_3_3')
	asciidoc_8_5_3_1 = scons_common.get_asciidoc('asciidoc_8_5_3_1')
	
	
	#----------------------------------------------------------------------------
	#
	# create the default environment
	#
	env_default = Environment()
	gcc_arm_elf_4_3_3_3.ApplyToEnv(env_default)
	env_default.Decider('MD5')
	env_default.Append(CPPPATH = ['src'])
	env_default.Replace(CCFLAGS = Split(default_ccflags))
	env_default.Replace(LIBS = ['m', 'c', 'gcc'])
	env_default.Replace(LINKFLAGS = ['-nostdlib', '-static', '-Map=${TARGET}.map'])
	
	asciidoc_8_5_3_1.ApplyToEnv(env_default)
	build_properties.ApplyToEnv(env_default)
	svnversion.ApplyToEnv(env_default)
	uuencode.ApplyToEnv(env_default)
	
	
	#----------------------------------------------------------------------------
	#
	# Create a special filter builder which includes the svnversion command.
	#
	env_default.SVNVersion('src/flasher_version.h', 'templates/flasher_version.h')
	
	# create environments for all builds
	env_netx500 = env_default.Clone()
	env_netx500.Append(CCFLAGS = ['-mcpu=arm926ej-s'])
	env_netx500.Replace(LDFILE = 'src/netx500/netx500.ld')
	env_netx500.Replace(LIBPATH = ['${GCC_DIR}/arm-elf/lib/arm926ej-s', '${GCC_DIR}/lib/gcc/arm-elf/${GCC_VERSION}/arm926ej-s'])
	env_netx500.Append(CPPDEFINES = [['ASIC_TYP', '500']])
	env_netx500.Append(CPPPATH = ['src/netx500'])
	
	env_netx50 = env_default.Clone()
	env_netx50.Append(CCFLAGS = ['-mcpu=arm966e-s'])
	env_netx50.Replace(LDFILE = 'src/netx50/netx50.ld')
	env_netx50.Replace(LIBPATH = ['${GCC_DIR}/arm-elf/lib/arm966e-s', '${GCC_DIR}/lib/gcc/arm-elf/${GCC_VERSION}/arm966e-s'])
	env_netx50.Append(CPPDEFINES = [['ASIC_TYP', '50']])
	env_netx50.Append(CPPPATH = ['src/netx50'])
	
	env_netx10 = env_default.Clone()
	env_netx10.Append(CCFLAGS = ['-mcpu=arm966e-s'])
	env_netx10.Replace(LDFILE = 'src/netx10/netx10.ld')
	env_netx10.Replace(LIBPATH = ['${GCC_DIR}/arm-elf/lib/arm966e-s', '${GCC_DIR}/lib/gcc/arm-elf/${GCC_VERSION}/arm966e-s'])
	env_netx10.Append(CPPDEFINES = [['ASIC_TYP', '10']])
	env_netx10.Append(CPPPATH = ['src/netx10'])
	
	
	#----------------------------------------------------------------------------
	#
	# build the files
	#
#	flasher_sources_netx500 = [src.replace('src', 'targets/netx500') for src in Split(flasher_sources_common+flasher_sources_custom_netx500)]
#	flasher_netx500_elf = env_netx500.Elf('targets/flasher_netx500', flasher_sources_netx500)
#	flasher_netx500_bin = env_netx500.ObjCopy('targets/flasher_netx500', flasher_netx500_elf)
	
#	flasher_sources_netx50  = [src.replace('src', 'targets/netx50')  for src in Split(flasher_sources_common+flasher_sources_custom_netx50)]
#	flasher_netx50_elf = env_netx50.Elf('targets/flasher_netx50', flasher_sources_netx50)
#	env_netx50.ObjCopy('targets/flasher_netx50', flasher_netx50_elf)
	
	
	env_netx10_intram = env_netx10.Clone()
	src_netx10_intram = scons_common.set_build_path(env_netx10_intram, 'targets/netx10_intram', 'src', src_netx10)
	elf_netx10_intram = env_netx10_intram.Elf('targets/flasher_netx10', src_netx10_intram)
	bin_netx10_intram = env_netx10_intram.ObjCopy('targets/flasher_netx10', elf_netx10_intram)
	uue_netx10_intram = env_netx10_intram.UUEncode('targets/flasher_netx10.uue', bin_netx10_intram, UUE_PRE = """
L 00020000
""", UUE_POST = "")


	#----------------------------------------------------------------------------
	#
	# Build the documentation.
	#
	env_default.Asciidoc('targets/doc/flasher.html', 'doc/flasher.txt')
