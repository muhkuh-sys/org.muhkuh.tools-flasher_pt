# -*- coding: utf-8 -*-

from SCons.Script import *


#----------------------------------------------------------------------------
#
# Accept 'clean' target like make as an alternative to '-c'. This makes it
# much easier to work with an IDE like KDevelop.
#
if 'clean' in COMMAND_LINE_TARGETS:
	Alias('clean', '.')
	SetOption('clean', 1)


#----------------------------------------------------------------------------
#
# Add the depack_gcc_dir define to the site directory.
#
global depack_gcc_dir
try:
	SCons.Script.Main._load_site_scons_dir(SCons.Node.FS.get_default_fs().SConstruct_dir, depack_gcc_dir)
except NameError:
	print "No GCC directory specified!"

#----------------------------------------------------------------------------
#
# Display the complete command line if any command failed.
#
def display_build_status():
	from SCons.Script import GetBuildFailures
	bf_all = GetBuildFailures()
	if bf_all:
		# iterate over all failures and print the command
		for bf in bf_all:
			if bf and bf.node and bf.command:
				print 'Failed command for ' + str(bf.node) + ":\n" + ' '.join(bf.command)
		print "!!!!!!!!!!!!!!!"
		print "!!! FAILED !!!!"
		print "!!!!!!!!!!!!!!!"
	else:
		print "Build succeeded."

import atexit
atexit.register(display_build_status)

