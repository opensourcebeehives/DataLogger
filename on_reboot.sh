# Reboot bash script for the OSBHLogger
# Mounts the USB drive - ensure it is the only one plugged in!
# Teddy Lowe, October 2016

#!/bin/bash

if [ -d /media/usb ]; then
	echo "USB directory exists, skipping"
else
	echo "Creating USB directory"
	sudo mkdir /media/usb
fi
sudo mount /dev/sda1 /media/usb
python /home/pi/OSBHLogger/beginRecord.py

