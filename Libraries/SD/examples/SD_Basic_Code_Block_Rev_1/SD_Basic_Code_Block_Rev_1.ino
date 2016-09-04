#include <SPI.h>
#include <SD.h>

const int chipSelect = 10;

void setup() {
  
  Serial.begin(9600);

  Serial.print("Initializing SD card...");

  // see if the card is present and can be initialized:
  if (!SD.begin(chipSelect)) {
    Serial.println("Card failed, or not present");
    // don't do anything more:
    return;
  }
  Serial.println("card initialized.");
  
}

void loop() {
  
  String dataString = "";
  dataString += analogRead(A0);
  
  File dataFile = SD.open("datalog.txt", FILE_WRITE);
  if (dataFile) {
    dataFile.println(dataString);
    dataFile.close();
    Serial.println(dataString);
  }
  else Serial.println("error");

  delay(1000);
}


