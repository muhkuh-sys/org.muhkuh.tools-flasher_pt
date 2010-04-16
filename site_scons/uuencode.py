# -*- coding: utf-8 -*-

import uu

import SCons.Node.FS
import SCons.Scanner


def builder_uuencode(target, source, env):
	file_source = open(source[0].get_path(), 'r')
	file_target = open(target[0].get_path(), 'w')
	
	file_target.write(env['UUE_PRE'])
	uu.encode(file_source, file_target)
	file_target.write(env['UUE_POST'])
	
	file_source.close()
	file_target.close()
	return 0


def ApplyToEnv(env):
	#----------------------------------------------------------------------------
	#
	# Add uuencode builder.
	#
	env['UUE_PRE'] = ''
	env['UUE_POST'] = ''
	
	uuencode = SCons.Builder.Builder(action = builder_uuencode,
	                               suffix = '.uue',
	                               src_suffix = '.bin',
	                               src_builder = 'ObjCopy',
	                               single_source = 1)
	env['BUILDERS']['Uuencode'] = uuencode
