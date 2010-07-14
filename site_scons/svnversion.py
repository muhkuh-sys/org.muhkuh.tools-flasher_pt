# -*- coding: utf-8 -*-

import os

from SCons.Script import *


def uuencode_action(target, source, env):
	file_source = open(source[0].get_path(), 'r')
	file_target = open(target[0].get_path(), 'w')
	
	file_target.write(env['UUE_PRE'])
	uu.encode(file_source, file_target)
	file_target.write(env['UUE_POST'])
	
	file_source.close()
	file_target.close()
	return 0


def svnversion_action(target, source, env):
	global PROJECT_VERSION
	
	# split up the project version
	version_info = PROJECT_VERSION.split('.')
	project_version_maj = version_info[0]
	project_version_min = version_info[1]
	project_version_svn = 'unknown'
	
	if env['SVNVERSION']:
		# get the svn version
		child = os.popen(env['SVNVERSION']+' -n')
		project_version_svn = child.read()
		err = child.close()
		if err:
			project_version_svn = 'unknown'
	
	# apply the project version to the environment
	substenv = Environment()
	substenv['PROJECT_VERSION_MAJ'] = project_version_maj
	substenv['PROJECT_VERSION_MIN'] = project_version_min
	substenv['PROJECT_VERSION_SVN'] = project_version_svn
	
	# read the template
	src_file = open(source[0].get_path(), 'r')
	src_txt = src_file.read()
	src_file.close()
	
	# read the destination (if exists)
	try:
		dst_file = open(target[0].get_path(), 'r')
		dst_oldtxt = dst_file.read()
		dst_file.close()
	except IOError:
		dst_oldtxt = ''
	
	# filter the src file
	dst_newtxt = substenv.subst(src_txt)
	if dst_newtxt!=dst_oldtxt:
		# overwrite the file
		dst_file = open(target[0].get_path(), 'w')
		dst_file.write(dst_newtxt)
		dst_file.close()


def svnversion_emitter(target, source, env):
	global PROJECT_VERSION
	
	# Make the target depend on the parameter.
	Depends(target, SCons.Node.Python.Value(PROJECT_VERSION))
	
	return target, source


def svnversion_string(target, source, env):
	return 'SVNVersion %s' % target[0].get_path()


def ApplyToEnv(env):
	#----------------------------------------------------------------------------
	#
	# Add uuencode builder.
	#
	env['SVNVERSION'] = env.Detect('svnversion')
	
	svnversion_act = SCons.Action.Action(svnversion_action, svnversion_string)
	svnversion_bld = Builder(action=svnversion_act, emitter=svnversion_emitter, single_source=1)
	env['BUILDERS']['SVNVersion'] = svnversion_bld

