#! /bin/sh

# Build the artifact.
python mbs/mbs
STATUS=$?
if [ $STATUS -ne 0 ]; then
	echo "Error building the flasher artifact!"
	exit 1
fi

cd targets/ivy/flasher_cli
STATUS=$?
if [ $STATUS -ne 0 ]; then
	echo "Error changing to the artifacts folder."
	exit 1
fi

ant bootstrap
STATUS=$?
if [ $STATUS -ne 0 ]; then
	echo "Error running ant bootstrap."
	exit 1
fi

ant
STATUS=$?
if [ $STATUS -ne 0 ]; then
	echo "Error running ant."
	exit 1
fi

cd ../../..
