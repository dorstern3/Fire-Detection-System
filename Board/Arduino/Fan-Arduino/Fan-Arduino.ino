const int fanPin = 9;  // PWM-enabled pin

void setup() {
  // Set the fan control pin as an output
  pinMode(fanPin, OUTPUT);
}

void loop() {
  // Control fan speed using PWM (values between 0 and 255)
  
  // Set fan speed to 50% (127 out of 255)
  analogWrite(fanPin, 127);  
  delay(5000);  // Run for 5 seconds
  
  // Set fan speed to 0% (off)
  analogWrite(fanPin, 0);
  delay(5000);  // Fan off for 5 seconds
}