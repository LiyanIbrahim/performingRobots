
//This is the code for my final project which is a performace using Nizar qabbani's poem "A lesson is Drawing"
//Link to Documentation+Video of Performance:
//https://github.com/LiyanIbrahim/performingRobots/blob/master/FinalProject/README.md


#include <Arduino.h>
#include <stdint.h>
#include "SCMD.h"
#include "SCMD_config.h"
#include "Wire.h"
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels
// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
#define OLED_RESET     4 // Reset pin # (or -1 if sharing Arduino reset pin)
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

//initializing Global Variables (helps with syncronization)
int initialWalkIntoTheScene = 1000;
int stopMotorForScene1 = 15000;
int moveFromScene1To2StraightLine = 2200;
//int moveFromScene1To2curveLine = 1000;
int displayFace2 = 900;
int moveFromScene2To3StraightLine = 1800;


int moveForwardinThirdScene = 1000;
int waitInThirdScene = 25000;
int movebackwardThirdScene = 1000; //same as forward

int leavingSceneTurn = 2000;

SCMD myMotorDriver; //This creates the main object of one motor driver and connected slaves.
MP3TRIGGER mp3;

void setup()
{
  Serial.begin(9600);

  //motor setup
  pinMode(8, INPUT_PULLUP);
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

  //OLED initialization
  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3D)) {
    Serial.println(F("SSD1306 allocation failed"));
    for (;;);
  }

  //Mp3 trigger setup
  if (mp3.begin() == false)
  {
    Serial.println("Qwiic MP3 failed to respond. Please check wiring and possibly the I2C address. Freezing...");
    while (1);
  }
  mp3.setVolume(20);

}

#define LEFT_MOTOR 0
#define RIGHT_MOTOR 1
int x = 0; //only do performance one
void loop()
{
  //stop motors so I can setup camera
  myMotorDriver.setDrive( LEFT_MOTOR, 0, 0);
  myMotorDriver.setDrive( RIGHT_MOTOR, 0, 0);
  delay(10000);

  while (digitalRead(8) == 0); //Hold if jumper is placed between pin 8 and ground

  //to play the performance only once
  if (x == 0) {
    mp3.playTrack(1);
    //performace by calling the functions (filmed in 2 takes)
    scene1();
    transitionToScene2();
    scene2();
    transitionToScene3();
    //    delay(300);
    scene3();
    transitionToScene4();
    scene4();
    //while (1);
    x++;
  }
}

void scene1() {
  // go forward into the scene
  Serial.println("In scene 1");
  //move forward into scene
  myMotorDriver.setDrive( LEFT_MOTOR, 0, 100);
  myMotorDriver.setDrive( RIGHT_MOTOR, 1, 100);
  delay(initialWalkIntoTheScene);
  Serial.println("done moving forward");
  // stop the motors until I place the box on it (adjust to sync with audio)
  Serial.println("starting to stop");
  myMotorDriver.setDrive( LEFT_MOTOR, 0, 0);
  myMotorDriver.setDrive( RIGHT_MOTOR, 0, 0);
  delay(stopMotorForScene1);

  // wiggles when I put the box on, wiggle
  Serial.println("Starting to wiggle");
  myMotorDriver.setDrive( LEFT_MOTOR, 0, 70);
  myMotorDriver.setDrive( RIGHT_MOTOR, 0, 45);
  delay(300);
  myMotorDriver.setDrive( LEFT_MOTOR, 1, 45);
  myMotorDriver.setDrive( RIGHT_MOTOR, 1, 70);
  delay(300);

  //stop  till end of scene (adjust delay so it's perfect)
  myMotorDriver.setDrive( LEFT_MOTOR, 0, 0);
  myMotorDriver.setDrive( RIGHT_MOTOR, 0, 0);
  delay(23000);
  Serial.println("done with scene1");
}

//function for moving between scene 1 and 2
void transitionToScene2() {
  //turn
  Serial.println("Starting transition to Scene2");
  myMotorDriver.setDrive( LEFT_MOTOR, 0, 100);
  myMotorDriver.setDrive( RIGHT_MOTOR, 0, 60);
  delay(1100); //perfect delay to make it turn to the correct face
  //move forward
  myMotorDriver.setDrive( LEFT_MOTOR, 0, 100);
  myMotorDriver.setDrive( RIGHT_MOTOR, 1, 100);
  delay(moveFromScene1To2StraightLine);
  //stop
  myMotorDriver.setDrive( LEFT_MOTOR, 0, 0);
  myMotorDriver.setDrive( RIGHT_MOTOR, 0, 0);
  delay(200);
  //show face
  turningtoShowFace(displayFace2);
  Serial.println("Ending Transition Scene2");
}

