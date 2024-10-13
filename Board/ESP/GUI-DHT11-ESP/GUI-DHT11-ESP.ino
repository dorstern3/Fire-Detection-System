// Token
#define BLYNK_TEMPLATE_ID "TMPL6kJTsV83G"
#define BLYNK_TEMPLATE_NAME "DHT11"
#define BLYNK_PRINT Serial

//ESP 8288
#include <ESP8266WiFi.h>           
#include <BlynkSimpleEsp8266.h>     
#include <DHT.h>

//DHT11
#define DHTPIN 0 // D3
#define DHTTYPE DHT11 // DHT11
DHT dht(DHTPIN, DHTTYPE); 

// Token
char auth[] = ""; 
// WIFI      
char ssid[] = "";  // wifi username
char pass[] = ""; // wifi password

BlynkTimer timer; // Blynk timer

//DHT11
void sendSensor() {
  float h = dht.readHumidity();
  float t = dht.readTemperature();

  if (isnan(h) || isnan(t)) {
    Serial.println("Failed to read from DHT sensor!");
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
}

void setup() {
  Serial.begin(9600);

  // DHT11 start
  dht.begin();

  // Connect to WiFi
  Blynk.begin(auth, ssid, pass);
  timer.setInterval(2000L, sendSensor);
}

void loop() {
  Blynk.run();  // start Blynk gui
  timer.run(); // start timer
}
