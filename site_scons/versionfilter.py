# -*- coding: utf-8 -*-

import os

from SCons.Script import *


def gen_version(env, src_name, dst_name):
	global PROJECT_VERSION_MAJ
	global PROJECT_VERSION_MIN
	
	
	# get the svn version
	if not env['SVNVERSION']:
		project_svnversion = 'unknown'
	else:
		child = os.popen(env['SVNVERSION']+' -n')
		project_svnversion = child.read()
		err = child.close()
		if err:
			project_svnversion = 'unknown'
	env['PROJECT_VERSION_MAJ'] = PROJECT_VERSION_MAJ
	env['PROJECT_VERSION_MIN'] = PROJECT_VERSION_MIN
	env['PROJECT_VERSION_SVN'] = project_svnversion
	
	# read the template
	src_file = open(src_name, 'r')
	src_txt = src_file.read()
	src_file.close()
	
	# read the destination (if exists)
	try:
		dst_file = open(dst_name, 'r')
		dst_oldtxt = dst_file.read()
		dst_file.close()
	except IOError:
		dst_oldtxt = ''
	
	# filter the src file
	dst_newtxt = env.subst(src_txt)
	if dst_newtxt!=dst_oldtxt:
		# overwrite the file
		dst_file = open(dst_name, 'w')
		dst_file.write(dst_newtxt)
		dst_file.close()


def generate(env):
	env['SVNVERSION'] = env.Detect('svnversion')
	env.AddMethod(gen_version, "GenVersion")
