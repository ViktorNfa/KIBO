#include <Arduino.h>
#include <Adafruit_MCP23X17.h>

Adafruit_MCP23X17 mcp;

// Motor A
int motor1Pin1 = 8; 
int motor1Pin2 = 0; 
int enable1Pin = 19; 

// Setting PWM properties
const int freq = 30000;
const int pwmChannel = 0;
const int resolution = 8;
int dutyCycle = 200;

void setup() {
  Serial.begin(115200);
  //while (!Serial);
  Serial.print("Testing DC Motor...");

  // uncomment appropriate mcp.begin
  if (!mcp.begin_I2C()) {
  //if (!mcp.begin_SPI(CS_PIN)) {
    Serial.println("Error.");
    while (1);
  }

  // sets the pins as outputs:
  mcp.pinMode(motor1Pin1, OUTPUT);
  mcp.pinMode(motor1Pin2, OUTPUT);
  pinMode(enable1Pin, OUTPUT);
  
  // configure LED PWM functionalitites
  ledcSetup(pwmChannel, freq, resolution);
  
  // attach the channel to the GPIO to be controlled
  ledcAttachPin(enable1Pin, pwmChannel);
}

void loop() {
  // Move the DC motor forward at maximum speed
  Serial.println("Moving Forward");
  mcp.digitalWrite(motor1Pin1, LOW);
  mcp.digitalWrite(motor1Pin2, HIGH); 
  delay(2000);

  // Stop the DC motor
  Serial.println("Motor stopped");
  mcp.digitalWrite(motor1Pin1, LOW);
  mcp.digitalWrite(motor1Pin2, LOW);
  delay(1000);

  // Move DC motor backwards at maximum speed
  Serial.println("Moving Backwards");
  mcp.digitalWrite(motor1Pin1, HIGH);
  mcp.digitalWrite(motor1Pin2, LOW); 
  delay(2000);

  // Stop the DC motor
  Serial.println("Motor stopped");
  mcp.digitalWrite(motor1Pin1, LOW);
  mcp.digitalWrite(motor1Pin2, LOW);
  delay(1000);

  // Move DC motor forward with increasing speed
  mcp.digitalWrite(motor1Pin1, HIGH);
  mcp.digitalWrite(motor1Pin2, LOW);
  while (dutyCycle <= 255){
    ledcWrite(pwmChannel, dutyCycle);   
    Serial.print("Forward with duty cycle: ");
    Serial.println(dutyCycle);
    dutyCycle = dutyCycle + 5;
    delay(500);
  }
  dutyCycle = 200;
}