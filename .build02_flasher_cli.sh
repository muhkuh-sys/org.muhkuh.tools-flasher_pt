#! /bin/bash
set -e

# Get the project folder.
PRJ_DIR=`pwd`

# This is the path to the jonchki tool.
JONCHKI=/home/cthelen/workspace/org.muhkuh.lua-jonchki/jonchki.lua

# Build the Windows_x86 artifact.
pushd targets/jonchki/flasher_cli
lua5.1 ${JONCHKI} -v info --syscfg jonchkisys_Windows_x86.cfg --prjcfg jonchkicfg.xml --target Windows_x86 --finalizer flasher_cli.lua flasher_cli.xml
pushd Windows_x86/install
7z a -tzip -mx=9 ../../flasher_cli_windows_x86.zip flasher_cli_windows_x86
popd
lua5.1 ${JONCHKI} -v info --syscfg jonchkisys_Windows_x64.cfg --prjcfg jonchkicfg.xml --target Windows_x64 --finalizer flasher_cli.lua flasher_cli.xml
pushd Windows_x64/install
7z a -tzip -mx=9 ../../flasher_cli_windows_x64.zip flasher_cli_windows_x64
popd
popd
