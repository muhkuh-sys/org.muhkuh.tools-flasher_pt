#! /usr/bin/python2.7

from jonchki import cli_args
from jonchki import jonchkihere
from jonchki import vcs_id

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
strCfg_jonchkiVersion = '0.0.3.1'

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

strCfg_jonchkiSystemConfiguration = os.path.join(
    strCfg_projectFolder,
    'jonchki',
    'org.muhkuh.tools.flasher_cli',
    'jonchkisys.cfg'
)
strCfg_jonchkiProjectConfiguration = os.path.join(
    strCfg_projectFolder,
    'jonchki',
    'org.muhkuh.tools.flasher_cli',
    'jonchkicfg.xml'
)
strCfg_jonchkiFinalizer = os.path.join(
    strCfg_projectFolder,
    'jonchki',
    'org.muhkuh.tools.flasher_cli',
    'finalizer.lua'
)
# This is the artifact configuration file.
strCfg_artifactConfiguration = os.path.join(
    strCfg_projectFolder,
    'targets',
    'jonchki',
    'flasher_cli',
    'flasher_cli.xml'
)

# -
# --------------------------------------------------------------------------

# Try to get the VCS ID.
strProjectVersionVcs, strProjectVersionVcsLong = vcs_id.get(
    strCfg_projectFolder
)
print(strProjectVersionVcs, strProjectVersionVcsLong)

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

# Create the testbench folder if it does not exist yet.
if os.path.exists(strCfg_workingFolder) is not True:
    os.makedirs(strCfg_workingFolder)

if os.path.exists(strCfg_artifactConfiguration) is not True:
    raise Exception(
        'The artifact configuration "%s" does not exist.' % (
            strCfg_artifactConfiguration
        )
    )

# Run jonchki.
sys.stdout.flush()
sys.stderr.flush()
astrArguments = [strJonchki]
astrArguments.append('install-dependencies')
astrArguments.extend(['-v', strCfg_jonchkiVerbose])
astrArguments.extend(['--syscfg', strCfg_jonchkiSystemConfiguration])
astrArguments.extend(['--prjcfg', strCfg_jonchkiProjectConfiguration])
astrArguments.extend(['--finalizer', strCfg_jonchkiFinalizer])
astrArguments.extend(astrJonchkiPlatform)
astrArguments.append(strCfg_artifactConfiguration)
sys.exit(subprocess.call(astrArguments, cwd=strCfg_workingFolder))
