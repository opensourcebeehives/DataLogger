#!/bin/bash

# Time now
#now="$(date +'%y%m%d%H%M%S')"

# Read in the datalogger ID
_LOGGERID=$(sed '1q;d' /home/pi/AKERLogger/info.txt)

# Check the increment number, read in as an integer
declare -i _NUMBER=$(sed '2q;d' /home/pi/AKERLogger/info.txt)

## audio options
audio_length_s=300

## video options
video_length_ms=10000
#video_bitrate =

# run
# this displays disk space used as a percent, then checks if it is over 95%
used=$(df /home/pi/AKERLogger/ | awk '{ print $5 }' | tail -n 1 | sed 's/%//')

if [ $used -ge 95 ]; then
	echo "${_NUMBER} startup disk almost full, no data will be recorded" >> /home/pi/AKERLogger/errors.txt
	exit 3
fi

# Create the temporary directory to store files before moving them to the USB
if [ -d "/home/pi/AKERLogger/temp" ]; then
	echo "temp directory exists"
else
	echo "no temp directory, creating..."
	cd /home/pi/AKERLogger
	mkdir temp
fi

# This records video
echo video

raspivid -t $video_length_ms -o /home/pi/AKERLogger/temp/${_LOGGERID}_${_NUMBER}_v.h264

# This records audio
echo audio

arecord -f dat -r 44100 -c 1 -D plughw:1,0 -d ${audio_length_s} /home/pi/AKERLogger/temp/${_LOGGERID}_${_NUMBER}_a.wav

# Increment the number and write to the info.txt file
_NUMBER=$_NUMBER+1
sed -i "2s/.*/$_NUMBER/" /home/pi/AKERLogger/info.txt

# Check to see if a USB is plugged in
if [ -d "/media/pi/RECORDINGS" ]; then
	echo "media inserted"
else
	echo "${_NUMBER} no media, exiting" >> /home/pi/AKERLogger/errors.txt
	exit 2
fi

# Check the space used on the USB and don't move data if too full
used=$(df /media/pi/RECORDINGS/ | awk '{ print $5 }' | tail -n 1 | sed 's/%//')

if [ $used -ge 97 ]; then
	echo "${_NUMBER} External media almost full, not moving files to external device" >> errors.txt
	exit 4
fi

# If not full then move the files to the external media and delete the temp directory
echo "moving files"
mv /home/pi/AKERLogger/temp/* /media/pi/RECORDINGS/
rmdir /home/pi/AKERLogger/temp

echo fin

