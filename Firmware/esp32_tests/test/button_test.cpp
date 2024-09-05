#include <Arduino.h>

#define BUTTON_PIN1 33 // GIOP33 pin connected to button
#define BUTTON_PIN2 15 // GIOP15 pin connected to button
#define BUTTON_PIN3 14 // GIOP14 pin connected to button

void setup() {
  // initialize serial communication at 9600 bits per second:
  Serial.begin(9600);
  // initialize the pushbutton pin as an pull-up input
  // the pull-up input pin will be HIGH when the switch is open and LOW when the switch is closed.
  pinMode(BUTTON_PIN1, INPUT_PULLUP);
  pinMode(BUTTON_PIN2, INPUT_PULLUP);
  pinMode(BUTTON_PIN3, INPUT_PULLUP);
}

void loop() {
  // read the state of the switchs/buttons:
  int buttonState1 = digitalRead(BUTTON_PIN1);
  int buttonState2 = digitalRead(BUTTON_PIN2);
  int buttonState3 = digitalRead(BUTTON_PIN3);

  // print out the button's state
  Serial.print(buttonState1);
  Serial.print(buttonState2);
  Serial.println(buttonState3);
}