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


def get_compiler(name):
	import imp
	import sys
	import os
	global DEPACK_GCC_DIR
	
	pathname = DEPACK_GCC_DIR + os.pathsep + name
	
	mod = None
	fp,pathname,description = imp.find_module(name, [DEPACK_GCC_DIR])
	try:
		mod = imp.load_module(name, fp, pathname, description)
	finally:
		# Since we may exit via an exception, close fp explicitly.
		if fp:
			fp.close()
	return mod
