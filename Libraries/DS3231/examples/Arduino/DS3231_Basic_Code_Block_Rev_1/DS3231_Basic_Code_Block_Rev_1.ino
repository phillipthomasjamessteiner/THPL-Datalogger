#include <DS3231.h>

DS3231 rtc(SDA, SCL);
Time t;

void setup() {
  
  Serial.begin(9600);
  
  rtc.begin();
  // The following lines can be uncommented to set the date and time
  //rtc.setDOW(WEDNESDAY);     // Set Day-of-Week to SUNDAY
  //rtc.setTime(12, 0, 0);     // Set the time to 12:00:00 (24hr format)
  //rtc.setDate(1, 1, 2014);   // Set the date to January 1st, 2014
}

void loop() {
  // put your main code here, to run repeatedly:
  t = rtc.getTime();
  String Date = "";
  Date += t.mon;    Date += "/";
  Date += t.date;   Date += "/";
  Date += t.year;

  String T = "";
  T += t.hour;  T += ":";
  T += t.min;   T += ":";
  T += t.sec;

  Serial.println(Date + " " + T);
  Serial.println("-----");
  
}
