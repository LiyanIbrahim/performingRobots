void setup()
{
  pinMode(4,OUTPUT);//setup for blue-wire LED 
  pinMode(6,OUTPUT);//setup for brown-wire LED 
  pinMode(8, OUTPUT);//setup for pink-wire LED 
  pinMode(10,OUTPUT);//setup for grey-wire LED
  pinMode(12,OUTPUT);//setup for orange-wire LED 
}

//function declaration 
void blinkAfterEachOther();
void blinkTwice();
void blinkthreetimes();
void jingleBells();

void loop()
{
  //switch 1 (purple wire)
  int switchP = digitalRead(2);
  if (switchP == HIGH)
  { 
    for (int i=0;i<=2;i++) //run the first pattern 3 times
    { 
      blinkAfterEachOther();    
    }
    blinkTwice(); // then run blink twice  
  }
  //switch 2 (yellow wire) 
  int switchY = digitalRead(3);
  if (switchY == HIGH) // if switch is pressed, run the jingle bells function once 
  {
    jingleBells();
  }
}

//function definitions
void blinkAfterEachOther() // function for switch 1 that allows the LEDs to blink one after another
{
  for(int i=4;i<=12;i=i+2) //for every LED (iteration is by 2 since they are connected to even terminals)
  {
    digitalWrite(i,HIGH);
    delay(150);
    digitalWrite(i,LOW);
  }
}
void blinkTwice() //allows all the lights to blink together twice 
{
  for (int i=0;i<2;i++) // loop iterates twice turning all LEDs on/off together  
  {
    digitalWrite(4,HIGH);
    digitalWrite(6,HIGH);
    digitalWrite(8,HIGH);
    digitalWrite(10,HIGH);
    digitalWrite(12,HIGH);
    delay(250);
    digitalWrite(4,LOW);
    digitalWrite(6,LOW);
    digitalWrite(8,LOW);
    digitalWrite(10,LOW);
    digitalWrite(12,LOW);
    delay(250);
  }
}
void blinkthreetimes() // used in the jingleBells function, makes pink-wire LED blink 3 times 
{
   for (int i=0;i<3;i++)
  {
    digitalWrite(8,HIGH);
    delay(170);
    digitalWrite(8,LOW);
    delay(170);
  }
}
void jingleBells() // LEDs match the first tune of the song Jingle Bells
{
  blinkthreetimes();
  delay(350);
  blinkthreetimes();
  delay(350);
  digitalWrite(8,HIGH);
  delay(170);
  digitalWrite(8,LOW);
  delay(350);
  digitalWrite(4,HIGH);
  delay(170);
  digitalWrite(4,LOW);
  delay(350);
  digitalWrite(12,HIGH);
  delay(170);
  digitalWrite(12,LOW);
  delay(350);
  digitalWrite(10,HIGH);
  delay(170);
  digitalWrite(10,LOW);
  delay(350);  
  digitalWrite(8,HIGH);
  delay(170);
  digitalWrite(8,LOW);
  delay(350);
}
