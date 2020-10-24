// This performance is of Shakespeare's "As You Like it" play, scene 4 act 1 in which my robot plays Rosalind
//Done by Liyan Ibrahim


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
  mp3.setVolume(20);

  //OLED setup
  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3D)) {
    Serial.println(F("SSD1306 allocation failed"));
    for (;;); // Don't proceed, loop forever
  }

  //Show initial display buffer contents on the screen
  // the library initializes this with an Adafruit splash screen.
  display.display();
  delay(2000); // Pause for 2 seconds
  // Clear the buffer
  display.clearDisplay();
  //mp3.playTrack(1);
}

#define LEFT_MOTOR 0
#define RIGHT_MOTOR 1
void loop() {
  mp3.playTrack(1);
  startingPRINT();
  //starting scene
  stopping();
  delay(2000);//stop for 2 secs
  
  //second scene (0:21)
  Serial.println(" Scene2");
  heart();
  stopping();
  delay(1000);
  stopping();
  delay(600);
  myMotorDriver.setDrive( LEFT_MOTOR, 0, 70); //move forward
  myMotorDriver.setDrive( RIGHT_MOTOR, 1, 70);
  delay(2000);
  Serial.println("Done moving forward");
  stopping();
  delay(900);//stop for 1 secs
  Serial.println("Done stopping");
  turning45(); //turn to face the other way
  stopping();
  delay(900);// until she finishes the line 


  //third scene when he speak
  Serial.println("Scene3, hes speaking");
  //until he finishes his line then stop --> he will move towards her

  //scene 4
  Serial.println(" Scene4");
  moveForward();
  delay(1000);// away from him
  turningRight(); //turn so that you are facing the doll
  stopping();
  delay(1000); //until her line ends (0:33)

  //scene 5 (his scene)
  Serial.println(" Scene5");
  stopping();
  delay(400); 

  //scene 6 (she speaks without moving)
  Serial.println(" Scene6");
  stopping();
  delay(700);

  //scene 7  he speaks
  Serial.println(" Scene7");
  stopping();
  delay(300); //until his line ends (0:41)

  // scene 8 (she speaks)
  Serial.println(" Scene8");
  stopping();
  delay(600);

  //scene 9(he speaks)
  Serial.println("Scene9");
  stopping();
  delay(600);

  //scene 10
  Serial.println("Scene10");
  moveinCircle();//turn in circle

  //scene 11 (his scene)
  //Serial.println("Scene10");
  stopping();
  delay(1000);

  //scene 12 until 1:06  
  //Serial.println("Scene10"); 
  moveForward();
  delay(1000);
  turningRight();
  stopping();
  delay(2400);
  turning45();
  turning45();
  
  //scene 13 his scene
  //Serial.println("Scene10");
  stopping();
  delay(8000);
  moveinCircle();
  stopping();
  delay(15000);
  moveinCircle();
  delay(6000);
  stopping();
  delay(9000);

  //end play
  endingPRINT();

  while (1);


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
  delay(1000);
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
