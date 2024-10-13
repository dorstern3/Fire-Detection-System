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

unsigned long PrevTime_RedLed = 0; // Previous time Red Led 
unsigned long Delay_RedLed = 500; // Delay Red Led 
byte RedLedState = LOW; // Red Led State
unsigned long PrevTime_DHT = 0; // Previous time for DHT sensor
unsigned long Delay_DHT = 4000; // Delay for DHT sensor

//FAN
const int fanPin = D8;  

// Set the LCD address to 0x27 or 0x3F for a 16 chars and 2 line display
LiquidCrystal_I2C lcd(0x3F, 16, 2);

void setup() {
  Serial.begin(9600);

  // LCD
  lcd.begin();
  lcd.backlight();

  pinMode(D5, OUTPUT); // Green Led
  pinMode(D6, OUTPUT); // Red Led
  pinMode(D7, OUTPUT); // Buzzer
  pinMode(D4, INPUT); // Flame Sensor
  dht.begin(); // DHT11
  pinMode(fanPin, OUTPUT); //FAN
}

void loop() {  
  unsigned long currentTime = millis(); // currentTime Red Led 

// DHT11
if (currentTime - PrevTime_DHT > Delay_DHT) {
    PrevTime_DHT = currentTime;
    float temp = dht.readTemperature(); 
    float hum = dht.readHumidity();     
    //Serial print
    Serial.print("Temperature = ");
    Serial.print(temp);
    Serial.println();

    Serial.print("Humidity = ");
    Serial.print(hum);
    Serial.print(" %");
    Serial.println();
    Serial.println();

    //LCD
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Temp:");
    lcd.print(temp);
    lcd.print("C");

    lcd.setCursor(0, 1);
    lcd.print("Humidity:");
    lcd.print(hum);
    lcd.print("%");
  }

bool FlameSensor = digitalRead(D4); // Flame Sensor State
Serial.println(FlameSensor); // Serial Print Flame Sensor State

if(FlameSensor == 1) // Flame Sensor Not Work
{
digitalWrite(D5, HIGH); // Green Led HIGH
analogWrite(fanPin, 0);  // FAN OFF
}
else{
  digitalWrite(D5, LOW); // Green Led LOW
}

if(FlameSensor == 0){ // Flame Sensor Work
// Parllel 
if (currentTime - PrevTime_RedLed > Delay_RedLed) {
   PrevTime_RedLed += Delay_RedLed;
   if(RedLedState == HIGH)
   {
    RedLedState = LOW; // Led Red LOW
    noTone(D7); // Buzzer Stop
   }

   else
   {
   RedLedState = HIGH; // Led Red HIGH
    tone(D7,261); // Buzzer Start
   }
 
}
digitalWrite(D6,RedLedState); // Write Red Led State
analogWrite(fanPin, 255);  // FAN ON
}
}





        



        

