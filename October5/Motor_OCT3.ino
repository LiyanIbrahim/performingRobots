
#include <Arduino.h>
#include <stdint.h>
#include "SCMD.h"
#include "SCMD_config.h"
#include "Wire.h"
#include "SparkFun_Qwiic_MP3_Trigger_Arduino_Library.h"
#include <SparkFun_Qwiic_Button.h>
//create objects
QwiicButton button;
MP3TRIGGER mp3;
SCMD myMotorDriver;

void setup()
{
  //motor setup
  pinMode(8, INPUT_PULLUP);
  Serial.begin(9600);
  Serial.println("Starting sketch.");
  myMotorDriver.settings.commInterface = I2C_MODE;
  myMotorDriver.settings.I2CAddress = 0x5D;
  myMotorDriver.settings.chipSelectPin = 10;
  while ( myMotorDriver.begin() != 0xA9 )
  {
    Serial.println( "ID mismatch, trying again" );
    delay(500);
  }
  Serial.println( "ID matches 0xA9" );
  Serial.print("Waiting for enumeration...");
  while ( myMotorDriver.ready() == false );
  Serial.println("Done.");
  Serial.println();
  while ( myMotorDriver.busy() );
  myMotorDriver.inversionMode(1, 1);
  while ( myMotorDriver.busy() );
  myMotorDriver.enable();

  //Mp3 trigger setup
  if (mp3.begin() == false)
  {
    Serial.println("Qwiic MP3 failed to respond. Please check wiring and possibly the I2C address. Freezing...");
    while (1);
  }
  mp3.setVolume(10);

  //Button setup
  if (button.begin() == false) {
    Serial.println("Device did not acknowledge! Freezing.");
    while (1);
  }
  Serial.println("Button acknowledged.");
}

int oneTime = 1; //used to play the pattern only once in the beginning
int pressed = 0; //used to detect button pressing
#define LEFT_MOTOR 0
#define RIGHT_MOTOR 1
void loop()
{
  if (oneTime == 1) { // do pattern only once
    mp3.playTrack(3);
    Serial.println("Original Pattern");
    pattern();
    oneTime++;
  }

  if (button.isPressed() == true) {
    pressed = 1;
  }
  if (pressed == 1) { // if the button is pressed again, play the pattern again but with a different song
    Serial.println("Second Pattern");
    mp3.playTrack(1);
    pattern();
  }
  pressed = 0;
}
// FUNCTIONS

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
  Serial.println("done turning right");
}

void turning45() {
  Serial.println(" turning left");
  myMotorDriver.setDrive( LEFT_MOTOR, 0, 45);
  myMotorDriver.setDrive( RIGHT_MOTOR, 0, 70);
  delay(1000);
  Serial.println("done turning left");
}
//pattern the robot follows 
void pattern() {
  stopping(); //stopping motors
  delay(2000);
  myMotorDriver.setDrive( LEFT_MOTOR, 0, 70);
  myMotorDriver.setDrive( RIGHT_MOTOR, 1, 70);
  delay(4000);
  stopping();
  delay (250);
  turningRight();
  stopping();
  delay (1000);
  turning45();
  stopping();
  delay (1000);
  turning45();
  stopping();
  delay (1000);
  turning45();
  stopping();
  delay (1000);
}
