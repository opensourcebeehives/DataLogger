# Python script for OSBHLogger
# Uses the GPIO library to communicate with the sleepypi and execute recording
# Teddy Lowe, Oct 2016

#!/usr/bin/python

import RPi.GPIO as GPIO
import os, time

GPIO.setmode(GPIO.BCM)
GPIO.setup(25, GPIO.OUT)
GPIO.output(25, GPIO.HIGH)
os.system("/home/pi/OSBHLogger/AVrecord.sh")
GPIO.output(25, GPIO.LOW)
GPIO.cleanup()
print ("Shutting down")
os.system("sudo shutdown -h now")
