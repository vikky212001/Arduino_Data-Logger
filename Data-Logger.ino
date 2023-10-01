#include <DHT.h>
#include <LiquidCrystal.h>
#include <Wire.h>
#include <RTClib.h>

// Define the pin where your DHT11 sensors are connected
#define DHTPIN 2
#define DHTPIN1 3

// Define the DHT11 sensor type
#define DHTTYPE DHT11
#define DHTTYPE1 DHT11

DHT dht(DHTPIN, DHTTYPE);   // Initialize DHT library
DHT dht1(DHTPIN1, DHTTYPE1);

RTC_DS3231 rtc;
LiquidCrystal lcd(8, 9, 4, 5, 6, 7);  // Initialize the LCD library

void setup() {
  Serial.begin(9600);  // Initialize serial communication
  dht.begin();         // Initialize the first DHT sensor
  dht1.begin();        // Initialize the second DHT sensor
  lcd.begin(16, 2);    // Initialize the LCD screen with 16 columns and 2 rows

  if (!rtc.begin()) {
    Serial.println("Couldn't find RTC");
    while (1);
  }
}

void loop() {
  DateTime now = rtc.now();
  delay(5000);

  // Read temperature and humidity from the first sensor
  int temperature = dht.readTemperature();
  int humidity = dht.readHumidity();

  // Read temperature and humidity from the second sensor
  int temperature1 = dht1.readTemperature();
  int humidity1 = dht1.readHumidity();

  // Check if any reads failed and exit early (to try again)
  if (isnan(temperature) || isnan(humidity)) {
    Serial.println("Failed to read from First sensor!");
    return;
  }
  if (isnan(temperature1) || isnan(humidity1)) {
    Serial.println("Failed to read from Second sensor!");
    return;
  }

  // Print temperature, humidity, and timestamp to the serial monitor
  Serial.print("Temperature: ");
  Serial.print(temperature);
  Serial.print(" Humidity: ");
  Serial.print(humidity);
  Serial.print(" Date/Time: ");
  Serial.print(now.year(), DEC);
  Serial.print('/');
  Serial.print(now.month(), DEC);
  Serial.print('/');
  Serial.print(now.day(), DEC);
  Serial.print(" ");
  Serial.print(now.hour(), DEC);
  Serial.print(':');
  Serial.print(now.minute(), DEC);
  Serial.print(':');
  Serial.print(now.second(), DEC);

  // Print temperature, humidity, and timestamp from the second sensor
  Serial.print(" Temperature 1: ");
  Serial.print(temperature1);
  Serial.print(" Humidity 1: ");
  Serial.print(humidity1);
  Serial.print(" Date/Time: ");
  Serial.print(now.year(), DEC);
  Serial.print('/');
  Serial.print(now.month(), DEC);
  Serial.print('/');
  Serial.print(now.day(), DEC);
  Serial.print(" ");
  Serial.print(now.hour(), DEC);
  Serial.print(':');
  Serial.print(now.minute(), DEC);
  Serial.print(':');
  Serial.print(now.second(), DEC);
  Serial.println();

  // Display temperature, humidity, and timestamp on the LCD screen
  lcd.clear(); // Clear the LCD screen
  lcd.setCursor(0, 0); // Set the cursor to the first row, first column
  lcd.print("T:");
  lcd.print(temperature);
  lcd.setCursor(0, 1); // Set the cursor to the second row, first column
  lcd.print("H:");
  lcd.print(humidity);
  lcd.setCursor(5, 0); // Set the cursor to the first row, fifth column
  lcd.print("T1:");
  lcd.print(temperature1);
  lcd.setCursor(5, 1); // Set the cursor to the second row, fifth column
  lcd.print("H1:");
  lcd.print(humidity1);
  lcd.setCursor(11, 0); // Set the cursor to the first row, eleventh column
  lcd.print(now.hour(), DEC);
  lcd.print(':');
  lcd.print(now.minute(), DEC);
  lcd.setCursor(11, 1); // Set the cursor to the second row, eleventh column
  lcd.print(now.day(), DEC);
  lcd.print('/');
  lcd.print(now.month(), DEC);
}
