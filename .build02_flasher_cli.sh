#! /bin/bash
set -e

VERBOSITY=debug

# Get the project folder.
PRJ_DIR=`pwd`

# Install jonchki v0.0.1.1 .
python2.7 jonchki/jonchkihere.py --jonchki-version 0.0.1.1 ${PRJ_DIR}/targets

# This is the path to the jonchki tool.
JONCHKI=${PRJ_DIR}/targets/jonchki-0.0.1.1/jonchki

# This is the base path to the jonchki working folders.
WORK_BASE=${PRJ_DIR}/targets/jonchki/flasher_cli

# Remove all working folders and re-create them.
rm -rf ${WORK_BASE}/windows_32bit
rm -rf ${WORK_BASE}/windows_64bit
rm -rf ${WORK_BASE}/ubuntu_14.04_32bit
rm -rf ${WORK_BASE}/ubuntu_14.04_64bit
rm -rf ${WORK_BASE}/ubuntu_16.04_32bit
rm -rf ${WORK_BASE}/ubuntu_16.04_64bit
rm -rf ${WORK_BASE}/ubuntu_17.04_32bit
rm -rf ${WORK_BASE}/ubuntu_17.04_64bit

mkdir -p ${WORK_BASE}/windows_32bit
mkdir -p ${WORK_BASE}/windows_64bit
mkdir -p ${WORK_BASE}/ubuntu_14.04_32bit
mkdir -p ${WORK_BASE}/ubuntu_14.04_64bit
mkdir -p ${WORK_BASE}/ubuntu_16.04_32bit
mkdir -p ${WORK_BASE}/ubuntu_16.04_64bit
mkdir -p ${WORK_BASE}/ubuntu_17.04_32bit
mkdir -p ${WORK_BASE}/ubuntu_17.04_64bit

COMMON_OPTIONS="--syscfg ${PRJ_DIR}/jonchki/org.muhkuh.tools.flasher_cli/jonchkisys.cfg --prjcfg ${PRJ_DIR}/jonchki/org.muhkuh.tools.flasher_cli/jonchkicfg.xml --finalizer ${PRJ_DIR}/jonchki/org.muhkuh.tools.flasher_cli/flasher_cli.lua ${WORK_BASE}/flasher_cli.xml"

# Build the Windows_x86 artifact.
pushd ${WORK_BASE}/windows_32bit
${JONCHKI} -v ${VERBOSITY} --distribution-id windows --empty-distribution-version --cpu-architecture x86 ${COMMON_OPTIONS}
popd
# Build the Windows_x86_64 artifact.
pushd ${WORK_BASE}/windows_64bit
${JONCHKI} -v ${VERBOSITY} --distribution-id windows --empty-distribution-version --cpu-architecture x86_64 ${COMMON_OPTIONS}
popd

# Ubuntu 14.04 32bit
pushd ${WORK_BASE}/ubuntu_14.04_32bit
${JONCHKI} -v ${VERBOSITY} --distribution-id ubuntu --distribution-version 14.04 --cpu-architecture x86 ${COMMON_OPTIONS}
popd
# Ubuntu 14.04 64bit
pushd ${WORK_BASE}/ubuntu_14.04_64bit
${JONCHKI} -v ${VERBOSITY} --distribution-id ubuntu --distribution-version 14.04 --cpu-architecture x86_64 ${COMMON_OPTIONS}
popd

# Ubuntu 16.04 32bit
pushd ${WORK_BASE}/ubuntu_16.04_32bit
${JONCHKI} -v ${VERBOSITY} --distribution-id ubuntu --distribution-version 16.04 --cpu-architecture x86 ${COMMON_OPTIONS}
popd
# Ubuntu 16.04 64bit
pushd ${WORK_BASE}/ubuntu_16.04_64bit
${JONCHKI} -v ${VERBOSITY} --distribution-id ubuntu --distribution-version 16.04 --cpu-architecture x86_64 ${COMMON_OPTIONS}
popd

# Ubuntu 17.04 32bit
pushd ${WORK_BASE}/ubuntu_17.04_32bit
${JONCHKI} -v ${VERBOSITY} --distribution-id ubuntu --distribution-version 17.04 --cpu-architecture x86 ${COMMON_OPTIONS}
popd
# Ubuntu 17.04 64bit
pushd ${WORK_BASE}/ubuntu_17.04_64bit
${JONCHKI} -v ${VERBOSITY} --distribution-id ubuntu --distribution-version 17.04 --cpu-architecture x86_64 ${COMMON_OPTIONS}
popd
