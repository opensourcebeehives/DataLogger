# Recording script for the OSBHLogger
# Handles recording and naming of video and audio files, 
# along with ensuring there is enough space to record
#
# Teddy Lowe, April 2017

#!/usr/bin/env bash

# Time now
#now="$(date +'%y%m%d%H%M%S')"

# Read in the datalogger ID and location
_LOGGERID=$(sed '1q;d' /home/pi/OSBHLogger/info.txt)

_LOCATION=$(sed '2q;d' /home/pi/OSBHLogger/info.txt)

# Check the increment number, read in as an integer
declare -i _NUMBER=$(sed '3q;d' /home/pi/OSBHLogger/info.txt)

## audio options
audio_length_s=300

## video options
#video_length_ms=10000
#video_bitrate =

# run
# this displays disk space used as a percent, then checks if it is over 95%
used=$(df /home/pi/OSBHLogger/ | awk '{ print $5 }' | tail -n 1 | sed 's/%//')

if [ $used -ge 97 ]; then
	echo "${_NUMBER} startup disk almost full, no data will be recorded" >> /home/pi/OSBHLogger/errors.txt
	exit 3
fi

# Create the temporary directory to store files before moving them to the USB
if [ -d "/home/pi/OSBHLogger/temp" ]; then
	echo "temp directory exists"
else
	echo "no temp directory, creating..."
	cd /home/pi/OSBHLogger
	mkdir temp
fi

# This records video
#echo video

#raspivid -t $video_length_ms -o /home/pi/OSBHLogger/temp/${_LOGGERID}-${_NUMBER}-${_LOCATION}.h264

# This records audio
echo audio

arecord -f dat -r 44100 -c 1 -D plughw:1,0 -d ${audio_length_s} /home/pi/OSBHLogger/temp/${_LOGGERID}-${_NUMBER}-${_LOCATION}.wav

# Increment the number and write to the info.txt file
_NUMBER=${_NUMBER}+1
sed -i "3s/.*/${_NUMBER}/" /home/pi/OSBHLogger/info.txt

# Check to see if a USB is plugged in
if grep -qs '/media/usb' /proc/mounts; then
	echo "media mounted"
else
	echo "${_NUMBER} media not mounted! exiting" >> /home/pi/OSBHLogger/errors.txt
	exit 2
fi

# Check the space used on the USB and don't move data if too full
used=$(df /media/usb/ | awk '{ print $5 }' | tail -n 1 | sed 's/%//')

if [ $used -ge 99 ]; then
	echo "${_NUMBER} External media almost full, not moving files to external device" >> /home/pi/OSBHLogger/errors.txt
	exit 4
fi

# If not full then move the files to the external media and delete the temp directory
echo "moving files"
sudo mv /home/pi/OSBHLogger/temp/* /media/usb/
rmdir /home/pi/OSBHLogger/temp

echo fin

