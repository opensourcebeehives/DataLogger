/* 
 *  SleepyPi_FW - Firmware developed for a SleepyPi2 (http://spellfoundry.com/products/sleepy-pi-2/)
 *  To be used with a Raspberry Pi Model A+ for the Open Source Beehives Project (http://opensourcebeehives.net/)
 *  Wakes up every 15 minutes, waits for data to be taken and controls IR LEDs for the camera
 *  
 *  Teddy Lowe, October 2016
 *  CC BY-NC-SA
 *  
 *  Based on code from the University of Kent (http://www.instructables.com/id/ARUPi-A-Low-Cost-Automated-Recording-Unit-for-Soun/)
 *  
 */

// **** INCLUDES *****
#include "SleepyPi2.h"
#include <Time.h>
#include <LowPower.h>
#include <PCF8523.h>
#include <Wire.h>

// LED pin
const int LED_PIN = 13;
// Pi status
bool PI_WAKING_UP_FROM_SLEEP = true;
// Counter for number of times to check before switching off
int deadCounter = 0;
int videoCounter = 0;
// Battery Voltage Dead Value, where 1 = 0.06V, in this case 156 = 9.4V
int deadValue = 156;

// Globals
// ++++++++++++++++++++ Change me ++++++++++++++++++
// .. Setup the Periodic Timer
// .. use either eTB_SECOND or eTB_MINUTE or eTB_HOUR
eTIMER_TIMEBASE  PeriodicTimer_Timebase     = eTB_MINUTE;   // e.g. Timebase set to seconds
uint8_t          PeriodicTimer_Value        = 9;           // Timer Interval in units of Timebase e.g 10 seconds
// ++++++++++++++++++++ End Change me ++++++++++++++++++


void alarm_isr()
{
  PI_WAKING_UP_FROM_SLEEP = true;
}

void setup()
{ 
  // Configure "Standard" LED pin
  pinMode(LED_PIN, OUTPUT);		
  digitalWrite(LED_PIN,HIGH);		// Switch on LED

  // Battery Voltage ADC
  pinMode(A6, INPUT);

  SleepyPi.enablePiPower(false);
  SleepyPi.enableExtPower(false);

  // initialize serial communication: In Arduino IDE use "Serial Monitor"
  Serial.begin(9600);
  Serial.println("Starting...");
  delay(50);

  // Initialize the RTC
  SleepyPi.rtcInit(true);

  delay(200);
  digitalWrite(LED_PIN,LOW);   // Switch off LED

  Serial.println("Initial piHandler");
  piHandler();
  
/*
  // Check the battery voltage, a value of 1 = 0.06V, if it is too low, go back to sleep
  if (analogRead(A6) <= deadValue){
    flashLED(6, 500);
    break;
  }
    
  // It will sit in this loop until the dead counter gets too high
  while(1)
  {
    // If just finished the interrupt, wake up the pi
    if (PI_WAKING_UP_FROM_SLEEP){
      wakePiUp();
    }else{
      if(SleepyPi.checkPiStatus(false)){  // If the pi is awake, reset the dead counter
        deadCounter = 0;
        videoCounter++;
        //digitalWrite(LED_PIN, HIGH);
        //Serial.println("Pi awake");
        Serial.println(videoCounter);
        
      }else{                              // If the pi is not detected, count up on the dead counter
        digitalWrite(LED_PIN, LOW);
        videoCounter = 0;
        deadCounter++;
        Serial.println(deadCounter);
      }
    }
    if (deadCounter >= 6){ // If the pi still isn't detected, it hasn't switched on in time or is totally shut down, so kill it
      deadCounter = 0;
      break;
    }
    //if (videoCounter == 4){
    //  SleepyPi.enableExtPower(false);
    //}
    delay(5000);
  }
  */
}

void loop() 
{
    SleepyPi.enablePiPower(false);
    //SleepyPi.enableExtPower(false);
  
    SleepyPi.rtcClearInterrupts();

    // Allow wake up alarm to trigger interrupt on falling edge.
    attachInterrupt(0, alarm_isr, FALLING);    // Alarm pin

    Serial.println("Sleeping...");

    // Set the Periodic Timer
    SleepyPi.setTimer1(PeriodicTimer_Timebase, PeriodicTimer_Value);

    delay(500);

    // Enter power down state with ADC and BOD module disabled.
    // Wake up when wake up pin is low.
    SleepyPi.powerDown(SLEEP_FOREVER, ADC_OFF, BOD_OFF); 

    // Disable external pin interrupt on wake up pin.
    detachInterrupt(0);
    
    SleepyPi.ackTimer1();

    Serial.println("Main piHandler");
    piHandler();

    //digitalWrite(LED_PIN,HIGH);    // Switch on LED
    //delay(50);
    //digitalWrite(LED_PIN,LOW);    // Switch off LED 
    //delay(50);
    //digitalWrite(LED_PIN,HIGH);    // Switch on LED
    //delay(50);
    //digitalWrite(LED_PIN,LOW);    // Switch off LED   
}

void wakePiUp() {
  Serial.println("Wake up pi");
  // Wake PI up
  SleepyPi.enablePiPower(true);
  delay(3000);
  // Uncomment if we want to use EXT power for things
  //SleepyPi.enableExtPower(true);
  digitalWrite(LED_PIN, HIGH);
  PI_WAKING_UP_FROM_SLEEP = false;
}

void flashLED(int amount, int delaytime){
  int ii;

  for (ii = 0; ii < amount; ii++){
    digitalWrite(LED_PIN,HIGH);    // Switch on LED
    delay(delaytime);
    digitalWrite(LED_PIN,LOW);    // Switch off LED 
    delay(delaytime);
  }
}

void piHandler(){
  // Check the battery voltage, if it is too low, go back to sleep
  Serial.println("Battery check");
  if (analogRead(A6) <= deadValue){
    Serial.println("Batteries low, exiting");
    flashLED(6, 500);
    return;
  }
  // It will sit in this loop until the dead counter gets too high
  Serial.println("Main loop");
  while(1)
  {      
    // If just finished the interrupt, wake up the pi
    if (PI_WAKING_UP_FROM_SLEEP){
      Serial.println("Waking up pi");
      wakePiUp();
    }else{
      if(SleepyPi.checkPiStatus(false)){  // If the pi is awake, reset the dead counter
        deadCounter = 0;
        videoCounter++;
        //digitalWrite(LED_PIN, HIGH);
        Serial.println("Pi awake");
        //Serial.println(videoCounter);
        
      }else{                              // If the pi is not detected, count up on the dead counter
        digitalWrite(LED_PIN, LOW);
        //videoCounter = 0;
        deadCounter++;
        Serial.print("Dead counter: ");
        Serial.println(deadCounter);
      }
    }
    if (deadCounter >= 6){ // If the pi still isn't detected, it hasn't switched on in time or is totally shut down, so kill it
      Serial.println("Pi not detected, exiting");
      flashLED(2, 50);
      deadCounter = 0;
      break;
    }
    //if (videoCounter == 4){
    //  SleepyPi.enableExtPower(false);
    //}
    delay(5000);
  }
}

