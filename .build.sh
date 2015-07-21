#! /bin/bash
set -e

# Get the MBS Ivy path.
MBS_IVY_PATH=`pwd`/mbs/ivy

# Build the artifact.
python mbs/mbs
pushd targets/ivy/flasher_cli
ant -Dmbs.ivy.path=${MBS_IVY_PATH} bootstrap
ant -Dmbs.ivy.path=${MBS_IVY_PATH}
popd

