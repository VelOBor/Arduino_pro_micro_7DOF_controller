
#include <Arduino.h> //make sure VSCode understands that this is an arduino sketch
#include <Wire.h>    //include the arduino I2C library

//defining debug LED pins
byte pot_1_led = 9;  // brightness regulated LED for pot 1 (X-axis in future)
byte pot_2_led = 10; // ------------------------ for pot 2 (Y-axis in future)
byte pot_3_led = 11; // ------------------------ for pot 3 (Z-axis in future)

byte but_1_led = 3;  // HiLo LED for button 1
byte but_2_led = 5;  // ------------------- 2
byte but_3_led = 7;  // ------------------- 3
byte but_4_led = 12; // ------------------- 4


//defining pot input pins
byte pot_1 = A2;
byte pot_2 = A1;
byte pot_3 = A0;

//defining button input pins
byte but_1 = 2;
byte but_2 = 4;
byte but_3 = 6;
byte but_4 = 8;

//setting variables for pot values
int pot_1_val = 0;
int pot_2_val = 0;
int pot_3_val = 0;

//setting variables for pot LEDs for debugging output
byte pot_1_led_val = 0;
byte pot_2_led_val = 0;
byte pot_3_led_val = 0;

//setting up variables for button states
byte but_1_state = 0;
byte but_2_state = 0;
byte but_3_state = 0;
byte but_4_state = 0;

// the setup function runs once when you press reset or power the board
void setup() {
  //initialize the pins and start serial communications
  
  pinMode(pot_1_led, OUTPUT);
  pinMode(pot_2_led, OUTPUT);
  pinMode(pot_3_led, OUTPUT);

  pinMode(but_1_led, OUTPUT);
  pinMode(but_2_led, OUTPUT);
  pinMode(but_3_led, OUTPUT);
  pinMode(but_4_led, OUTPUT);

  pinMode(but_1, INPUT_PULLUP);
  pinMode(but_2, INPUT_PULLUP);
  pinMode(but_3, INPUT_PULLUP);
  pinMode(but_4, INPUT_PULLUP);

  pinMode(pot_1, INPUT);
  pinMode(pot_2, INPUT);
  pinMode(pot_3, INPUT);

  Serial.begin(9600);
  
}

// the loop function runs over and over again forever
void loop() 
{
  //read pot input values
  pot_1_val = analogRead(pot_1);
  pot_2_val = analogRead(pot_2);
  pot_3_val = analogRead(pot_3);

  but_1_state = digitalRead(but_1);
  but_2_state = digitalRead(but_2);
  but_3_state = digitalRead(but_3);
  but_4_state = digitalRead(but_4);

  //read button input values
  if (but_1_state == LOW)
  {
    but_1_state = 1;
  }
  else 
  {
    but_1_state = 0;
  }

  if (but_2_state == LOW)
  {
    but_2_state = 1;
  }
  else 
  {
    but_2_state = 0;
  }
  
  if (but_3_state == LOW)
  {
    but_3_state =1;
  }
  else 
  {
    but_3_state = 0;
  }
  
  if (but_4_state == LOW)
  {
    but_4_state = 1;
  }
  else 
  {
  but_4_state = 0;
  } 
  
  //print out values for debugging
  Serial.print("pot 1 val "); Serial.print(pot_1_val); Serial.print("  LED 1 val  "); Serial.print(pot_1_led_val); Serial.print(" "); Serial.print("but 1 st  "); Serial.print(but_1_state);
  Serial.print("pot 2 val "); Serial.print(pot_2_val); Serial.print("  LED 2 val  "); Serial.print(pot_2_led_val); Serial.print(" "); Serial.print("but 2 st  "); Serial.print(but_2_state);
  Serial.print("pot 3 val "); Serial.print(pot_3_val); Serial.print("  LED 3 val  "); Serial.print(pot_3_led_val); Serial.print(" "); Serial.print("but 3 st  "); Serial.print(but_3_state);Serial.print("but 4 st  "); Serial.println(but_4_state);

  //remapping and writing the values to debugging LEDs

  pot_1_val = analogRead(pot_1); //read the value from the pot
  pot_1_led_val = map(pot_1_val, 0, 1024, 0, 255); //remap the incomming 0-1024 pot value to 0-255 output value
  analogWrite(pot_1_led, pot_1_led_val); //light up the LED with appropriate brightness level, set by the pot value

  pot_2_val = analogRead(pot_2);
  pot_2_led_val = map(pot_2_val, 0, 1024, 0, 255);
  analogWrite(pot_2_led, pot_2_led_val);

  pot_3_val = analogRead(pot_3);
  pot_3_led_val = map(pot_3_val, 0, 1024, 0, 255);
  analogWrite(pot_3_led, pot_3_led_val);

  //wrting appropriate values to debugging LEDs
  if (but_1_state == 1)
  {
    digitalWrite(but_1_led, HIGH);
  }
  else
  {
    digitalWrite(but_1_led, LOW);
  }

  if (but_2_state == 1)
  {
    digitalWrite(but_2_led, HIGH);
  }
  else
  {
    digitalWrite(but_2_led, LOW);
  }

  if (but_3_state == 1)
  {
    digitalWrite(but_3_led, HIGH);
  }
  else
  {
    digitalWrite(but_3_led, LOW);
  }

  if (but_4_state == 1)
  {
    digitalWrite(but_4_led, HIGH);
  }
  else
  {
    digitalWrite(but_4_led, LOW);
  }

}
