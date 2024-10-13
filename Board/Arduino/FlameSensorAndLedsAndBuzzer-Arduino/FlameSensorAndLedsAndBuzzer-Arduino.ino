unsigned long PrevTime_RedLed = 0; // Previous time Red Led 
unsigned long Delay_RedLed = 500; // Delay Red Led 

byte RedLedState = LOW; // Red Led State

void setup() {
  pinMode(13, OUTPUT); // Green Led
  pinMode(12, OUTPUT); // Red Led
  pinMode(11, OUTPUT); // Buzzer
  pinMode(10, INPUT); // Flame Sensor

}

void loop() {  
unsigned long currentTime = millis(); // currentTime Red Led 

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






        



        

