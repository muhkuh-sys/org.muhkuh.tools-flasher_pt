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

/tmp/apache-ant-1.9.4/bin/ant bootstrap
STATUS=$?
if [ $STATUS -ne 0 ]; then
	echo "Error running ant bootstrap."
	exit 1
fi

/tmp/apache-ant-1.9.4/bin/ant
STATUS=$?
if [ $STATUS -ne 0 ]; then
	echo "Error running ant."
	exit 1
fi

cd ../../..
python ivy/deploy.py artifacts_flasher.xml artifacts_flasher_cli.xml
STATUS=$?
if [ $STATUS -ne 0 ]; then
	echo "Error running the deploy script."
	exit 1
fi

