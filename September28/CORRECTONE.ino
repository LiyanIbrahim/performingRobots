/**************************************************************************
  This code combines different parts of (Example1_PrintButtonStatus) and the OLED example (SSD1306_128x64_i2C)
 **************************************************************************/
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <SparkFun_Qwiic_Button.h>
QwiicButton button;
#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels
// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
#define OLED_RESET     4 // Reset pin # (or -1 if sharing Arduino reset pin)
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);
#define LOGO_HEIGHT   16
#define LOGO_WIDTH    16


int numberofPress = 0; // counter for the number of times a user presses
void setup() {
  Serial.begin(9600);
  //setup for OLED
  // SSD1306_SWITCHCAPVCC = generate display voltage from 3.3V internally
  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3D))
  { // Address 0x3D for 128x64
    Serial.println(F("SSD1306 allocation failed"));
    for (;;); // Don't proceed, loop forever
  }
  //setup for Button
  if (button.begin() == false) 
  {
    Serial.println("Device did not acknowledge! Freezing.");
    while (1);
  }
  Serial.println("Button acknowledged.");

  printReady();    // print "Ready"
}

void loop() {
  if (button.isPressed() == true) {
    display.clearDisplay();
    Serial.println("The button is pressed!");
    pressed(); // print "Pressed" 
    numberofPress++; //increment count of presses
    display.clearDisplay();
    while (button.isPressed() == true)
      delay(10);  //wait for user to stop pressing
    Serial.println("The button is not pressed!");
    notPressed(); // print the count 
    display.clearDisplay();
  }
  delay(20); //Don't hammer too hard on the I2C bus
}

//function that prints "Ready" in setup 
void printReady(void) {
  display.clearDisplay();
  display.setTextSize(3); 
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(10, 10);
  display.println(F("Ready"));
  display.display();      
  delay(100);
}

//function that prints "Pressed" 
void pressed() {
  display.clearDisplay();
  display.setTextSize(2); 
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(10, 10);
  display.println(F("Pressed"));
  display.display();      
  //delay(100);
}

//function that prints the count 
void notPressed() {
  display.clearDisplay();
  display.setTextSize(2);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(10, 10);
  display.println(F("Count: "));
  display.println(numberofPress);
  display.display();     
 // delay(100);
}
