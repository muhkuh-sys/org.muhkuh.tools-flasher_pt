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
	src/flasher_ext.c
	src/flasher_spi.c
	src/flasher_srb.c
	src/init_netx_test.s
	src/main.c
	src/netx_consoleapp.c
	src/parflash_common.c
	src/progress_bar.c
	src/rdyrun.c
	src/spansion.c
	src/spi_flash_types.c
	src/startvector.s
	src/strata.c
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


#----------------------------------------------------------------------------
# Only execute this part if the help text is not requested.
# This keeps the help message functional even if no include path for the
# compiler definitions was specified.
if not GetOption('help'):
	# Show summary of the build properties.
	build_properties.PrintSummary()
	
	
	#----------------------------------------------------------------------------
	#
	# import the compiler definitions
	#
	import gcc_arm_elf_4_3_3
	
	env = Environment()
	print env['CCCOM']
	#----------------------------------------------------------------------------
	#
	# create the default environment
	#
	env_default = gcc_arm_elf_4_3_3.get_gcc_arm_elf_4_3_3()
	build_properties.ApplyToEnv(env_default)
	env_default.Append(CPPPATH = ['src'])
	env_default.Replace(LIBS = ['m', 'c', 'gcc'])
	
	
	# create environments for both builds
	env_netx500 = env_default.Clone()
	env_netx500.Append(CCFLAGS = ['-mcpu=arm926ej-s'])
	env_netx500.Replace(LDFILE = 'src/flasher_netx500.ld')
	env_netx500.Replace(LIBPATH = [env_netx500['GCC_DIR']+'/arm-elf/lib/arm926ej-s', env_netx500['GCC_DIR']+'/lib/gcc/arm-elf/'+env_netx500['GCC_VERSION']+'/arm926ej-s'])
	env_netx500.Append(CPPDEFINES = ['__NETX500'])
	env_netx500.Append(CPPPATH = ['src/netx500'])
	env_netx500.VariantDir('target/netx500', 'src', duplicate=0)
	
	env_netx50 = env_default.Clone()
	env_netx50.Append(CCFLAGS = ['-mcpu=arm966e-s'])
	env_netx50.Replace(LDFILE = 'src/flasher_netx50.ld')
	env_netx50.Replace(LIBPATH = [env_netx50['GCC_DIR']+'/arm-elf/lib/arm966e-s', env_netx50['GCC_DIR']+'/lib/gcc/arm-elf/'+env_netx500['GCC_VERSION']+'/arm966e-s'])
	env_netx50.Append(CPPDEFINES = ['__NETX50'])
	env_netx50.Append(CPPPATH = ['src/netx50'])
	env_netx50.VariantDir('target/netx50', 'src', duplicate=0)
	
	
	#----------------------------------------------------------------------------
	#
	# build the files
	#
	flasher_sources_netx500 = [src.replace('src', 'target/netx500') for src in Split(flasher_sources_common+flasher_sources_custom_netx500)]
	env_netx500.Elf('target/flasher_netx500', flasher_sources_netx500)
	
	flasher_sources_netx50  = [src.replace('src', 'target/netx50')  for src in Split(flasher_sources_common+flasher_sources_custom_netx50)]
	env_netx50.Elf('target/flasher_netx50', flasher_sources_netx50)

