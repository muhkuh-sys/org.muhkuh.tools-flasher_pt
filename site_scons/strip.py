# -*- coding: utf-8 -*-
# ----------------------------------------------------------------------- #
#   Copyright (C) 2020 by Christoph Thelen                                #
#   doc_bacardi@users.sourceforge.net                                     #
#                                                                         #
#   This program is free software; you can redistribute it and/or modify  #
#   it under the terms of the GNU General Public License as published by  #
#   the Free Software Foundation; either version 2 of the License, or     #
#   (at your option) any later version.                                   #
#                                                                         #
#   This program is distributed in the hope that it will be useful,       #
#   but WITHOUT ANY WARRANTY; without even the implied warranty of        #
#   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         #
#   GNU General Public License for more details.                          #
#                                                                         #
#   You should have received a copy of the GNU General Public License     #
#   along with this program; if not, write to the                         #
#   Free Software Foundation, Inc.,                                       #
#   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.             #
# ----------------------------------------------------------------------- #


import os
import re
import subprocess

import SCons.Script


def strip_action(target, source, env):
    # Get the flags.
    atFlags = env['STRIP_FLAGS']

    tSrc = source[0]
    tDst = target[0]

    # Collect all command options.
    atCmd = [
        env['STRIP'],
        '-o', tDst.get_path()
    ]
    atCmd.extend(atFlags)
    atCmd.append(tSrc.get_path())

    # Strip the file.
    iReturnCode = subprocess.check_call(atCmd)


def strip_emitter(target, source, env):
    # Make the target depend on the parameter.
    env.Depends(target, SCons.Node.Python.Value(env['STRIP_FLAGS']))

    return target, source


def strip_string(target, source, env):
    return 'Strip %s' % target[0].get_path()


def ApplyToEnv(env):
    # ------------------------------------------------------------------------
    #
    # Add the Strip builder.
    #

    # Set the default strip options.
    env['STRIP'] = re.sub('-ar$', '-strip', env['AR'])
    env['STRIP_FLAGS'] = ['--strip-all']

    strip_act = SCons.Action.Action(strip_action, strip_string)
    strip_bld = SCons.Script.Builder(
        action=strip_act,
        emitter=strip_emitter,
        single_source=1
    )
    env['BUILDERS']['Strip'] = strip_bld
