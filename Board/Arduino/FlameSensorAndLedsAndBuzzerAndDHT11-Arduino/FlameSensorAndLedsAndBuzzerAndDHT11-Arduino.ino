unsigned long PrevTime_RedLed = 0; // Previous time Red Led 
unsigned long Delay_RedLed = 500; // Delay Red Led 

byte RedLedState = LOW; // Red Led State

unsigned long PrevTime_DHT = 0; // Previous time for DHT sensor
unsigned long Delay_DHT = 4000; // Delay for DHT sensor

#include <dht.h>
dht DHT;
int sensor_pin = 7;

void setup() {
  Serial.begin(9600);
  pinMode(13, OUTPUT); // Green Led
  pinMode(12, OUTPUT); // Red Led
  pinMode(11, OUTPUT); // Buzzer
  pinMode(10, INPUT); // Flame Sensor

}

void loop() {  
  unsigned long currentTime = millis(); // currentTime Red Led 

//DHT11
if (currentTime - PrevTime_DHT > Delay_DHT) {
    PrevTime_DHT = currentTime;
    
    int chk = DHT.read11(sensor_pin);
    Serial.print("Temperature = ");
    Serial.print(DHT.temperature);
    Serial.println();

    Serial.print("Humidity = ");
    Serial.print(DHT.humidity);
    Serial.print(" %");
    Serial.println();
    Serial.println();
  }

bool FlameSensor = digitalRead(10); // Flame Sensor State
Serial.println(FlameSensor); // Serial Print Flame Sensor State

if(FlameSensor == 1) // Flame Sensor Not Work
{
digitalWrite(13, HIGH); // Green Led HIGH
}
else{
  digitalWrite(13, LOW); // Green Led LOW
}


if(FlameSensor == 0){ // Flame Sensor Work

// Parllel Red Led 
if (currentTime - PrevTime_RedLed > Delay_RedLed) {
   PrevTime_RedLed += Delay_RedLed;
   if(RedLedState == HIGH)
   {
    RedLedState = LOW; // Led Red LOW
    noTone(11); // Buzzer Stop
   }

   else
   {
   RedLedState = HIGH; // Led Red HIGH
    tone(11,261); // Buzzer Start
   }
 
}

digitalWrite(12,RedLedState); // Write Red Led State

}
}





        



        

