# -*- coding: utf-8 -*-

import uu

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


def uuencode_emitter(target, source, env):
	# Make the target depend on the parameter.
	Depends(target, SCons.Node.Python.Value(env['UUE_PRE']))
	Depends(target, SCons.Node.Python.Value(env['UUE_POST']))
	
	return target, source


def uuencode_string(target, source, env):
	return 'UUEncode %s' % target[0].get_path()


def ApplyToEnv(env):
	#----------------------------------------------------------------------------
	#
	# Add uuencode builder.
	#
	env['UUE_PRE'] = ''
	env['UUE_POST'] = ''
	
	uuencode_act = SCons.Action.Action(uuencode_action, uuencode_string)
	uuencode_bld = Builder(action=uuencode_act, emitter=uuencode_emitter, suffix='.uue', single_source=1, src_suffix='.bin')
	env['BUILDERS']['UUEncode'] = uuencode_bld



