#!/bin/bash

if [ -d "encoded" ]; then
	echo "encoded directory exists, skipping"
else
	echo "creating encoded directory"
	mkdir encoded
fi

for f in *.h264; do
	if [ ! -f "encoded/${f}.mp4" ]; then
		avconv -i "$f" -vcodec copy "encoded/${f}.mp4"
	fi
done
