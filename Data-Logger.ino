#include <DHT.h>
#include <LiquidCrystal.h>

#define DHTPIN 2       // Define the pin where your DHT11 is connected
#define DHTTYPE DHT11  // DHT11 sensor type

#define DHTPIN1 3      // Define the pin for the first DHT11 sensor
#define DHTTYPE1 DHT11

DHT dht(DHTPIN, DHTTYPE); // Initialize DHT library
DHT dht1(DHTPIN1, DHTTYPE1);

LiquidCrystal lcd(8, 9, 4, 5, 6, 7);  // Initialize the LCD library

void setup() {
  Serial.begin(9600);  // Initialize serial communication
  dht.begin();         // Initialize the DHT sensor
  dht1.begin();
  lcd.begin(16, 2);    // Initialize the LCD screen with 16 columns and 2 rows
}

void loop() {
  // Wait a few seconds between measurements
  delay(2000);

  // Read temperature and humidity from the sensor
  int temperature = dht.readTemperature();
  int humidity = dht.readHumidity();

  int temperature1 = dht1.readTemperature();
  int humidity1 = dht1.readHumidity();

  // Check if any reads failed and exit early (to try again)
  if (isnan(temperature) || isnan(humidity)) {
    Serial.println("Failed to read from First sensors!");
    return;
  }
  if (isnan(temperature1) || isnan(humidity1)) {
    Serial.println("Failed to read from Second sensors!");
    return;
  }

  // Print temperature and humidity to the serial monitor
  Serial.print("Temperature: ");
  Serial.print(temperature);
  Serial.print(" °C | Humidity: ");
  Serial.print(humidity);
  Serial.println("%");

  Serial.print("Temperature 1: ");
  Serial.print(temperature1);
  Serial.print(" °C | Humidity 1: ");
  Serial.print(humidity1);
  Serial.println("%");

  // Display temperature and humidity on the LCD screen
  lcd.clear(); // Clear the LCD screen
  lcd.setCursor(0, 0); // Set the cursor to the first row, first column
  lcd.print("T:");
  lcd.print(temperature);
  //lcd.print(" C");
  lcd.setCursor(0, 1); // Set the cursor to the second row, first column
  lcd.print("H:");
  lcd.print(humidity);
  //lcd.print(" %");
  lcd.setCursor(5, 0); // Set the cursor to the first row, first column
  lcd.print("T1:");
  lcd.print(temperature1);
  //lcd.print(" C");
  lcd.setCursor(5, 1); // Set the cursor to the second row, first column
  lcd.print("H1:");
  lcd.print(humidity1);
}
