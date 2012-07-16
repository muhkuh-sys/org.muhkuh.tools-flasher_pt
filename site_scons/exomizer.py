# -*- coding: utf-8 -*-

import SCons.Node.FS
import SCons.Scanner


def exoraw_emitter(target, source, env):
	env.Depends(target, env['EXORAW'])
	return (target, source)


def ApplyToEnv(env):
	#----------------------------------------------------------------------------
	#
	# Add exoraw builder.
	#
	env['EXORAW']       = 'exoraw'
	env['EXORAWFLAGS']  = ['-b', '-q']
	env['EXORAWCOM']    = '"$EXORAW" $EXORAWFLAGS -o $TARGET $SOURCES'
	env['EXORAWCOMSTR'] = 'Exoraw $TARGET'
	env['EXORAWSUFFIX'] = '.exo'

	exoraw_com = SCons.Action.Action('$EXORAWCOM', '$EXORAWCOMSTR')
	exoraw_bld = SCons.Builder.Builder(action = exoraw_com,
	                                   emitter = exoraw_emitter,
	                                   suffix = '$EXORAWSUFFIX',
	                                   single_source = 1)
	env['BUILDERS']['Exoraw'] = exoraw_bld
