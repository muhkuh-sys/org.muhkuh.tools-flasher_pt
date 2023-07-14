#! /usr/bin/python3

from jonchki import cli_args
from jonchki import jonchkihere

import os
import subprocess
import sys


tPlatform = cli_args.parse()
astrJonchkiPlatform = cli_args.to_jonchki_args(tPlatform)
print('Building for %s' % tPlatform['platform_id'])

# --------------------------------------------------------------------------
# -
# - Configuration
# -

# Get the project folder. This is the folder of this script.
strCfg_projectFolder = os.path.dirname(os.path.realpath(__file__))

# This is the complete path to the testbench folder. The installation will be
# written there.
strCfg_workingFolder = os.path.join(
    strCfg_projectFolder,
    'targets',
    'jonchki',
    'flasher_cli',
    tPlatform['platform_id']
)

# Where is the jonchkihere tool?
strCfg_jonchkiHerePath = os.path.join(
    strCfg_projectFolder,
    'jonchki'
)
# This is the Jonchki version to use.
strCfg_jonchkiVersion = '0.0.11.1'

# Select the verbose level for jonchki.
# Possible values are "debug", "info", "warning", "error" and "fatal".
strCfg_jonchkiVerbose = 'debug'

# Look in this folder for Jonchki archives before downloading them.
strCfg_jonchkiLocalArchives = os.path.join(
    strCfg_projectFolder,
    'jonchki',
    'local_archives'
)
# The target folder for the jonchki installation. A subfolder named
# "jonchki-VERSION" will be created there. "VERSION" will be replaced with
# the version number from strCfg_jonchkiVersion.
strCfg_jonchkiInstallationFolder = os.path.join(
    strCfg_projectFolder,
    'targets'
)


# -
# --------------------------------------------------------------------------

# Build the netX tools.
astrArguments = [
    sys.executable,
    'mbs/mbs'
]
subprocess.check_call(astrArguments, cwd=strCfg_projectFolder)

# Install jonchki.
strJonchki = jonchkihere.install(
    strCfg_jonchkiVersion,
    strCfg_jonchkiInstallationFolder,
    LOCAL_ARCHIVES=strCfg_jonchkiLocalArchives
)
if strJonchki is None:
    raise Exception('Failed to install Jonchki.')

# Create the testbench folder if it does not exist yet.
if os.path.exists(strCfg_workingFolder) is not True:
    os.makedirs(strCfg_workingFolder)

# Run jonchki.
sys.stdout.flush()
sys.stderr.flush()
astrArguments = [strJonchki]
astrArguments.append('install-dependencies')
astrArguments.extend(['-v', strCfg_jonchkiVerbose])
astrArguments.extend([
    '--logfile',
    os.path.join(
        strCfg_workingFolder,
        'jonchki.log'
    )
])
astrArguments.extend([
    '--syscfg',
    os.path.join(
        strCfg_projectFolder,
        'jonchki',
        'org.muhkuh.tools.flasher_cli',
        'jonchkisys.cfg'
    )
])
astrArguments.extend([
    '--prjcfg',
    os.path.join(
        strCfg_projectFolder,
        'jonchki',
        'org.muhkuh.tools.flasher_cli',
        'jonchkicfg.xml'
    )
])
astrArguments.extend([
    '--dependency-log',
    os.path.join(
        strCfg_projectFolder,
        'dependency-log.xml'
    )
])
astrArguments.extend(astrJonchkiPlatform)
astrArguments.append(
    os.path.join(
        strCfg_projectFolder,
        'targets',
        'jonchki',
        'flasher_cli',
        'flasher_cli.xml'
    )
)
sys.exit(subprocess.call(astrArguments, cwd=strCfg_workingFolder))
