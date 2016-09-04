#include "DHT.h"

#define DHTPIN 2
#define DHTTYPE DHT11

DHT dht(DHTPIN, DHTTYPE);

float DHTHumid, DHTTemp;

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

  if (isnan(h) || isnan(t) || isnan(f)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }
  
}
