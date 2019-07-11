//Summer School Workshop, 12 July 2019
//C-3pH: Arduino Code
//Adapted by C. W. Chung (9 July 2019)

#include <Wire.h>
#include "Adafruit_TCS34725.h"

/* Example code for the Adafruit TCS34725 breakout library */

/* Connect SCL    to analog 5
   Connect SDA    to analog 4
   Connect VDD    to 3.3V DC
   Connect GROUND to common ground */

/* Initialise with default values (int time = 2.4ms, gain = 1x) */
// Adafruit_TCS34725 tcs = Adafruit_TCS34725();

/* Initialise with specific int time and gain values */
Adafruit_TCS34725 tcs = Adafruit_TCS34725(TCS34725_INTEGRATIONTIME_700MS, TCS34725_GAIN_1X); 

void setup(void) {
  Serial.begin(9600);
 }

//Displays data only 
void loop(void) {
//char userInput = ' ';   
//if (Serial.available()) {  
//  userInput = Serial.read();  

  uint16_t r, g, b, c, colorTemp, lux;
  float ratio, rf, gf, bf;

  tcs.getRawData(&r, &g, &b, &c);
  colorTemp = tcs.calculateColorTemperature_dn40(r, g, b, c);
  lux = tcs.calculateLux(r, g, b);
  rf=r;
  gf=g;
  bf=b;
  ratio = log(rf/(rf+bf+gf));

Serial.print("R: "); 
Serial.print(r, DEC); Serial.print(",");
Serial.print("G: "); 
Serial.print(g, DEC); Serial.print(",");
Serial.print("B: "); 
Serial.print(b, DEC); Serial.print(",");
//Serial.print("Ratio 1 = (R+G+B)/R: "); 
//Serial.print(ratio, DEC); Serial.print(",");
Serial.println(" ");
//}
}  
