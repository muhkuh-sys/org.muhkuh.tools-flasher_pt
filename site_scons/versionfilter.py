# -*- coding: utf-8 -*-

import os

from SCons.Script import *


def gen_version(env, src_name, dst_name):
	global PROJECT_VERSION
	
	# split up the project version
	version_info = PROJECT_VERSION.split('.')
	project_version_maj = version_info[0]
	project_version_min = version_info[1]
	
	# get the svn version
	if not env['SVNVERSION']:
		project_version_svn = 'unknown'
	else:
		child = os.popen(env['SVNVERSION']+' -n')
		project_version_svn = child.read()
		err = child.close()
		if err:
			project_version_svn = 'unknown'
	
	# apply the project version to the environment
	env['PROJECT_VERSION_MAJ'] = project_version_maj
	env['PROJECT_VERSION_MIN'] = project_version_min
	env['PROJECT_VERSION_SVN'] = project_version_svn
	
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