//scene that uses OLED
void scene2() {
  Serial.println("STARTING SCENE 2");
  // display on OLED
  oledSit();
  //stop motors
  myMotorDriver.setDrive( LEFT_MOTOR, 0, 0);
  myMotorDriver.setDrive( RIGHT_MOTOR, 0, 0);
  delay(10000);
  //move 1
  Serial.println("move1");
  myMotorDriver.setDrive( LEFT_MOTOR, 0, 100);
  myMotorDriver.setDrive( RIGHT_MOTOR, 0, 55);
  delay(200);
  //stop again
  myMotorDriver.setDrive( LEFT_MOTOR, 0, 0);
  myMotorDriver.setDrive( RIGHT_MOTOR, 0, 0);
  delay(10000);
  //move in circle
  Serial.println("moveCircle");
  myMotorDriver.setDrive( LEFT_MOTOR, 0, 100);
  myMotorDriver.setDrive( RIGHT_MOTOR, 0, 60);
  delay(2000); //make sure you face correct one
  //make sure you face correct one
  myMotorDriver.setDrive( LEFT_MOTOR, 0, 60);
  myMotorDriver.setDrive( RIGHT_MOTOR, 0, 100);
  delay(2000);
  //move forward slightly to another end
  Serial.println("move2");
  myMotorDriver.setDrive( LEFT_MOTOR, 0, 55);
  myMotorDriver.setDrive( RIGHT_MOTOR, 0, 100);
  delay(500);

  Serial.println("ending SCENE 2");
}
//long delay so I have an indication of when to start filming (seting up the camera and robot not incldued in this since I comment out the code for the first two scenes to do that)
void transitionToScene3() {
  Serial.println("delaying this! set up ur robot");
  delay(2000);
  Serial.println("delaying this! set up ur robot");
}
void scene3() {
  //move forward
  Serial.println("STARTING SCENE 3");
  myMotorDriver.setDrive( LEFT_MOTOR, 0, 100);
  myMotorDriver.setDrive( RIGHT_MOTOR, 1, 100);
  delay(200);
  //wait
  myMotorDriver.setDrive( LEFT_MOTOR, 0, 0);
  myMotorDriver.setDrive( RIGHT_MOTOR, 0, 0);
  delay(waitInThirdScene);
  //wiggle
  for (int i = 0; i < 5; i++) { //make this so its syncronized
    myMotorDriver.setDrive( LEFT_MOTOR, 0, 70);
    myMotorDriver.setDrive( RIGHT_MOTOR, 0, 45);
    delay(400);
    myMotorDriver.setDrive( LEFT_MOTOR, 1, 45);
    myMotorDriver.setDrive( RIGHT_MOTOR, 1, 70);
    delay(400);
  }
  //make sure its in the same orientation, if it is, stop
  myMotorDriver.setDrive( LEFT_MOTOR, 0, 0);
  myMotorDriver.setDrive( RIGHT_MOTOR, 0, 0);
  delay(500);
}

void transitionToScene4() {
  Serial.println("TRANSITION TO SCENE 4");
  //turn
  myMotorDriver.setDrive( LEFT_MOTOR, 0, 50);
  myMotorDriver.setDrive( RIGHT_MOTOR, 1, 100);
  delay(2000);
  //stop
  myMotorDriver.setDrive( LEFT_MOTOR, 0, 0);
  myMotorDriver.setDrive( RIGHT_MOTOR, 0, 0);
  delay(200);
  //stop (i dont need this but it was there in the code I used for the performance so I'll keep it here uncommented it out)
  myMotorDriver.setDrive( LEFT_MOTOR, 0, 0);
  myMotorDriver.setDrive( RIGHT_MOTOR, 0, 0);

}

void scene4() {
  Serial.println(" in 4");
  //robot will turn and leave the scene
  //turningtoShowFace(leavingSceneTurn);
  //stop
  myMotorDriver.setDrive( LEFT_MOTOR, 0, 0);
  myMotorDriver.setDrive( RIGHT_MOTOR, 0, 0);
  //leave scene
  myMotorDriver.setDrive( LEFT_MOTOR, 1, 100);
  myMotorDriver.setDrive( RIGHT_MOTOR, 0, 100);
  delay(3000); //stop filming so it doesnt matter
}

//function that takes a delay and turns the robot according to the delay 
void turningtoShowFace(int face) {
  Serial.println(" turning left");
  myMotorDriver.setDrive( LEFT_MOTOR, 0, 100);
  myMotorDriver.setDrive( RIGHT_MOTOR, 0, 50);
  delay(face);
  Serial.println("done turning left");
}

//displays on OLED "Memory Failed" phrase 
void oledSit() {
  display.clearDisplay();

  display.setTextSize(2);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(10, 0);
  display.println(F("Memory"));
  display.println(F("Failed"));
  display.display();      // Show initial text
  //delay(100);
}
