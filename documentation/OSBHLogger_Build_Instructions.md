# OSBHLogger Build Instructions

Teddy Lowe, October 2016

See the [GitHub](https://github.com/opensourcebeehives/OSBHLogger) 
for source files

----
##Hardware
Click to view the [Bill of Materials](google sheets link)

----
##Downloads
Before starting to build your own OSBHLogger, first make sure you have downloaded all software and files needed. Some files are quite large and may take some time to complete.

###Software
* [Arduino IDE](https://www.arduino.cc/en/Main/OldSoftwareReleases#previous) - *only tested on version 1.6.5, if you are using another version your mileage may vary*
* [Win32 Disk Imager](https://sourceforge.net/projects/win32diskimager/) - *Windows only, for Mac or Linux instructions will be provided below*

###Arduino Libraries
These libraries must be installed for the code to compile. [See here](https://www.arduino.cc/en/Guide/Libraries) for help installing.

* [PCF8523](https://github.com/SpellFoundry/PCF8523)
* [SleepyPi2](https://github.com/SpellFoundry/SleepyPi2)
* [Time](https://github.com/PaulStoffregen/Time)
* [Low Power](https://github.com/rocketscream/Low-Power)

###Additional Files
* [Raspberry Pi Disk Image](https://www.dropbox.com/s/cj2wm1wae3lfy33/AKERLogger_2016_10_25_PRODUCTION.img?dl=0) - *This file is nearly 8GB!*
* [Arduino Code](https://github.com/opensourcebeehives/OSBHLogger/tree/master/SleepyPi_FW)

----
##1. Write Raspberry Pi Image
*These instructions only apply to Windows. For Mac or Linux, [see here](http://elinux.org/RPi_Easy_SD_Card_Setup).*

To write the disk image for the Raspberry Pi, first ensure that you have installed Win32 Disk Imager and downloaded the latest disk image using the links above. 

Once that is done, plug your microSD card into your computer and run Win32 Disk Imager as an administrator. You will be presented with a window like the one below.

![Win32DiskImager](https://github.com/opensourcebeehives/OSBHLogger/blob/master/documentation/images/01_win32.png)

Click the folder icon and navigate to the disk image you downloaded earlier. Next, click the drive letter drop down menu to the right and choose the letter that represents your microSD card. 

Be careful! If you select the wrong letter you can lose a lot of data!

Once you have the correct drive selected, click "Write" to begin writing to the card. This process will take some time, and you can move on to the next steps as you wait.

----
##2. Format Memory Stick
*This step can be completed while the microSD card is being written to. This only applies to Windows. See here for [Mac](http://osxdaily.com/2012/01/04/format-an-external-hard-drive-or-usb-flash-drive-for-mac-os-x/) or [Linux](http://askubuntu.com/questions/22381/how-to-format-a-usb-flash-drive).*

First, plug in your memory stick to an open USB port on your computer. Next, open up "This PC" or "My Computer" depending on the version of Windows you are running. Right click on the memory stick you just inserted and choose "Format"

![Format](https://github.com/opensourcebeehives/OSBHLogger/blob/master/documentation/images/02_format.PNG)

In the window that pops up, pick "FAT32" from the "File system" dropdown menu and choose "Default allocation size" from the "Allocation unit size" menu. Put whatever you want the drive to be named in the "Volume label" field, ensure "Quick Format" is checked, and click start.

When this is completed, your drive is ready to go.

----
##3. Program Sleepy Pi 2
*This step can be completed while the microSD card is being written to.*

*If you decided to purchase a Sleepy Pi with low profile pins or did not purchase the programming adapter, information on programming through the Raspberry Pi can be found [here](http://spellfoundry.com/sleepy-pi/setting-arduino-ide-raspbian/).*

Before moving forward, make sure that you have downloaded and installed the Arduino IDE and the required libraries using the links from above, and that you have downloaded the Arduino code for the Sleepy Pi 2.

First, the Sleepy Pi 2 needs to be assembled. This involves soldering 2 sets of headers and a screw terminal for power, and inserting the stackable headers, standoffs, and backup battery. The following pictures show the locations of the solder joints and a fully assembled Sleepy Pi 2.

![Solder1](https://github.com/opensourcebeehives/OSBHLogger/blob/master/documentation/images/03_solder1.jpg)

![Solder2](https://github.com/opensourcebeehives/OSBHLogger/blob/master/documentation/images/03_solder2.jpg)

![Solder3](https://github.com/opensourcebeehives/OSBHLogger/blob/master/documentation/images/03_solder3.jpg)

Next, you will need to plug in the Sleepy Pi Programmer to the Sleepy Pi 2 as shown in the image below, and plug the other end into a spare USB port on your computer. Then plug in a micro USB plug into the Sleepy Pi to provide power.

![SleepyPiProgrammer](https://github.com/opensourcebeehives/OSBHLogger/blob/master/documentation/images/04_sleepypiprogrammer.jpg)

Open up the Arduino code that you downloaded earlier, called SleepyPi_FW. To check that your libraries installed correctly, click the blue check button in the upper left corner of the window. If you get any errors, make sure everything is where it should be and try again.

When you are ready to upload to the board, click "Tools > Board" and select the "Arduino Fio".

![Tools>Board](https://github.com/opensourcebeehives/OSBHLogger/blob/master/documentation/images/05_tools-board.png)

With the Arduino Fio selected, click "Tools > Port" and select whichever COM port is available. If the Port selection is grayed out, ensure that the Sleepy Pi Programmer is plugged in correctly and the Sleepy Pi is powered.

![Tools>Port](https://github.com/opensourcebeehives/OSBHLogger/blob/master/documentation/images/06_tools-port.png)

With this ready, click the blue arrow in the top left corner to upload the code. Your Sleepy Pi is ready to go.

----
##4. Set Up and Build Camera
Before the camera gets encased by LEDs and has extra wires running to it, we need to focus the lens to a very short distance because of the small spacing in beehives. 

###Set Up Camera
To begin doing this, we will first need to plug in the camera and the Sleepy Pi. This is also a good time to change out the short camera cable that it comes with for the longer one needed to reach inside the hive.

![Thread Sleepy Pi](https://github.com/opensourcebeehives/OSBHLogger/blob/master/documentation/images/07_thread-sleepypi.jpg)

![Plug RPi](https://github.com/opensourcebeehives/OSBHLogger/blob/master/documentation/images/08_plug-rpi.jpg)

![Plug Camera](https://github.com/opensourcebeehives/OSBHLogger/blob/master/documentation/images/09_plug-cam.jpg)

Once the camera and the Sleepy Pi are plugged in, plug the microSD card into the Raspberry Pi.

**BEFORE** powering on anything, make sure you connect the hardware jumper together using the provided connector as shown in the picture below. If you forget to do this, the Sleepy Pi will shut down the Raspberry Pi while you are working on it!

![Hardware Jumper On](https://github.com/opensourcebeehives/OSBHLogger/blob/master/documentation/images/10_hwjump-ON.jpg)

Next, plug in a keyboard and an HDMI capable monitor, then plug in the power on the Sleepy Pi. This will switch on the Raspberry Pi.

###Focus Camera
To allow for the camera to be focused, you need to firmly but gently break the glue that is used to stop the lens from spinning. I found that a pair of needle nose pliers worked perfectly for this job. Once the glue is broken, the lens can spin more freely and can be focused to different distances.

![Needle Nose on Lens](https://github.com/opensourcebeehives/OSBHLogger/blob/master/documentation/images/11_noselens.jpg)

Now, using a tape measure, an object of your choice, and the clear camera case, you can take pictures of the object at different distances while rotating the lens between pictures to try to focus the camera correctly. To take a picture, use the command `raspistill -o test.jpg`. This will show a preview window on the screen while the picture is taken and creates an image with the name `test.jpg`. I found that it takes about a three-quarter turn to the left to focus at 2cm, however each camera had to be fine tuned.

![Test Picture](https://github.com/opensourcebeehives/OSBHLogger/blob/master/documentation/images/12_focus_5cm_ball_5cm.jpeg)

This is an object at 5cm used to focus the camera to 5cm.

![Test Focus](https://github.com/opensourcebeehives/OSBHLogger/blob/master/documentation/images/13_focustest.jpg)

###Add IR LEDs
With the camera focused, you are now free to add the IR LEDs to the camera case. Since we are using a 12V supply, 5 LEDs in series with a 100 Ohm and a 47 Ohm resistor will give the desired brightness. These LEDs can be soldered together then stuck to the case using thick double sided tape.

![Case with LEDs](https://github.com/opensourcebeehives/OSBHLogger/blob/master/documentation/images/14_casewithled.jpg)

This is an older model case that used 7 IR LEDs.

Next, run wires to provide power from the LEDs on the case to the headers right next to the camera cable on the Sleepy Pi. These headers are controlled by the Sleepy Pi so that the lights switch off when video recording is completed. The header closest to the edge of the board is `VExt` or a direct connection to the external battery pack, and the header right next to it is ground.

![LED Power Headers](https://github.com/opensourcebeehives/OSBHLogger/blob/master/documentation/images/15_powerheaders.jpg)

----
##Build Power Switch
The last piece of hardware needed is the power switch. This switch can be soldered between the screw terminal and the battery pack as shown below. The ground wire will still need to be attached to the screw terminal and an extra wire will need to be added between the screw terminal and the power switch.

![Power Switch](https://github.com/opensourcebeehives/OSBHLogger/blob/master/documentation/images/16_powerswitch.jpg)

----
##Change ID and Prepare for Logging
The final steps before the OSBHLogger is ready involves working in the terminal.

First, boot up the Raspberry Pi with the hardware jumper **on** if it is not on already. You will be booted into the home directory of the system. 

Type `cd OSBHLogger/` to move into the folder containing the program. 

Type `nano info.txt` to open up the information about this particular OSBHLogger. 

Within this window, you will see the text looks like the following:

    default
    1

The first line is the ID of the datalogger. If you are using the OSBH data system, please contact us and we will give you an ID for your system so your data can be easily ingested and analyzed by our team. If not, feel free to use any ID you would like. The data from the system will look something like this `waffle_1_a.wav waffle_2_a.wav` and so on if you started with an info file that looked like this:

    waffle
    1

**Warning**: if you put the name on any other line than the first, or change the number in the second line, your data may corrupt!

When you have entered an ID for your Logger, hit `Crtl+X` then `y` then `Enter` to save and exit the editor.

To complete the process, type `crontab -e`. This will bring up another editor window. On the line that says `#@reboot /home/pi/OSBHLogger/on_reboot.sh &` delete the `#` so it reads `@reboot /home/pi/OSBHLogger/on_reboot.sh &`.

Finally hit `Crtl+X` then `y` then `Enter` to save and exit the editor. Then type `sudo shutdown -h now` to power off the Raspberry Pi, and when it has completed shutting off kill the power.

Move the hardware jumper into the **off** position as shown below:

![Hardware Jumper Off](https://github.com/opensourcebeehives/OSBHLogger/blob/master/documentation/images/17_hwjump-OFF.jpg)

Your OSBHLogger is nearly ready to go! Plug in the USB hub with your memory stick and sound card and remove the keyboard and monitor. The next time the power is switched on to the Sleepy Pi, the program will run and the Raspberry Pi will take data. Attach the batteries and computer to the inside of a case of your choice and put it in a beehive!

![Beehive](https://github.com/opensourcebeehives/OSBHLogger/blob/master/documentation/images/18_hive.jpg)

----
##Known Issues
* *If power is lost or removed while the recorder is taking data, it may overwrite previous data* - Sadly this is unavoidable. To ensure this doesn't happen, make sure all the lights are off before switching off your system!

* *The clock is always wrong, and the data is timestamped with weird dates* - This has something to do with the RTC on the Sleepy Pi and we are looking into it
