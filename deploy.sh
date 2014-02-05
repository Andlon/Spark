#!/bin/sh
echo 'Deploying Spark.';
echo 'Copying assets...';

if [ -d "debug" ]; then
	cp -R -f -t debug assets/*
fi

if [ -d "release" ]; then
	cp -R -f -t release assets/*
fi

echo 'Completed.';

