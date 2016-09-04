#include "DHT.h"

#define DHTPIN 6
#define DHTTYPE DHT11

DHT dht(DHTPIN, DHTTYPE);

int DHTHumid, DHTTemp;

void setup() {
  Serial.begin(9600);

  //=================================================================
  // DHT11 Init Code Block
  dht.begin();
  Serial.println("DHT Init");
  
}

void loop() {

  //=================================================================
  // DHT11 Get Temp and Humidity Code Block
  DHTHumid = dht.readHumidity();
  DHTTemp = dht.readTemperature(); // In Celsius

  Serial.println(DHTHumid); // Relative Humidity (RH) %
  Serial.println(DHTTemp); // Celcius
  Serial.println("-----");

  delay(2500);
}
