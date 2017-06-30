#! /bin/bash
set -e

# This is the name of the working container.
# FIXME: generate something unique to avoid collisions if more than one build is running.
CONTAINER=c0

# Get the project directory.
PRJDIR=`pwd`

# Make sure that the "targets" folder exists.
# NOTE: do not remove it, maybe there are already components.
mkdir -p ${PRJDIR}/targets
mkdir -p ${PRJDIR}/platform/targets

# Start the container and mount the project folder.
lxc init mbs-ubuntu-1604-x64 ${CONTAINER}
lxc config device add ${CONTAINER} projectDir disk source=${PRJDIR} path=/tmp/work
lxc start ${CONTAINER}
sleep 5

# Prepare the build folder.
lxc exec ${CONTAINER} -- bash -c 'rm -rf /tmp/targets'
lxc exec ${CONTAINER} -- bash -c 'mkdir /tmp/targets'
lxc exec ${CONTAINER} -- bash -c 'mount --bind /tmp/targets /tmp/work/targets'
lxc exec ${CONTAINER} -- bash -c 'rm -rf /tmp/platform/targets'
lxc exec ${CONTAINER} -- bash -c 'mkdir -p /tmp/platform/targets'
lxc exec ${CONTAINER} -- bash -c 'mount --bind /tmp/platform/targets /tmp/work/platform/targets'

# Update the package list to prevent "not found" messages.
lxc exec ${CONTAINER} -- bash -c 'apt-get update --assume-yes'

# Install the project specific packages.
lxc exec ${CONTAINER} -- bash -c 'apt-get install --assume-yes lua5.1 lua-filesystem lua-expat lua51-mhash lua-sql-sqlite3 p7zip-full'

# Build the artefacts.
lxc exec ${CONTAINER} -- bash -c 'cd /tmp/work && bash .build01_flasher.sh'
lxc exec ${CONTAINER} -- bash -c 'cd /tmp/work && bash .build02_flasher_cli.sh'

# Get all artifacts.
FILELIST=`lxc exec ${CONTAINER} -- bash -c 'find "/tmp/work" -path "/tmp/work/targets/jonchki/repository/org/muhkuh/tools/flasher/*" -type f'`
echo ${FILELIST}
for strAbsolutePath in ${FILELIST}; do
	echo "Pull ${strAbsolutePath}"
	lxc file pull ${CONTAINER}${strAbsolutePath} targets/
done
lxc file pull ${CONTAINER}/targets/jonchki/flasher_cli/flasher_cli_windows_32bit.zip targets/
lxc file pull ${CONTAINER}/targets/jonchki/flasher_cli/flasher_cli_windows_64bit.zip targets/

# Stop and remove the container.
lxc stop ${CONTAINER}
lxc delete ${CONTAINER}
