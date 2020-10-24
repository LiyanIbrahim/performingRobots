// This performance is of Shakespeare's "As You Like it" play, scene 4 act 1 in which my robot plays Rosalind


#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Arduino.h>
#include <stdint.h>
#include "SCMD.h"
#include "SCMD_config.h"
#include "Wire.h"
#include "SparkFun_Qwiic_MP3_Trigger_Arduino_Library.h"


//create objects

MP3TRIGGER mp3;
SCMD myMotorDriver;
#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels


#define OLED_RESET     4
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);


#define LOGO_HEIGHT   16
#define LOGO_WIDTH    16

void setup() {
  Serial.begin(9600);

  //motor setup
  pinMode(8, INPUT_PULLUP);
  //  Serial.begin(9600);
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

  //OLED setup
  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3D)) {
    Serial.println(F("SSD1306 allocation failed"));
    for (;;); // Don't proceed, loop forever
  }

  // Show initial display buffer contents on the screen --
  // the library initializes this with an Adafruit splash screen.
  display.display();
  delay(2000); // Pause for 2 seconds
  // Clear the buffer
  display.clearDisplay();

}

void loop() {
  startingPRINT();
  //starting scene
  void stopping()
  delay(2000);//stop for 2 secs
  //void playTRACK1();

  heart();
  void stopping();//still stopping
  delay (1000);//till track is done
  //second scene
  //void playTRACK2();
  void moveForward();
  delay(3000);
  void stopping()
  delay(1000);//stop for 1 secs
  void turn45(); //turn tp face the other way
  delay(2000);
  //scene 3
  void moveForward();
  delay(2000);//until the dude finishes the line
  //play track 3
  delay(2000); //keep moving forward
  void turningRight(); //turn so that you are facing the doll
  void stopping();//stop and the dude will speak
  //scene 4
  //play track();
  void stopping();
  delay(4000); // stay stopped until dude stops speaking
  //dude speaks
  //play aother track
  moveinCircle();//turn in circle
  //scene 5
  stopping();//dude speaks
  delay(2000); //dude speaks and sits
  //play track
  chaos();//move choatically
  stopping();// until midsummer night then
  delay(4000);//stop and sit next to barbie doll

  stopping();// until midsummer night then
  delay(7000);//stop and sit next to barbie doll
  endingPRINT();
  // dude speaks
  // and moves
  //play track
  // play trcak while still stopping
  // dude will speak (i want to end it here)
  while(1);
}

//functions for moving performance (most of the actions are made as a combination of these functions)
void stopping() {
  Serial.println("starting to stop");
  myMotorDriver.setDrive( LEFT_MOTOR, 0, 0); //Stop motor
  myMotorDriver.setDrive( RIGHT_MOTOR, 0, 0); //Stop motor
}
void moveForward() { // adapt it so it is in an arc
  myMotorDriver.setDrive( LEFT_MOTOR, 0, 70); //move forward
  myMotorDriver.setDrive( RIGHT_MOTOR, 1, 70);
}

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
void moveinCircle() {
  // Serial.println("Self destructing");
  myMotorDriver.setDrive( LEFT_MOTOR, 0, 100);
  myMotorDriver.setDrive( RIGHT_MOTOR, 0, 60);
  delay(2000);
}
void chaos() { //adjust this when trying this out
  moveForward();
  delay(2000);
  myMotorDriver.setDrive( LEFT_MOTOR, 1, 70); //move backward
  myMotorDriver.setDrive( RIGHT_MOTOR, 1, 70);
  delay (2000);
  turningRight();
  turning45();
}
void startingPRINT() {
  display.clearDisplay();
  display.setTextSize(3);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(10, 10);
  display.println(F("START SCENE"));
  display.display();
}

void heart() {
  display.clearDisplay();
  display.setCursor(20, 20);
  display.setTextSize(5);
  display.write(3);
  display.display();

  // Display ASCII Characters
  display.startscrollright(0x00, 0x07);
  delay(200);
  display.stopscroll();
  delay(200);
  display.startscrollleft(0x00, 0x07);
  delay(200);
  display.stopscroll();
  delay(200);
  display.startscrolldiagright(0x00, 0x07);
  delay(200);
  display.startscrolldiagleft(0x00, 0x07);
  delay(200);
  display.stopscroll();
  display.clearDisplay();

}

void endingPRINT() {
  display.clearDisplay();
  display.setTextSize(3);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(10, 10);
  display.println(F("END SCENE"));
  display.display();
}
