#include <Wire.h>
#include "Adafruit_TCS34725.h"
#include "dataset.h"
//#include "funcionesKNN.h"
#include <math.h>

/* Initialise with default values (int time = 2.4ms, gain = 1x) */
// Adafruit_TCS34725 tcs = Adafruit_TCS34725();

 // Initialise with specific int time and gain values 
Adafruit_TCS34725 tcs = Adafruit_TCS34725(TCS34725_INTEGRATIONTIME_700MS, TCS34725_GAIN_1X); //700MS


float distanceEuclidian(int pt1[], int pt2[], int co);

float pH_KNN_value(float dis[], float pH_value[], int num);

int r_init,g_init,b_init,c_init;

void setup(void) {
  Serial.begin(9600);
  delay(1000);
  tcs.getRawData(&r_init, &g_init, &b_init, &c_init);
  Serial.println("Hi, this is C-3NpH"); 
  Serial.println("Please insert strip");
  Serial.println(c_init); 

 }

void loop(void) {
  int r, g, b, c;

  float xc_sum = 0, yc_sum = 0;
  int dataPoint[2];
  float dis[num];
  float pH;
  int i;
  float X,Y,Z,xc,yc;
  float min_1, min_2, min_3;
  bool counter = false;

  tcs.getRawData(&r, &g, &b, &c);

  if((c-c_init)>2000)
  {

    delay(2000);
    for (i=0;i<5;i++)
    {
      tcs.getRawData(&r, &g, &b, &c);
      X = (-0.14282 * r) + (1.54924 * g) + (-0.95641 * b);
      Y = (-0.32466 * r) + (1.57837 * g) + (-0.73191 * b);
      Z = (-0.68202 * r) + (0.77073 * g) + (0.56332 * b);

      xc = (X) / (X + Y + Z);
      yc = (Y) / (X + Y + Z);

      xc_sum = xc + xc_sum;
      yc_sum = yc + yc_sum;

    }
      dataPoint[0] = xc_sum*20;
      dataPoint[1] = yc_sum*20;

      for (i=0; i<num; i++)
      {
        dis[i] =  distanceEuclidian(dataPoint, pH_color[i], 2);
      }

      min_1, min_2, min_3, pH = pH_KNN_value(dis, pH_value, num);

    Serial.print("pH is ");
    Serial.println(pH, DEC);
    counter = true;
  }

  while(counter)
  {
      tcs.getRawData(&r, &g, &b, &c);

    if((c - c_init)<1000)
    {
      // Serial.println("out");
      counter = false;
    }
  }
}


float distanceEuclidian(int pt1[], int pt2[], int co)
{  
  int i;
  int suma = 0;
  for(i=0; i<co; i++){
    suma = pow(pt1[i] - pt2[i], 2) + suma;
  }
  return sqrt(suma);
}

float pH_KNN_value(float dis[], float pH_value[], int num)
{
  int i = 0, minIndex_1 = 0, minIndex_2 = 0, minIndex_3 = 0;
  for(i=1;i<num;i++)
  {
    if(dis[minIndex_1]>dis[i])
    {
      minIndex_1=i;
    }
  }
  for(i=1;i<num;i++)
  {
    if(dis[minIndex_2]>dis[i] && (i != minIndex_1))
    {
      minIndex_2=i;
    }
  }
  for(i=1;i<num;i++)
  {
    if(dis[minIndex_3]>dis[i] && (i != minIndex_1) && (i != minIndex_2))
    {
      minIndex_3=i;
    }
  }
  return minIndex_1, minIndex_2, minIndex_3, (pH_value[minIndex_1] + pH_value[minIndex_2] + pH_value[minIndex_3]) / 3;
}
