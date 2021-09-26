/*
This is the code for Module A NANO (master) of the twin stick controller by Oleg "Salty" Velichko, AKA Helgar Fenrir.
The controller features a total two 3-axis sticks and 12 buttons. Each of the sticks has a button on top,
one stick and 4 buttons (one of which is on the stick) on Module B, one stick and 8 buttons 
(one of which is on the stick) on Module A. The reason behind having nano's for I2C is the fact that
I need more leads than a single RJ45 can handle for Module B. The main controller is Arduino Micro.
If you have any questions or comments - find me on discord under the name "Salty NUggeTZ#6753"
N.B. - I like using VSCode to write my arduino sketches, so the look of this sketch in your IDE may differ slightly
*/

#include <Arduino.h> //make sure VSCode understands that this is an arduino sketch
#include <Wire.h>    //include the arduino I2C library
#define SLAVE_ADDR 42 //define slave address for Module B NANO (slave)

//define output pins to the MICRO
byte but1out = 8;
byte but2out = 7;
byte but3out = 6;

int pot1out = 10;
int pot2out = 9;
int pot3out = 5;
int pot4out = 3;

//define variables to hold the state of buttons and value of pots
byte but1state = 0;
byte but2state = 0;
byte but3state = 0;

int pot1val = 0;
int pot2val = 0;
int pot3val = 0;
int pot4val = 0;


//define a counter to count bytes in response
byte bcount;
 
//define an array for returned data
int getResponse[7];


//if you don't know what "void setup()" does - you probably shouldn't be reading this
void setup() 
{

pinMode(but1out, OUTPUT);
pinMode(but2out, OUTPUT);
pinMode(but3out, OUTPUT);

pinMode(pot1out, OUTPUT);
pinMode(pot2out, OUTPUT);
pinMode(pot3out, OUTPUT);
pinMode(pot4out, OUTPUT);

Wire.begin();
Serial.begin(115200);
}


byte readI2C(int address) 
{
  //define a variable to hold byte of data
  byte bval ;
  long entry = millis();
  //read one byte at a time
  Wire.requestFrom(address, 1); 
  //wait 20 ms for data to stabilize
  while (Wire.available() == 0 && (millis() - entry) < 20)  Serial.print("Waiting");
  //place data into byte
  if  (millis() - entry < 20) bval = Wire.read();
  return bval;
}


//you should know what "void loop()" does
void loop() 
{
while (readI2C(SLAVE_ADDR) < 255) 
{

}
  for (bcount = 0; bcount < 7; bcount++) 
  {
    getResponse[bcount] = readI2C(SLAVE_ADDR);
  }

  //record response values to variables to be used later
  pot1val = getResponse[0];
  pot2val = getResponse[1];
  pot3val = getResponse[2];
  pot4val = getResponse[3];

  but1state = getResponse[4];
  but2state = getResponse[5];
  but3state = getResponse[6];

  //reversing button state logic
  if (but1state == LOW)
  {but1state = 1;}
    else{but1state = 0;}

  if (but2state == LOW)
  {but2state = 1;}
    else{but2state = 0;}
  
  if (but3state == LOW)
  {but3state = 1;}
    else{but3state = 0;}


  //debugging - print received values to screen...
  Serial.print("p1v:"); Serial.print(pot1val); Serial.print(" p2v:"); Serial.print(pot2val); Serial.print( "p3v:");
  Serial.print(pot3val); Serial.print(" p4v:"); Serial.print(pot4val); Serial.print(" b1s:"); Serial.print(but1state);
  Serial.print(" b2s:"); Serial.print(but2state); Serial.print(" b3s:"); Serial.println(but3state);
  
  
  //output values to MICRO
  analogWrite(pot1out, pot1val);
  analogWrite(pot2out, pot2val);
  analogWrite(pot3out, pot3val);
  analogWrite(pot4out, pot4val);

  digitalWrite(but1out, but1state);
  digitalWrite(but2out, but2state);
  digitalWrite(but3out, but3state);
  
}
