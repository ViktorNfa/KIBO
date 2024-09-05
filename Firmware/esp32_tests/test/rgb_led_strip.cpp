#include <Arduino.h>

#define BLUE_PIN  27  // The ESP32 pin GPIO23 connects to the blue pin of LED strip via relay 1
#define RED_PIN   16  // The ESP32 pin GPIO22 connects to the red pin of LED strip via relay 2
#define GREEN_PIN 17  // The ESP32 pin GPIO21 connects to the green pin of LED strip via relay 3

void setup() {
  Serial.begin(115200);

  // initialize ESP32 pins as digital output pins
  pinMode(BLUE_PIN,  OUTPUT);
  pinMode(RED_PIN,   OUTPUT);
  pinMode(GREEN_PIN, OUTPUT);
}

// the loop function runs over and over again forever
void loop() {
  Serial.println("The LED strip is turned red");
  digitalWrite(BLUE_PIN,  LOW);
  digitalWrite(RED_PIN,   HIGH);
  digitalWrite(GREEN_PIN, LOW);
  delay(2000);

  Serial.println("The LED strip is turned green");
  digitalWrite(BLUE_PIN,  LOW);
  digitalWrite(RED_PIN,   LOW);
  digitalWrite(GREEN_PIN, HIGH);
  delay(2000);

  Serial.println("The LED strip is turned blue");
  digitalWrite(BLUE_PIN,  HIGH);
  digitalWrite(RED_PIN,   LOW);
  digitalWrite(GREEN_PIN, LOW);
  delay(2000);

  Serial.println("The LED strip is turned yellow");
  digitalWrite(BLUE_PIN,  LOW);
  digitalWrite(RED_PIN,   HIGH);
  digitalWrite(GREEN_PIN, HIGH);
  delay(2000);

  Serial.println("The LED strip is turned magenta");
  digitalWrite(BLUE_PIN,  HIGH);
  digitalWrite(RED_PIN,   HIGH);
  digitalWrite(GREEN_PIN, LOW);
  delay(2000);

  Serial.println("The LED strip is turned cyan");
  digitalWrite(BLUE_PIN,  HIGH);
  digitalWrite(RED_PIN,   LOW);
  digitalWrite(GREEN_PIN, HIGH);
  delay(2000);

  Serial.println("The LED strip is turned white");
  digitalWrite(BLUE_PIN,  HIGH);
  digitalWrite(RED_PIN,   HIGH);
  digitalWrite(GREEN_PIN, HIGH);
  delay(2000);
}