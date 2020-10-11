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
#include <SparkFun_Qwiic_Button.h>

//create objects
QwiicButton button ;
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

  //Button setup
  if (button.begin() == false) {
    Serial.println("Device did not acknowledge! Freezing.");
    while (1);
  }
  Serial.println("Button acknowledged.");

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


int pressed = 0; //used to detect button pressing

#define LEFT_MOTOR 0
#define RIGHT_MOTOR 1

void loop() {
  if (button.isPressed() == true) {
    pressed = 1;
  }

  if (pressed == 1) {
    mp3.playTrack(1); // start playing the first track
    printing1(); // print the first message
    stopping(); //stop
    delay(2000);
    printing2(); //print second message
    //delay(2000);
    myMotorDriver.setDrive( LEFT_MOTOR, 0, 70); //move forward
    myMotorDriver.setDrive( RIGHT_MOTOR, 1, 70);
    delay(4000);
    stopping(); // stop again
    delay(2000);
    //    smileyFACE();
    //    delay(1000);
    printing3(); //print third message
    turningRight(); //turn right
    stopping(); // stop
    delay (1000);
    printing4(); //print forth message
    turning45(); // turn
    stopping(); // stop
    delay (1000);
    printing5(); //print message
    turning45(); //turn
    stopping(); //stop
    delay (1000);
    testfillcircle(); // print the sircular pattern
    heart(); //print heart scrolling
    delay(1000);
    //    turning45();
    //    stopping();
    // delay (1000);
    printing6(); //print message
    turning45(); // turn
    //printing6();
    stopping(); //stop
    delay (1000);
    printing7(); //print message
    stopping(); // stop
    delay (3000);
    aAA(); //print aAAA
    delay(500);
    mp3.playTrack(2); //play second "dying" track
    destructionDANCE(); // do the destruction dance
    testfilltriangle(); // while doing the dance, display this pattern
    stopping(); // stop
    delay(1000);
    display.clearDisplay();
  }
  pressed = 0; // set pressed back to 0
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
  Serial.println("done turning right");
}

void turning45() {
  Serial.println(" turning left");
  myMotorDriver.setDrive( LEFT_MOTOR, 0, 45);
  myMotorDriver.setDrive( RIGHT_MOTOR, 0, 70);
  delay(1000);
  Serial.println("done turning left");
}
void printing1() {
  display.clearDisplay();
  display.setTextSize(3);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(10, 10);
  display.println(F("Hello humans,"));
  display.display();
  //delay(100);
}
void printing2() {
  display.clearDisplay();
  display.setTextSize(2);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(2, 2);
  display.println(F("Despite"));
  display.println(F("what"));
  display.println(F("you've"));
  display.println(F("seen"));
  display.display();
  //delay(1000);
}
void printing3() {
  display.clearDisplay();
  display.setTextSize(2);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(2, 2);
  display.println(F("I am a"));
  display.println(F("very useful"));
  display.println(F("robot"));
  display.display();
  //delay(100);
}
void printing4() {
  display.clearDisplay();
  display.setTextSize(2);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(2, 2);
  display.println(F("I can"));
  display.println(F("deliver"));
  display.println(F("sanitizer"));
  display.display();
  // delay(100);
}
void printing5() {
  display.clearDisplay();
  display.setTextSize(2);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(2, 2);
  display.println(F("Prevent"));
  display.println(F("Covid"));
  display.display();
  //delay(100);
}
void printing6() {
  display.clearDisplay();
  display.setTextSize(2);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(2, 2);
  display.println(F("If you"));
  display.println(F("don't"));
  display.println(F("believe"));
  display.println(F("me"));
  display.display();
  // delay(100);
}
void printing7() {
  display.clearDisplay();
  display.setTextSize(2);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(5, 5);
  display.println(F("I WILL"));
  display.println(F("SELF"));
  display.println(F("DESTRUCT"));
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

void aAA() {
  display.clearDisplay();
  display.setTextColor(WHITE);
  display.setCursor(0, 0);
  display.setTextSize(1);
  display.print("A");
  display.setTextSize(2);
  display.print("A");
  display.setTextSize(3);
  display.print("A");
  display.setTextSize(4);
  display.print("A");
  display.setTextSize(5);
  display.print("A");
  display.setTextSize(6);
  display.print("A");
  display.display();
}

void testfillcircle() {
  // for (int j = 0; j < 8; j++) {
  display.clearDisplay();

  for (int16_t i = max(display.width(), display.height()) / 2; i > 0; i -= 3) {
    // The INVERSE color is used so circles alternate white/black
    display.fillCircle(display.width() / 2, display.height() / 2, i, SSD1306_INVERSE);
    display.display(); // Update screen with each newly-drawn circle
    //delay(1);
  }
  // }
  turning45();
  stopping();
  // delay(2000);
}
void testfilltriangle() {
  for (int j = 0; j < 8; j++) {
    display.clearDisplay();

    for (int16_t i = max(display.width(), display.height()) / 2; i > 0; i -= 5) {
      // The INVERSE color is used so triangles alternate white/black
      display.fillTriangle(
        display.width() / 2  , display.height() / 2 - i,
        display.width() / 2 - i, display.height() / 2 + i,
        display.width() / 2 + i, display.height() / 2 + i, SSD1306_INVERSE);
      display.display();
      //delay(1);
    }
  }
  display.clearDisplay();
}
void destructionDANCE() {
  // Serial.println("Self destructing");
  myMotorDriver.setDrive( LEFT_MOTOR, 0, 100);
  myMotorDriver.setDrive( RIGHT_MOTOR, 0, 60);
  delay(10000);
}
