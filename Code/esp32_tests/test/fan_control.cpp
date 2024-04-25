#include <Arduino.h>

// the transistor which controls the motor will be attached to digital pin 27
int motorControl = 27;

// the setup routine runs once when you press reset:
void setup() {
  // make the transistor's pin an output:
  pinMode(motorControl, OUTPUT);  
}

// the loop routine runs over and over again forever:
void loop() {
  // ramp up the motor speed
  for(int x = 0; x <= 255; x++){
    analogWrite(motorControl, x);
    delay(50);
  }

  // ramp down the motor speed
  for(int x = 255; x >= 0; x--){
    analogWrite(motorControl, x);
    delay(50);
  } 

  delay(1);        // delay in between reads for stability
}