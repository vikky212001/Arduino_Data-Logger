#include <DHT.h>
#include <Wire.h>
#include <RTClib.h>
#include <LiquidCrystal.h>
#include <SdFat.h>

#define DHTPIN A1
#define DHTPIN1 A2
#define DHTTYPE DHT11
#define DHTTYPE1 DHT11

DHT dht(DHTPIN, DHTTYPE);
DHT dht1(DHTPIN1, DHTTYPE1);
RTC_DS3231 rtc;
LiquidCrystal lcd(8, 9, 4, 5, 6, 7);

const int chipSelect = 10;
SdFat sd;
File dataFile;
const int maxSubstrings = 10;
String substrings[maxSubstrings];
String remainingStrings[38];
String deviceName = "Logger";
const String password = "1234";
String T1SV;
String H1SV;
String T1UL;
String T1LL;
String H1UL;
String H1LL;
String T1C;
String H1C;
String T2SV;
String H2SV;
String T2UL;
String T2LL;
String H2UL;
String H2LL;
String T2C;
String H2C;
String T3SV;
String H3SV;
String T3UL;
String T3LL;
String H3UL;
String H3LL;
String T3C;
String H3C;
String T4SV;
String H4SV;
String T4UL;
String T4LL;
String H4UL;
String H4LL;
String T4C;
String H4C;

void setup() {
  Serial.begin(9600);
  dht.begin();
  dht1.begin();
  lcd.begin(16, 2);
  if (!rtc.begin()) {
    Serial.println("Couldn't find RTC");
    while (1)
      return;
  }
  if (!sd.begin(chipSelect, SPI_HALF_SPEED)) {
    Serial.println("SD initialization failed!");
    while (1)
      return;
  }
}

void loop() {
  delay(5000);
  float temperature = dht.readTemperature();
  float humidity = dht.readHumidity();
  float temperature1 = dht1.readTemperature();
  float humidity1 = dht1.readHumidity();
  DateTime now = rtc.now();
  int year = now.year();
  int month = now.month();
  int day = now.day();
  int hour = now.hour();
  int minute = now.minute();
  int second = now.second();

  if (Serial.available() > 0) {
    String inputLine = Serial.readStringUntil('\n');
    if (inputLine.length() > 0) {
      splitString(inputLine, '-');
      String name = substrings[0];

      if (name.equals(deviceName)) {
        String secondWord = substrings[1];

        if (secondWord.equals("ChangeName")) {
          String maindataCN = substrings[2];
          splitRemainingString(maindataCN, ' ');
          String pass = remainingStrings[0];
          if (pass.equals(password)) {
            deviceName = remainingStrings[1];
          } else {
            Serial.println("Error_PassIncorrect");
          }
        } else if (secondWord.equals("Config")) {
          String maindataCO = substrings[2];
          splitRemainingString(maindataCO, ' ');
          String logType = remainingStrings[0];
          String NoOfSensor = 
          if (logType.equals("Temperature")) {
            // Code for Temperature         
          } else if (logType.equals("Humidity")) {
            // Code for Humidity
          } else if (logType.equals("Both")) {
            // Code for Both
          }
        }
      }
    }
  }

  if (isnan(temperature) || isnan(humidity)) {
    Serial.println("Failed to read from First sensor!");
    return;
  }
  if (isnan(temperature1) || isnan(humidity1)) {
    Serial.println("Failed to read from Second sensor!");
    return;
  }
  Serial.print(deviceName);
  Serial.print("_VALUES_");
  Serial.print("Temperature: ");
  Serial.print(temperature, 2);
  Serial.print(" Humidity: ");
  Serial.print(humidity, 2);
  Serial.print(" Temperature1: ");
  Serial.print(temperature1, 2);
  Serial.print(" Humidity1: ");
  Serial.print(humidity1, 2);
  Serial.print(" Date/Time: ");
  Serial.print(year, DEC);
  Serial.print('/');
  Serial.print(month, DEC);
  Serial.print('/');
  Serial.print(day, DEC);
  Serial.print(" ");
  Serial.print(hour, DEC);
  Serial.print(':');
  Serial.print(minute, DEC);
  Serial.print(':');
  Serial.print(second, DEC);
  Serial.println();

  dataFile = sd.open("data.csv", FILE_WRITE);

  if (dataFile) {
    dataFile.print(year, DEC);
    dataFile.print('/');
    dataFile.print(month, DEC);
    dataFile.print('/');
    dataFile.print(day, DEC);
    dataFile.print(" ");
    dataFile.print(hour, DEC);
    dataFile.print(':');
    dataFile.print(minute, DEC);
    dataFile.print(':');
    dataFile.print(second, DEC);
    dataFile.print(",");
    dataFile.print(temperature, 2);
    dataFile.print(",");
    dataFile.print(humidity, 2);
    dataFile.print(",");
    dataFile.print(temperature1, 2);
    dataFile.print(",");
    dataFile.println(humidity1, 2);
    dataFile.close();
  } else {
    Serial.println("Error_OpenFile");
  }

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("T:");
  lcd.print(temperature);
  lcd.setCursor(0, 1);
  lcd.print("H:");
  lcd.print(humidity);
  lcd.setCursor(5, 0);
  lcd.print("T1:");
  lcd.print(temperature1);
  lcd.setCursor(5, 1);
  lcd.print("H1:");
  lcd.print(humidity1);
  lcd.setCursor(11, 0);
  lcd.print(hour, DEC);
  lcd.print(':');
  lcd.print(minute, DEC);
  lcd.setCursor(11, 1);
  lcd.print(day, DEC);
  lcd.print('/');
  lcd.print(month, DEC);
}

void splitString(String input, char delimiter) {
  int delimiterIndex = input.indexOf(delimiter);
  int substringIndex = 0;

  while (delimiterIndex != -1 && substringIndex < maxSubstrings) {
    substrings[substringIndex] = input.substring(0, delimiterIndex);
    input = input.substring(delimiterIndex + 1);
    delimiterIndex = input.indexOf(delimiter);
    substringIndex++;
  }
  substrings[substringIndex] = input;
}

String splitRemainingString(String input, char delimiter, int index) {
  int delimiterIndex = input.indexOf(delimiter);
  int remainingStringIndex = 0;
  while (delimiterIndex != -1 && remainingStringIndex < 38) {
    remainingStrings[remainingStringIndex] = input.substring(0, delimiterIndex);
    input = input.substring(delimiterIndex + 1);
    delimiterIndex = input.indexOf(delimiter);
    remainingStringIndex++;
  }
  remainingStrings[remainingStringIndex] = input;
}
