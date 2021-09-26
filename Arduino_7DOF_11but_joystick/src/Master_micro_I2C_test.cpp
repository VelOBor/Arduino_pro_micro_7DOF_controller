/*
 
*/

#include <Arduino.h> //make sure VSCode understands that this is an arduino sketch
#include <Wire.h>    //include the arduino I2C library
#include <Joystick.h> //include the Joystick library
#define SLAVE_ADDR 42 //define slave address for Module B NANO (slave)

Joystick_ joystick; //create a joystick instance called "joystick"... Pretty inventive, huh...

//define input pins for the pots on Module A MICRO (local)
int xrotpot = A11;
int yrotpot = A0;
int zrotpot = A1;

//define the pins for the buttons on Module A MICRO (local)
int but4pin = 11;
int but5pin = 10;
int but6pin = 9;
int but7pin = 8;
int but8pin = 7;
int but9pin = 6;
int but10pin = 5;
int but11pin = 13;

//define variables to hold the state of buttons and value of pots
//remote
byte but1state = 0;
byte but2state = 0;
byte but3state = 0;
//local
byte but4state = 0;
byte but5state = 0;
byte but6state = 0;
byte but7state = 0;
byte but8state = 0;
byte but9state = 0;
byte but10state = 0;
byte but11state = 0;

//bytes to hold the button states to send to joystick library after debounce (??)
byte but1laststate = 0;
byte but2laststate = 0;
byte but3laststate = 0;
byte but4laststate = 0;
byte but5laststate = 0;
byte but6laststate = 0;
byte but7laststate = 0;
byte but8laststate = 0;
byte but9laststate = 0;
byte but10laststate = 0;
byte but11laststate = 0;

//remote
int xpotval = 0;
int ypotval = 0;
int zpotval = 0;
int apotval = 0;
//local
int xrotpotval = 0;
int yrotpotval = 0;
int zrotpotval = 0;

//define a counter to count bytes in response
byte bcount;
 
//define an array for returned data
int getResponse[7];


//if you don't know what "void setup()" does - you probably shouldn't be reading this
void setup() 
{
joystick.begin();

//set pin modes for the local button pins
pinMode(but4pin, INPUT_PULLUP);
pinMode(but5pin, INPUT_PULLUP);
pinMode(but6pin, INPUT_PULLUP);
pinMode(but7pin, INPUT_PULLUP);
pinMode(but8pin, INPUT_PULLUP);
pinMode(but9pin, INPUT_PULLUP);
pinMode(but10pin, INPUT_PULLUP);
pinMode(but11pin, INPUT_PULLUP);

analogReference(INTERNAL); //set analog voltage reference, used this because was having less than 5V on the output, possibly due to powering the Module B nano
Wire.begin(); //initialize the I2C comms
Serial.begin(115200); //initialize serial comms for debugging
}


