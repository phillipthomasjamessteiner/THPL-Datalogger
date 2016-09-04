#include "DHT.h"
#include <SFE_BMP180.h>
#include <Wire.h>
#include <DS3231.h>
#include <SPI.h>
#include <SD.h>

#define DHTPIN 6
#define DHTTYPE DHT11
#define p0 1013.25 // Seal leven pressure in mb
#define fill " | "

#define delayBTChecks 30000 // delayBetweenTimeChecks in milliseconds (less than 60,000)
#define minsBetweenLogs 30

DHT dht(DHTPIN, DHTTYPE);
SFE_BMP180 BMP;
DS3231 rtc(SDA, SCL);
Time t;

int DHTHumid;
double T,P,a;
const int chipSelect = 10; // SS pin on ATMega328

int mCount;
int pMCount;
int pLogM;

void setup() {
  Serial.begin(9600);

  //=================================================================
  // DHT11 Init Code Block
  dht.begin();
  Serial.println("DHT Init");

  //=================================================================
  // BMP180 Init Code Block
  if (BMP.begin()) // Initialize BMP180
    Serial.println("BMP180 init success");
  else {
    Serial.println("BMP180 init fail\n\n");
    while(1);
  }

  //=================================================================
  // DS3231 Init Code Block
  rtc.begin();

  t = rtc.getTime();

  pMCount = t.min;
  // The following lines can be uncommented to set the date and time
  //rtc.setDOW(WEDNESDAY);     // Set Day-of-Week to SUNDAY
  //rtc.setTime(12, 0, 0);     // Set the time to 12:00:00 (24hr format)
  //rtc.setDate(1, 1, 2014);   // Set the date to January 1st, 2014

  //=================================================================
  // SD Init Code Block
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
  t = rtc.getTime();
  
  if (t.min != pMCount) {
    mCount ++;
    pMCount = t.min;
  }

  if (((mCount % minsBetweenLogs) == 0) && mCount != pLogM) {
    logData();
    pLogM = mCount;
  }
  delay(delayBTChecks);
}

void logData() {
  //=================================================================
  // DHT11 Get Temp and Humidity Code Block
  DHTHumid = dht.readHumidity();

//  Serial.println(DHTHumid); // Relative Humidity (RH) %

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
      }
    }
  }
//  Serial.println(P);
//  Serial.println(T);
//  Serial.println(a);

  //=================================================================
  // DS3231 Get Time Code Block
  t = rtc.getTime();
  String Date = "";
  Date += t.mon;    Date += "/";
  Date += t.date;   Date += "/";
  Date += t.year;

  String Ti = "";
  Ti += t.hour;  Ti += ":";
  Ti += t.min;   Ti += ":";
  Ti += t.sec;

//  Serial.println(Date + " " + Ti);

  //=================================================================
  // SD Write Data Code Block
  String dataString = "";
  dataString += Date;       dataString += fill;
  dataString += Ti;         dataString += fill;
  dataString += DHTHumid;   dataString += fill;
  dataString += P;          dataString += fill;
  dataString += T;          dataString += fill;
  dataString += a;
  
  File dataFile = SD.open("datalog.txt", FILE_WRITE);
  if (dataFile) {
    dataFile.println(dataString);
    dataFile.close();
    Serial.println(dataString);
  }
  else Serial.println("error");
}

