#! /usr/bin/python2.7

import os
import re
import shutil
import subprocess
import site
import string
import sys
import xml.etree.ElementTree


argc = len(sys.argv)
if argc == 1:
    # No platform was specified on the command line.
    # Build for the local platform in the folder 'local'.

    # Pass no options to the jonchki tool.
    astrJonchkiPlatform = []

    # Build in the folder "local".
    strJonchkiPlatformID = 'local'

elif argc == 3:
    # The command line has 2 arguments.
    # This looks like a distribution ID and a CPU architecture.
    strJonchkiDistributionID = sys.argv[1]
    strJonchkiDistributionVersion = ''
    strJonchkiCPUArchitecture = sys.argv[2]

    # Pass the options to jonchki.
    astrJonchkiPlatform = [
        '--distribution-id', strJonchkiDistributionID,
        '--empty-distribution-version',
        '--cpu-architecture', strJonchkiCPUArchitecture
    ]

    strJonchkiPlatformID = '%s_%s' % (
        strJonchkiDistributionID,
        strJonchkiCPUArchitecture
    )

elif argc == 4:
    # The command has 3 arguments.
    # This looks like a distribution ID, a distribution version and a CPU
    # architecture.
    strJonchkiDistributionID = sys.argv[1]
    strJonchkiDistributionVersion = sys.argv[2]
    strJonchkiCPUArchitecture = sys.argv[3]

    # Pass the options to jonchki.
    astrJonchkiPlatform = [
        '--distribution-id', strJonchkiDistributionID,
        '--distribution-version', strJonchkiDistributionVersion,
        '--cpu-architecture', strJonchkiCPUArchitecture
    ]

    strJonchkiPlatformID = '%s_%s_%s' % (
        strJonchkiDistributionID,
        strJonchkiDistributionVersion,
        strJonchkiCPUArchitecture
    )

else:
    raise Exception('Invalid numer of arguments.')

print('Building for %s' % strJonchkiPlatformID)


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
    strJonchkiPlatformID
)

# Where is the jonchkihere tool?
strCfg_jonchkiHerePath = os.path.join(
    strCfg_projectFolder,
    'jonchki'
)
# This is the Jonchki version to use.
strCfg_jonchkiVersion = '0.0.3.1'
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

# - Try to get the VCS ID.

# The default version is 'unknown'.
strProjectVersionVcs = 'unknown'
strProjectVersionVcsLong = 'unknown'

# Find GIT on windows.
#strGit = 'c:/Programme/Git/bin/git.exe'
strGit = 'git'

try:
    strCmd = '%s describe --abbrev=12 --always --dirty=+ --long' % strGit
    tProcess = subprocess.Popen(
        strCmd,
        stdout=subprocess.PIPE,
        cwd=strCfg_projectFolder,
        shell=True
    )
    strOutput, strError = tProcess.communicate()
    if tProcess.returncode != 0:
        raise Exception('git failed!')
    strGitId = string.strip(strOutput)
    tMatch = re.match('[0-9a-f]{12}\+?$', strGitId)
    if tMatch is not None:
        # This is a repository with no tags.
        # Use the raw SHA sum.
        strProjectVersionVcs = strGitId
        strProjectVersionVcsLong = strGitId
    else:
        tMatch = re.match(
            'v(\d+(\.\d+)*)-(\d+)-g([0-9a-f]{12})$',
            strGitId
        )
        if tMatch is not None:
            ulRevsSinceTag = long(tMatch.group(3))
            if ulRevsSinceTag==0:
                # This is a repository which is exactly on a
                # tag. Use the tag name.
                strProjectVersionVcs = tMatch.group(1)
                strProjectVersionVcsLong = '%s-%s' % (
                    tMatch.group(1),
                    tMatch.group(4)
                )
            else:
                # This is a repository with commits after
                # the last tag. Use the checkin ID.
                strProjectVersionVcs = tMatch.group(4)
                strProjectVersionVcsLong = tMatch.group(4)
        else:
            tMatch = re.match(
                'v(\d+(\.\d+)*)-(\d+)-g([0-9a-f]{12})\+?$',
                strGitId
            )
            if tMatch is not None:
                ulRevsSinceTag = long(tMatch.group(3))
                if ulRevsSinceTag==0:
                    # This is a repository on a tag, but it has
                    # modified files. Use the tag name and the '+'.
                    strProjectVersionVcs = '%s+' % (tMatch.group(1))
                    strProjectVersionVcsLong = '%s-%s+' % (
                        tMatch.group(1),
                        tMatch.group(4)
                    )
                else:
                    # This is a repository with commits after
                    # the last tag and modified files. Use the checkin ID and the '+'.
                    strProjectVersionVcs = '%s+' % (tMatch.group(4))
                    strProjectVersionVcsLong = '%s+' % (tMatch.group(4))
            else:
                # The description has an unknown format.
                strProjectVersionVcs = strGitId
                strProjectVersionVcsLong = strGitId

    strProjectVersionVcs = 'GIT%s' % strProjectVersionVcs
    strProjectVersionVcsLong = 'GIT%s' % strProjectVersionVcsLong
except Exception as e:
    print('Failed to get the GIT VCS ID: %s' % e)


# Add the module path for jonchkihere.
site.addsitedir(strCfg_jonchkiHerePath)
import jonchkihere

# Create the testbench folder if it does not exist yet.
if os.path.exists(strCfg_workingFolder) is not True:
    os.makedirs(strCfg_workingFolder)

if os.path.exists(strCfg_artifactConfiguration) is not True:
    raise Exception(
        'The artifact configuration "%s" does not exist.' % strCfg_artifactConfiguration
    )

# Install jonchki.
jonchkihere.install(
    strCfg_jonchkiVersion,
    strCfg_jonchkiInstallationFolder,
    LOCAL_ARCHIVES=strCfg_jonchkiLocalArchives
)
# Get the path to the Jonchki tool.
strJonchkiCmd = os.path.join(
    strCfg_jonchkiInstallationFolder,
    '.jonchki.cmd'
)
tFile = open(strJonchkiCmd, 'rt')
strJonchki = string.strip(tFile.read())
tFile.close()


# Run jonchki.
sys.stdout.flush()
sys.stderr.flush()
astrArguments = [strJonchki]
astrArguments.append('install-dependencies')
astrArguments.extend(['-v', 'info'])
astrArguments.extend(['--syscfg', strCfg_jonchkiSystemConfiguration])
astrArguments.extend(['--prjcfg', strCfg_jonchkiProjectConfiguration])
astrArguments.extend(['--finalizer', strCfg_jonchkiFinalizer])
astrArguments.extend(astrJonchkiPlatform)
astrArguments.append(strCfg_artifactConfiguration)
sys.exit(subprocess.call(astrArguments, cwd=strCfg_workingFolder))
