#!/usr/bin/python

import RPi.GPIO as GPIO
import os, time

GPIO.setmode(GPIO.BCM)
GPIO.setup(25, GPIO.OUT)
GPIO.output(25, GPIO.HIGH)
os.system("/home/pi/AKERLogger/AVrecord.sh")
GPIO.output(25, GPIO.LOW)
GPIO.cleanup()
print ("Shutting down")
os.system("sudo shutdown -h now")