byte readI2C(int address) 
{
  //define a variable to hold byte of data
  byte bval ;
  //counter related stuff
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
while (readI2C(SLAVE_ADDR) < 255) //because 255 signals that the next byte of information is starting
{

}
  for (bcount = 0; bcount < 7; bcount++) 
  {
    getResponse[bcount] = readI2C(SLAVE_ADDR);
  }

  //record response values from Module B pots to variables to be used later
  xpotval = getResponse[0];
  ypotval = getResponse[1];
  zpotval = getResponse[2];
  apotval = getResponse[3];
  //read buttons from Module B
  but1state = getResponse[4];
  but2state = getResponse[5];
  but3state = getResponse[6];
    
  //read pots from Module A
  xrotpotval = analogRead(xrotpot);
  yrotpotval = analogRead(yrotpot);
  zrotpotval = analogRead(zrotpot);
  //read buttons from Module A
  but4state = digitalRead(but4pin);
  but5state = digitalRead(but5pin);
  but6state = digitalRead(but6pin);
  but7state = digitalRead(but7pin);
  but8state = digitalRead(but8pin);
  but9state = digitalRead(but9pin);
  but10state = digitalRead(but10pin);
  but11state = digitalRead(but11pin);
  
  
  //reversing button state logic
  if (but1state == HIGH)
  {but1state = 0;}
    else{but1state = 1;}

  if (but2state == HIGH)
  {but2state = 0;}
    else{but2state = 1;}
  
  if (but3state == HIGH)
  {but3state = 0;}
    else{but3state = 1;}

  if (but4state == HIGH)
  {but4state = 0;}
    else{but4state = 1;}

  if (but5state == HIGH)
  {but5state = 0;}
    else{but5state = 1;}
  
  if (but6state == HIGH)
  {but6state = 0;}
    else{but6state = 1;}

  if (but7state == HIGH)
  {but7state = 0;}
    else{but7state = 1;}

  if (but8state == HIGH)
  {but8state = 0;}
    else{but8state = 1;}
  
  if (but9state == HIGH)
  {but9state = 0;}
    else{but9state = 1;}
  
  if (but10state == HIGH)
  {but10state = 0;}
    else{but10state = 1;}

  if (but11state == HIGH)
  {but11state = 0;}
    else{but11state = 1;}
  
  //tell the joystick library where to get the values for the axes
  joystick.setXAxis(xpotval);
  joystick.setYAxis(ypotval);
  joystick.setZAxis(zpotval);
  joystick.setRxAxis(xrotpotval);
  joystick.setRyAxis(yrotpotval);
  joystick.setRzAxis(zrotpotval);
  joystick.setThrottle(apotval);

  //set the min-max values for the REMOTE axes
  joystick.setXAxisRange(0, 254);
  joystick.setYAxisRange(254, 0);
  joystick.setZAxisRange(0, 254);
  joystick.setThrottleRange(0, 254);

  //tell the joystick library state of buttons
	if (but1state != but1laststate)
	{
	joystick.setButton(0, but1state);
	but1laststate = but1state;
	}
  if (but2state != but2laststate)
	{
	joystick.setButton(1, but2state);
	but2laststate = but2state;
	}
  if (but3state != but3laststate)
	{
	joystick.setButton(2, but3state);
	but3laststate = but3state;
	}
  if (but4state != but4laststate)
	{
	joystick.setButton(3, but4state);
	but4laststate = but4state;
	}
  if (but5state != but5laststate)
	{
	joystick.setButton(4, but5state);
	but5laststate = but5state;
	}
  if (but6state != but6laststate)
	{
	joystick.setButton(5, but6state);
	but6laststate = but6state;
	}
  if (but7state != but7laststate)
	{
	joystick.setButton(6, but7state);
	but7laststate = but7state;
	}
  if (but8state != but8laststate)
	{
	joystick.setButton(7, but8state);
	but8laststate = but8state;
	}
  if (but9state != but9laststate)
	{
	joystick.setButton(8, but9state);
	but9laststate = but9state;
	}
  if (but10state != but10laststate)
	{
	joystick.setButton(9, but10state);
	but10laststate = but10state;
	}
  if (but11state != but11laststate)
	{
	joystick.setButton(10, but11state);
	but11laststate = but11state;
	}
  
	//delay(50);

//debugging - print remote pot values to screen...
  Serial.print("xpv:"); Serial.print(xpotval); 
  Serial.print(" ypv:"); Serial.print(ypotval); 
  Serial.print(" zpv:"); Serial.print(zpotval); 
  Serial.print(" apv:"); Serial.print(apotval); 
//debugging - print "local" pot values to screen...
  Serial.print(" xrpv:"); Serial.print(xrotpotval);
  Serial.print(" yrpv:"); Serial.print(yrotpotval);
  Serial.print(" zrpv:"); Serial.print(zrotpotval);
//debugging - print REMOTE button states to screen...
  Serial.print(" b1s:"); Serial.print(but1state);
  Serial.print(" b2s:"); Serial.print(but2state); 
  Serial.print(" b3s:"); Serial.print(but3state);
//debugging - print LOCAL button states to screen...
  Serial.print(" b4s:"); Serial.print(but4state);
  Serial.print(" b5s:"); Serial.print(but5state); 
  Serial.print(" b6s:"); Serial.print(but6state);
  Serial.print(" b7s:"); Serial.print(but7state);
  Serial.print(" b8s:"); Serial.print(but8state); 
  Serial.print(" b9s:"); Serial.print(but9state);  
  Serial.print(" b10s:"); Serial.print(but10state);
  Serial.print(" b11s:"); Serial.println(but11state); 
}
