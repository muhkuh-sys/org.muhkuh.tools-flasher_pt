# -*- coding: utf-8 -*-

import imp
import sys
import os

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
	global DEPACK_GCC_DIR
	
	mod = None
	fp,pathname,description = imp.find_module(name, [DEPACK_GCC_DIR])
	try:
		mod = imp.load_module(name, fp, pathname, description)
	finally:
		# Since we may exit via an exception, close fp explicitly.
		if fp:
			fp.close()
	return mod


def get_asciidoc(name):
	global DEPACK_ASCIIDOC_DIR
	
	mod = None
	fp,pathname,description = imp.find_module(name, [DEPACK_ASCIIDOC_DIR])
	
	try:
		mod = imp.load_module(name, fp, pathname, description)
	finally:
		# Since we may exit via an exception, close fp explicitly.
		if fp:
			fp.close()
	return mod


def set_build_path(env, build_path, source_path, sources):
	env.VariantDir(build_path, source_path, duplicate=0)
	return [src.replace(source_path, build_path) for src in sources]

