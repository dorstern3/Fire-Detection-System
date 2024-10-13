// Token
#define BLYNK_TEMPLATE_ID "TMPL6kJTsV83G"
#define BLYNK_TEMPLATE_NAME "DHT11"
#define BLYNK_PRINT Serial

//ESP
#include <ESP8266WiFi.h>           
#include <BlynkSimpleEsp8266.h>     
#include <DHT.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

//DHT11
#define DHTPIN 0 
#define DHTTYPE DHT11 
DHT dht(DHTPIN, DHTTYPE);

// Token
char auth[] = ""; 
// WIFI      
char ssid[] = "";  // wifi username
char pass[] = ""; // wifi password   

BlynkTimer timer;

// LCD 
LiquidCrystal_I2C lcd(0x3F, 16, 2);

// Fan 
const int fanPin = D8;

// Concurrent operation times
unsigned long PrevTime_RedLed = 0;
unsigned long Delay_RedLed = 500;
byte RedLedState = LOW;

//DHT11
void sendSensor() {
  float h = dht.readHumidity();
  float t = dht.readTemperature();

  if (isnan(h) || isnan(t)) {
    Serial.println("Failed to read from DHT sensor!");
    lcd.clear();
    lcd.print("Sensor error");
    return;
  }

  // Serial Monitor
  Serial.print("Temperature: ");
  Serial.print(t);
  Serial.println(" *C");
  
  Serial.print("Humidity: ");
  Serial.print(h);
  Serial.println(" %");

  // Blynk
  Blynk.virtualWrite(V0, t); 
  Blynk.virtualWrite(V1, h);

  // LCD
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Temp:");
  lcd.print(t);
  lcd.print("C");
  
  lcd.setCursor(0, 1);
  lcd.print("Humidity:");
  lcd.print(h);
  lcd.print("%");
}

void setup() {
  Serial.begin(9600);
  
  // DHT11 start
  dht.begin();

  // LCD 
  lcd.begin();
  lcd.backlight();

  // Pin setup
  pinMode(D5, OUTPUT); // Green Led
  pinMode(D6, OUTPUT); // Red Led
  pinMode(D7, OUTPUT); // Buzzer
  pinMode(D4, INPUT);  // Flame Sensor
  pinMode(fanPin, OUTPUT); // Fan
  
  // Connect to WiFi and Blynk
  Blynk.begin(auth, ssid, pass);

  // Timer for sensor data
  timer.setInterval(2000L, sendSensor);
}

void loop() {
  Blynk.run();
  timer.run();

  // Flame sensor 
  unsigned long currentTime = millis();
  bool FlameSensor = digitalRead(D4);

  // No flame detected
  if (FlameSensor == 1) { 
    digitalWrite(D5, HIGH); // Green Led ON
    analogWrite(fanPin, 0);  // Fan OFF
  }

  // Flame detected
   else { 
   digitalWrite(D5, LOW); // Green Led OFF
    if (currentTime - PrevTime_RedLed > Delay_RedLed) {
      PrevTime_RedLed += Delay_RedLed;

      if (RedLedState == HIGH) {
        RedLedState = LOW;   // Red Led OFF
        noTone(D7);          // Stop buzzer
      } 
      else 
      {
        RedLedState = HIGH;  // Red Led ON
        tone(D7, 261);       // Start buzzer
      }
    }
    digitalWrite(D6, RedLedState); // Update Red Led state
    analogWrite(fanPin, 255);      // Fan ON at full speed
  }
}
