unsigned long PrevTime_RedLed = 0; // Previous time Red Led 
unsigned long Delay_RedLed = 500; // Delay Red Led 

byte RedLedState = LOW; // Red Led State

void setup() {
  pinMode(13, OUTPUT); // Green Led
  pinMode(12, OUTPUT); // Red Led
  pinMode(11, OUTPUT); // Buzzer 
}

void loop() {  
unsigned long currentTime = millis(); // currentTime Red Led 

digitalWrite(13, HIGH); // Green Led HIGH

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

// Blink Red Led
  // digitalWrite(12, HIGH);  
  // delay(500);                      
  // digitalWrite(12, LOW);   
  // delay(500);   

//Buzzer
//  tone(11,261);
//  delay(3000);
//   tone(11,440);
//   delay(3000);
  // Add sounds




        



        
