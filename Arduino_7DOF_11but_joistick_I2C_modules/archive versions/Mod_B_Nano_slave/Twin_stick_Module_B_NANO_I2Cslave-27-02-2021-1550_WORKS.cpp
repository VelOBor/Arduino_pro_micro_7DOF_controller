/*
This is the code for Module B NANO (slave) of the twin stick controller by Oleg "Salty" Velichko, AKA Helgar Fenrir.
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

//defining pot input pins for the joystick
byte pot_1 = A3; //X-axis
byte pot_2 = A2; //Y-axis
byte pot_3 = A1; //Z-axis
byte pot_4 = A0; //extra pot

//defining button input pins
byte but_1 = 4; //leftmost button
byte but_2 = 3; //center button
byte but_3 = 2; //right button


//setting variables for pot values
int pot_1_val = 0;
int pot_2_val = 0;
int pot_3_val = 0;
int pot_4_val = 0;


//setting up variables for button states
byte but_1_state = 0;
byte but_2_state = 0;
byte but_3_state = 0;


//define a counter for the number of bytes in the response on I2C
byte bcount = 0;

//Define return data array size, one element per input (3 pots + 4 buttons = total 7)
int response[7];

//WHAT?!?!?
void requestEvent() 
{
  //define a byte to hold data
  byte bval;
  
  //cycle through inputs
  //first response is always 255 to mark beginning
  switch (bcount) 
  {
    case 0:
      bval = 255;
      break;
    case 1:
      bval = response[0];
      break;
    case 2:
      bval = response[1];
      break;
    case 3:
      bval = response[2];
      break;
    case 4:
      bval = response[3];
      break;
    case 5:
      bval = response[4];
      break;
     case 6:
      bval = response[5];
      break;
    case 7:
      bval = response[6];
      break;  
  }
 
  //send response back to Master
  Wire.write(bval);
  
  // Increment byte counter
  bcount = bcount + 1;
  if (bcount > 7) bcount = 0;
 
}

//main function to assign values from the controller inputs to the array
void getInput()
{
//read pot input values
  pot_1_val = analogRead(pot_1);
  pot_2_val = analogRead(pot_2);
  pot_3_val = analogRead(pot_3);
  pot_4_val = analogRead(pot_4);

  //remapping the pot values down to UNDER 1 byte size for easier I2C communication (value of 255 will be used to denote next byte)
  pot_1_val = map(pot_1_val, 0, 1023, 0, 254);
  pot_2_val = map(pot_2_val, 0, 1023, 0, 254);
  pot_3_val = map(pot_3_val, 0, 1023, 0, 254);
  pot_4_val = map(pot_4_val, 0, 1023, 0, 254);

  //read button states
  but_1_state = digitalRead(but_1);
  but_2_state = digitalRead(but_2);
  but_3_state = digitalRead(but_3);

  //remap button states to logical values of 1 for "pressed" and 0 "not pressed" instead of
  //the "reverse logic" of "pressed is low" and "not pressed is high"...
  if (but_1_state == LOW)
  {but_1_state = 1;}
    else{but_1_state = 0;}

  if (but_2_state == LOW)
  {but_2_state = 1;}
    else{but_2_state = 0;}
  
  if (but_3_state == LOW)
  {but_3_state =1;}
    else{but_3_state = 0;}
  
  
  //write the inputs to the response array
  response[0] = pot_1_val;
  //delay(20);
  response[1] = pot_2_val;
  //delay(20);
  response[2] = pot_3_val;
  //delay(20);
  response[3] = pot_4_val;
  //delay(20);
  response[4] = but_1_state;
  //delay(20);
  response[5] = but_2_state;
  //delay(20);
  response[6] = but_3_state;
  //delay(20); 
}

//if you don't know what "void setup()" does - you probably shouldn't be reading this
void setup() 
{

  //initialize the pins and start serial communications
  pinMode(but_1, INPUT_PULLUP);
  pinMode(but_2, INPUT_PULLUP);
  pinMode(but_3, INPUT_PULLUP);
  
  pinMode(pot_1, INPUT);
  pinMode(pot_2, INPUT);
  pinMode(pot_3, INPUT);
  pinMode(pot_4_val, INPUT);
  
  Wire.begin(SLAVE_ADDR);
  Wire.onRequest(requestEvent);
  Serial.begin(115200);
  
}


//you should know what "void loop()" does
void loop() 
{
  getInput();
  
  //---------============main part of code starts here============---------//
  //everything above these comments is just for reading the values, everything following this 
  //is for writing these values to I2C for Module A to read.
 
  //serial monitor debugging
Serial.print("b_1_s:"); Serial.print(but_1_state); Serial.print(" b_2_s:"); Serial.print(but_2_state); Serial.print(" b_3_s:");
Serial.print(but_3_state); Serial.print(" p_1_v:"); Serial.print(pot_1_val); Serial.print(" p_2_v:"); Serial.print(pot_2_val); 
Serial.print(" p_3_v:"); Serial.print(pot_3_val); Serial.print(" p_4_v:"); Serial.print(pot_4_val);
Serial.print(" res[0]p1v:"); Serial.print(response[0]); Serial.print(" res[1]p2v:"); Serial.print(response[1]);
Serial.print(" res[2]p3v:"); Serial.print(response[2]); Serial.print(" res[3])p1v:"); Serial.print(response[3]);
Serial.print(" res[4]b1s:"); Serial.print(response[4]); Serial.print(" res[5]b2s:"); Serial.print(response[5]);
Serial.print(" res[6]b3s:"); Serial.println(response[6]);
  
}
