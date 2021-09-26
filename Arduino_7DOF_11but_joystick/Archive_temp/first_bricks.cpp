#include <Arduino.h>

//module b pots

int xpot = A2;
int ypot = A3;
int zpot = A4;
int apot = A5;

//module a pots
int xrpot = A11;
int yrpot = A0;
int zrpot = A1;

/*
//module b buttons
byte b1 = 2;
byte b2 = 3;
byte b3 = 4;

//module a buttons
byte b4 = 11;
byte b5 = 10;
byte b6 = 9;
byte b7 = 8;
byte b8 = 7;
byte b9 = 6;
byte b10 = 5;
byte b11 = 13; //button on stick
*/

//variables to hold pot values
int xpotval = 0;
int ypotval = 0;
int zpotval = 0;
int apotval = 0;
int xrpotval = 0;
int yrpotval = 0;
int zrpotval = 0;

/*
//variables to hold button states
byte b1state = 0;
byte b2state = 0;
byte b3state = 0;
byte b4state = 0;
byte b5state = 0;
byte b6state = 0;
byte b7state = 0;
byte b8state = 0;
byte b9state = 0;
byte b10state = 0;
byte b11state = 0;
*/

//if you don't know what "void setup()" does - you probably shouldn't be reading this
void setup() 
{
Serial.begin(115200); //just in case we need this for debugging and such

pinMode(xpot, INPUT);
pinMode(ypot, INPUT);
pinMode(zpot, INPUT);
pinMode(apot, INPUT);
pinMode(xrpot, INPUT);
pinMode(yrpot, INPUT);
pinMode(zrpot, INPUT);

/*
pinMode(b1, INPUT_PULLUP);
pinMode(b2, INPUT_PULLUP);
pinMode(b3, INPUT_PULLUP);
pinMode(b4, INPUT_PULLUP);
pinMode(b5, INPUT_PULLUP);
pinMode(b6, INPUT_PULLUP);
pinMode(b7, INPUT_PULLUP);
pinMode(b8, INPUT_PULLUP);
pinMode(b9, INPUT_PULLUP);
pinMode(b10, INPUT_PULLUP);
pinMode(b11, INPUT_PULLUP);
*/

}


//you should know what "void loop()" does
void loop() 
{

/*   
b1state = digitalRead(b1);
b2state = digitalRead(b2);
b3state = digitalRead(b3);
b4state = digitalRead(b4);
b5state = digitalRead(b5);
b6state = digitalRead(b6);
b7state = digitalRead(b7);
b8state = digitalRead(b8);
b9state = digitalRead(b9);
b10state = digitalRead(b10);
b11state = digitalRead(b11);

//map button states to logic LOW = 1 (button pressed)
if (b1state == LOW) {b1state = 1;}
    else {b1state = 0;}
if (b2state == LOW) {b2state = 1;}
    else {b2state = 0;}
if (b3state == LOW) {b3state = 1;}
    else {b3state = 0;}
if (b4state == LOW) {b4state = 1;}
    else {b4state = 0;}
if (b5state == LOW) {b5state = 1;}
    else {b5state = 0;}
if (b6state == LOW) {b6state = 1;}
    else {b6state = 0;}
if (b7state == LOW) {b7state = 1;}
    else {b7state = 0;}
if (b8state == LOW) {b8state = 1;}
    else {b8state = 0;}
if (b9state == LOW) {b9state = 1;}
    else {b9state = 0;}
if (b10state == LOW) {b10state = 1;}
    else {b10state = 0;}
if (b11state == LOW) {b11state = 1;}
    else {b11state = 0;}
*/

//read pot values, expect the XYZA pots to read 0-254 and XrYrZr pots to read 0-1024

xpotval = analogRead(xpot);
ypotval = analogRead(ypot);
zpotval = analogRead(zpot);
apotval = analogRead(apot);
xrpotval = analogRead(xrpot);
yrpotval = analogRead(yrpot);
zrpotval = analogRead(zrpot);

//output to serial monitor for debugging

//module a outputs

Serial.print("xpot:"); Serial.print(xpotval); 
Serial.print(" ypot:"); Serial.print(ypotval); 
Serial.print(" zpot:"); Serial.print(zpotval);
Serial.print(" apot:"); Serial.print(apotval);


/*
Serial.print(" b1:"); Serial.print(b1state); 
Serial.print(" b2:"); Serial.print(b2state);
Serial.print(" b3:"); Serial.print(b3state);
*/

//module b outputs
Serial.print(" xrpot:"); Serial.print(xrpotval);
Serial.print(" yrpot:"); Serial.print(yrpotval);
Serial.print(" zrpot:"); Serial.println(zrpotval);

/*
Serial.print(" b4:"); Serial.print(b4state);
Serial.print(" b5:"); Serial.print(b5state);
Serial.print(" b6:"); Serial.print(b6state);
Serial.print(" b7:"); Serial.print(b7state);
Serial.print(" b8:"); Serial.print(b8state);
Serial.print(" b9:"); Serial.print(b9state);
Serial.print(" b10:"); Serial.print(b10state);
Serial.print(" b11:"); Serial.println(b11state);
*/

}