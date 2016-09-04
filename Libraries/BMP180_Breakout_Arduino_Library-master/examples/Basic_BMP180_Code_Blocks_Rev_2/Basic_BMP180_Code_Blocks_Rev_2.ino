#include <SFE_BMP180.h>
#include <Wire.h>

SFE_BMP180 BMP;
double T,P,a;

#define p0 1013.25 // Seal leven pressure in mb

void setup() {

  Serial.begin(9600);

  //=================================================================
  // BMP180 Init Code Block
  if (BMP.begin()) // Initialize BMP180
    Serial.println("BMP180 init success");
  else {
    Serial.println("BMP180 init fail\n\n");
    while(1);
  }
}

void loop() {
  //=================================================================
  // BMP180 Get Temp and Altitude Code Block
  char status;
  status = BMP.startTemperature();
  if (status != 0) { 
    delay(status);
    status = BMP.getTemperature(T);
    if (status != 0) {
      status = BMP.startPressure(3);
      if (status != 0) {
        delay(status);
        status = BMP.getPressure(P,T);
        if (status != 0) {
          a = BMP.altitude(P,p0);
        }
        else Serial.println("error retrieving pressure measurement\n");
      }
      else Serial.println("error starting pressure measurement\n");
    }
    else Serial.println("error retrieving temperature measurement\n");
  }
  else Serial.println("error starting temperature measurement\n");
  Serial.println(P);
  Serial.println(T);
  Serial.println(a);
  Serial.println("-----");
  delay(1000);
}
