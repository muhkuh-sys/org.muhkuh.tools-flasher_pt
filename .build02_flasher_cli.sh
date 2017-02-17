#! /bin/bash
set -e

# Get the project folder.
PRJ_DIR=`pwd`

# This is the path to the jonchki tool.
JONCHKI=${PRJ_DIR}/jonchki/local/jonchki.lua

# Build the Windows_x86 artifact.
pushd targets/jonchki/flasher_cli
lua5.1 ${JONCHKI} -v info --syscfg jonchkisys_windows_32.cfg --prjcfg jonchkicfg.xml --distribution-id windows --cpu-architecture x86 --finalizer flasher_cli.lua flasher_cli.xml
pushd windows_32/install
7z a -tzip -mx=9 ../../flasher_cli_windows_32bit.zip flasher_cli_windows_32bit
popd
lua5.1 ${JONCHKI} -v info --syscfg jonchkisys_windows_64.cfg --prjcfg jonchkicfg.xml --distribution-id windows --cpu-architecture x86_64 --finalizer flasher_cli.lua flasher_cli.xml
pushd windows_64/install
7z a -tzip -mx=9 ../../flasher_cli_windows_64bit.zip flasher_cli_windows_64bit
popd
popd
