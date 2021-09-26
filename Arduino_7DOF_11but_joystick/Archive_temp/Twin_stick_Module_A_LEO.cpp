/*
This is the code for Module A LEONARDO of the twin stick controller by Oleg "Salty" Velichko, AKA Helgar Fenrir.
The controller features a total two 3-axis sticks, a rotary pot and 11 buttons. The left (slave) Module B stick has a stick,
3 buttons and a rotary potentiometer. The right Module A (master), has a stick with a button on top and 7 additional buttons.
The two modules communicate via I2C (the code to which is an inherent part of this project and is located in a separate file).
The reason behind having nano's for I2C is the fact that I need more leads than a single RJ45 can handle for Module B (slave). 
The main controller is Arduino LEONARDO (later to be replaced with a micro).
If you have any questions or comments - find me on discord under the name "Salty NUggeTZ#6753"
N.B. - I like using VSCode to write my arduino sketches, so the look of this sketch in your IDE may differ slightly
*/


#include <Arduino.h> //make sure VSCode understands that this is an arduino sketch
#include <joystick.h>


//if you don't know what "void setup()" does - you probably shouldn't be reading this
void setup() 
{
Serial.begin(115200); //just in case we need this for debugging and such
  
}


//you should know what "void loop()" does
void loop() 
{
 
}