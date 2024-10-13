#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include "DHT.h"

#define DHTPIN 0    // Pin where the DHT11 is connected
#define DHTTYPE DHT11   // Define the type of DHT sensor
DHT dht(DHTPIN, DHTTYPE); // Initialize DHT sensor

// Set the LCD address to 0x27 or 0x3F for a 16 chars and 2 line display
LiquidCrystal_I2C lcd(0x3F, 16, 2);

void setup() {
  Serial.begin(9600);
  
  // Initialize the LCD
  lcd.begin();
  lcd.backlight();
  lcd.print("Initializing...");

  // Initialize the DHT sensor
  dht.begin();
  delay(2000); // Wait a few seconds to ensure sensor initialization
}

void loop() {
  float temperature = dht.readTemperature();
  float humidity = dht.readHumidity();
  
  // Check if any reads failed and exit early (to try again).
  if (isnan(temperature) || isnan(humidity)) {
    Serial.println("Failed to read from DHT sensor!");
    lcd.clear();
    lcd.print("Sensor error");
    return;
  }

  // Print to Serial Monitor
  Serial.print("Temperature: ");
  Serial.print(temperature);
  Serial.println("*C");
  Serial.print("Humidity: ");
  Serial.print(humidity);
  Serial.println("%");

  // Display on LCD
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Temp:");
  lcd.print(temperature);
  lcd.print("C");

  lcd.setCursor(0, 1);
  lcd.print("Humidity:");
  lcd.print(humidity);
  lcd.print("%");

  delay(2000); // Wait 2 seconds before updating again
}