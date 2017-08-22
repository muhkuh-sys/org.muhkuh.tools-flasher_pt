#! /bin/bash
set -e

# Get the project folder.
PRJ_DIR=`pwd`

# This is the path to the jonchki tool.
JONCHKI_PATH=/tmp/jonchki/install
JONCHKI=${JONCHKI_PATH}/jonchki.lua

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

# Build the Windows_x86 artifact.
pushd ${WORK_BASE}/windows_32bit
LD_LIBRARY_PATH=${JONCHKI_PATH} ${JONCHKI_PATH}/lua5.1 ${JONCHKI} -v debug --syscfg ${PRJ_DIR}/jonchki/org.muhkuh.tools.flasher_cli/jonchkisys.cfg --prjcfg ${PRJ_DIR}/jonchki/org.muhkuh.tools.flasher_cli/jonchkicfg.xml --distribution-id windows --distribution-version "" --cpu-architecture x86 --finalizer ${PRJ_DIR}/jonchki/org.muhkuh.tools.flasher_cli/flasher_cli.lua ${WORK_BASE}/flasher_cli.xml
popd
# Build the Windows_x86_64 artifact.
pushd ${WORK_BASE}/windows_64bit
LD_LIBRARY_PATH=${JONCHKI_PATH} ${JONCHKI_PATH}/lua5.1 ${JONCHKI} -v info --syscfg ${PRJ_DIR}/jonchki/org.muhkuh.tools.flasher_cli/jonchkisys.cfg --prjcfg ${PRJ_DIR}/jonchki/org.muhkuh.tools.flasher_cli/jonchkicfg.xml --distribution-id windows --distribution-version "" --cpu-architecture x86_64 --finalizer ${PRJ_DIR}/jonchki/org.muhkuh.tools.flasher_cli/flasher_cli.lua ${WORK_BASE}/flasher_cli.xml
popd

# Ubuntu 14.04 32bit
pushd ${WORK_BASE}/ubuntu_14.04_32bit
LD_LIBRARY_PATH=${JONCHKI_PATH} ${JONCHKI_PATH}/lua5.1 ${JONCHKI} -v info --syscfg ${PRJ_DIR}/jonchki/org.muhkuh.tools.flasher_cli/jonchkisys.cfg --prjcfg ${PRJ_DIR}/jonchki/org.muhkuh.tools.flasher_cli/jonchkicfg.xml --distribution-id ubuntu --distribution-version 14.04 --cpu-architecture x86 --finalizer ${PRJ_DIR}/jonchki/org.muhkuh.tools.flasher_cli/flasher_cli.lua ${WORK_BASE}/flasher_cli.xml
popd
# Ubuntu 14.04 64bit
pushd ${WORK_BASE}/ubuntu_14.04_64bit
LD_LIBRARY_PATH=${JONCHKI_PATH} ${JONCHKI_PATH}/lua5.1 ${JONCHKI} -v info --syscfg ${PRJ_DIR}/jonchki/org.muhkuh.tools.flasher_cli/jonchkisys.cfg --prjcfg ${PRJ_DIR}/jonchki/org.muhkuh.tools.flasher_cli/jonchkicfg.xml --distribution-id ubuntu --distribution-version 14.04 --cpu-architecture x86_64 --finalizer ${PRJ_DIR}/jonchki/org.muhkuh.tools.flasher_cli/flasher_cli.lua ${WORK_BASE}/flasher_cli.xml
popd

# Ubuntu 16.04 32bit
pushd ${WORK_BASE}/ubuntu_16.04_32bit
LD_LIBRARY_PATH=${JONCHKI_PATH} ${JONCHKI_PATH}/lua5.1 ${JONCHKI} -v info --syscfg ${PRJ_DIR}/jonchki/org.muhkuh.tools.flasher_cli/jonchkisys.cfg --prjcfg ${PRJ_DIR}/jonchki/org.muhkuh.tools.flasher_cli/jonchkicfg.xml --distribution-id ubuntu --distribution-version 16.04 --cpu-architecture x86 --finalizer ${PRJ_DIR}/jonchki/org.muhkuh.tools.flasher_cli/flasher_cli.lua ${WORK_BASE}/flasher_cli.xml
popd
# Ubuntu 16.04 64bit
pushd ${WORK_BASE}/ubuntu_16.04_64bit
LD_LIBRARY_PATH=${JONCHKI_PATH} ${JONCHKI_PATH}/lua5.1 ${JONCHKI} -v info --syscfg ${PRJ_DIR}/jonchki/org.muhkuh.tools.flasher_cli/jonchkisys.cfg --prjcfg ${PRJ_DIR}/jonchki/org.muhkuh.tools.flasher_cli/jonchkicfg.xml --distribution-id ubuntu --distribution-version 16.04 --cpu-architecture x86_64 --finalizer ${PRJ_DIR}/jonchki/org.muhkuh.tools.flasher_cli/flasher_cli.lua ${WORK_BASE}/flasher_cli.xml
popd

# Ubuntu 17.04 32bit
pushd ${WORK_BASE}/ubuntu_17.04_32bit
LD_LIBRARY_PATH=${JONCHKI_PATH} ${JONCHKI_PATH}/lua5.1 ${JONCHKI} -v info --syscfg ${PRJ_DIR}/jonchki/org.muhkuh.tools.flasher_cli/jonchkisys.cfg --prjcfg ${PRJ_DIR}/jonchki/org.muhkuh.tools.flasher_cli/jonchkicfg.xml --distribution-id ubuntu --distribution-version 17.04 --cpu-architecture x86 --finalizer ${PRJ_DIR}/jonchki/org.muhkuh.tools.flasher_cli/flasher_cli.lua ${WORK_BASE}/flasher_cli.xml
popd
# Ubuntu 17.04 64bit
pushd ${WORK_BASE}/ubuntu_17.04_64bit
LD_LIBRARY_PATH=${JONCHKI_PATH} ${JONCHKI_PATH}/lua5.1 ${JONCHKI} -v info --syscfg ${PRJ_DIR}/jonchki/org.muhkuh.tools.flasher_cli/jonchkisys.cfg --prjcfg ${PRJ_DIR}/jonchki/org.muhkuh.tools.flasher_cli/jonchkicfg.xml --distribution-id ubuntu --distribution-version 17.04 --cpu-architecture x86_64 --finalizer ${PRJ_DIR}/jonchki/org.muhkuh.tools.flasher_cli/flasher_cli.lua ${WORK_BASE}/flasher_cli.xml
popd
