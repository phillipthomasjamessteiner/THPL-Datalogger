#include <SFE_BMP180.h>
#include <Wire.h>

SFE_BMP180 BMP;
double T,P,p0,a;


void setup() {

  Serial.begin(9600);

  //=================================================================
  // BMP180 Init Code Block
  if (pressure.begin()) // Initialize BMP180
    Serial.println("BMP180 init success");
  else {
    Serial.println("BMP180 init fail\n\n");
    while(1);
  }
  
}

void loop() {

  //=================================================================
  // BMP180 Get Temp and Altitude Code Block
  status = pressure.startTemperature();
  if (status != 0) { 
    delay(status);
    status = pressure.getTemperature(T);
    if (status != 0) {
      status = pressure.startPressure(3);
      if (status != 0) {
        delay(status);
        status = pressure.getPressure(P,T);
        if (status != 0) {
          p0 = pressure.sealevel(P,ALTITUDE); // we're at 1655 meters (Boulder, CO)
          a = pressure.altitude(P,p0);
        }
        else Serial.println("error retrieving pressure measurement\n");
      }
      else Serial.println("error starting pressure measurement\n");
    }
    else Serial.println("error retrieving temperature measurement\n");
  }
  else Serial.println("error starting temperature measurement\n");

}
