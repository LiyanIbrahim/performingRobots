//This example drives a robot in left and right arcs, driving in an overall wiggly course.
//  It demonstrates the variable control abilities. When used with a RedBot chassis,
//  each turn is about 90 degrees per drive.
//
//  Pin 8 can be grounded to disable motor movement, for debugging.

#include <Arduino.h>
#include <stdint.h>
#include "SCMD.h"
#include "SCMD_config.h" //Contains #defines for common SCMD register names and values
#include "Wire.h"
#include "SparkFun_Qwiic_MP3_Trigger_Arduino_Library.h" //http://librarymanager/All#SparkFun_MP3_Trigger
MP3TRIGGER mp3;

SCMD myMotorDriver; //This creates the main object of one motor driver and connected slaves.

long previousForwardMillis = 0;
long interval = 400;
long previousMillis2 = 0;
long interval2 = 600;
long previousMillis3 = 0;
long interval3 = 1000;
long previousStopMillis = 0;
void setup()
{
  pinMode(8, INPUT_PULLUP); //Use to halt motor movement (ground)

  Serial.begin(9600);
  Serial.println("Starting sketch.");

  //***** Configure the Motor Driver's Settings *****//
  //  .commInter face is I2C_MODE
  myMotorDriver.settings.commInterface = I2C_MODE;

  //  set address if I2C configuration selected with the config jumpers
  myMotorDriver.settings.I2CAddress = 0x5D; //config pattern is "1000" (default) on board for address 0x5D

  //  set chip select if SPI selected with the config jumpers
  myMotorDriver.settings.chipSelectPin = 10;

  //*****initialize the driver get wait for idle*****//
  while ( myMotorDriver.begin() != 0xA9 ) //Wait until a valid ID word is returned
  {
    Serial.println( "ID mismatch, trying again" );
    delay(500);
  }
  Serial.println( "ID matches 0xA9" );

  //  Check to make sure the driver is done looking for slaves before beginning
  Serial.print("Waiting for enumeration...");
  while ( myMotorDriver.ready() == false );
  Serial.println("Done.");
  Serial.println();

  //*****Set application settings and enable driver*****//

  //Uncomment code for motor 0 inversion
  //while( myMotorDriver.busy() );
  //myMotorDriver.inversionMode(0, 1); //invert motor 0

  //Uncomment code for motor 1 inversion
  while ( myMotorDriver.busy() ); //Waits until the SCMD is available.
  myMotorDriver.inversionMode(1, 1); //invert motor 1

  while ( myMotorDriver.busy() );
  myMotorDriver.enable(); //Enables the output driver hardware
  //Check to see if Qwiic MP3 is present on the bus
  if (mp3.begin() == false)
  {
    Serial.println("Qwiic MP3 failed to respond. Please check wiring and possibly the I2C address. Freezing...");
    while (1);
  }

  mp3.setVolume(10); //Volume can be 0 (off) to 31 (max)

}

#define LEFT_MOTOR 0
#define RIGHT_MOTOR 1
void loop()
{
  unsigned long currentMillis = millis();

  stopping(); //stopping motors
  previousStopMillis = currentMillis; // keep updating previousForwardMillis
  if (currentMillis - previousStopMillis >= interval) { //if time ellapsed is greater than 4secs, move the motors (I only want to stop them for 4 secs)
    mp3.playTrack(2); //play this song
    Serial.println("in first if");
    myMotorDriver.setDrive( LEFT_MOTOR, 0, 70);
    myMotorDriver.setDrive( RIGHT_MOTOR, 1, 70);
    previousStopMillis = currentMillis; //update the timer, I dont know why this is here. Should it be here? 
    if (currentMillis - previousForwardMillis >= interval) { // only go forward for 4secs (so if time is greater then stop it
      stopping();
      Serial.println("in second if");
      previousForwardMillis = currentMillis;
    }
    previousForwardMillis = currentMillis; // I think i should remove this (?) 
  }
  //  delay (3000);
  //  // go forward for 4 seconds
  //  //goStraight();
  //  Serial.println(currentMillis);
  //  Serial.println("going forward");
  //  mp3.playTrack(2);
  //  myMotorDriver.setDrive( LEFT_MOTOR, 0, 70);
  //  myMotorDriver.setDrive( RIGHT_MOTOR, 1, 70);
  //  //Serial.println("inside if statement");
  //  //delay(4000);
  //  //previousForwardMillis = currentMillis;
  //  //  if (currentMillis >= forwardInterval) {
  //  //    stopping();
  //  //  }
  //
  //
  //  Serial.println("left if statement");
  //  stopping();
  //  //previousForwardMillis = currentMillis;
  //  //delay (250);
  //  turningRight();
  //  //  myMotorDriver.setDrive( LEFT_MOTOR, 0, 70);
  //  //  myMotorDriver.setDrive( RIGHT_MOTOR, 1, 70);
  //  stopping();
  //  delay (3000);
  //  turning45();
  //  stopping();
  //  delay (3000);
  //  turning45();
  //  stopping();
  //  delay (3000);
  //  turning45();
  //  stopping();
  //  delay (1000);
  while (1)
    ;
}
// FUNCTIONS
// function that lets my robot go straight for 4secs
void goStraight() {

  Serial.println("going forward");
  mp3.playTrack(2); //Begin playing the first track on the SD card
  Serial.println("All done!");
  myMotorDriver.setDrive( LEFT_MOTOR, 0, 70);
  myMotorDriver.setDrive( RIGHT_MOTOR, 1, 70);
  //delay(4000);
  Serial.println("done going forward");

}
//function that makes it stop
void stopping() {
  Serial.println("starting to stop");
  myMotorDriver.setDrive( LEFT_MOTOR, 0, 0); //Stop motor
  myMotorDriver.setDrive( RIGHT_MOTOR, 0, 0); //Stop motor
}
//function for turning right

void turningRight() {
  Serial.println(" turning right");
  myMotorDriver.setDrive( LEFT_MOTOR, 0, 70);
  myMotorDriver.setDrive( RIGHT_MOTOR, 0, 45);
  //stopping();
  delay(600);
  //mp3.playTrack(2); //Begin playing the first track on the SD card

  //Serial.println("All done!");
  Serial.println("done going turning right");
}

void turning45() {
  Serial.println(" turning left");
  myMotorDriver.setDrive( LEFT_MOTOR, 0, 45);
  myMotorDriver.setDrive( RIGHT_MOTOR, 0, 70);

  //mp3.playTrack(2); //Begin playing the first track on the SD card

  //Serial.println("All done!");
  delay(1000);
  Serial.println("done turning left");
}
