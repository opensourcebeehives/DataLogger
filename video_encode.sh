# Batch video encoding script for .h264 files
# Place in folder full of files and run, encoded files will be put in 
# the encoded folder. Duplicates will be ignored. Can also be used with 
# ffmpeg instead of avconv simply by replacing the command
#
# Teddy Lowe, October 2016

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
