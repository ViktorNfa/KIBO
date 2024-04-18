// Main file to test hardware on ESP32

// Include Wire Library for I2C
#include <Wire.h>
 
// Include Adafruit PCA9685 Servo Library
#include <Adafruit_PWMServoDriver.h>

// Include Adafruit MPU6050 IMU and SSD1306 OLED Library
#include <Adafruit_MPU6050.h>
#include <Adafruit_SSD1306.h>
#include <Adafruit_Sensor.h>

// Include Adafruit MCP23X17 Library
#include <Adafruit_MCP23X17.h>
 
// Creat object to represent PCA9685 at default I2C address
Adafruit_PWMServoDriver pca9685 = Adafruit_PWMServoDriver(0x40);

// Define maximum and minimum number of "ticks" for the servo motors
// Range from 0 to 4095
// This determines the pulse width
 
#define SERVOMIN  80  // Minimum value
#define SERVOMAX  600  // Maximum value
 
// Define servo motor connections (expand as required)
#define SER0  0   //Servo Motor 0 on connector 0
#define SER1  1  //Servo Motor 1 on connector 12
 
// Variables for Servo Motor positions (expand as required)
int pwm0;
int pwm1;

// Variables for Servo Motor positions
int posDegrees = 0;

// Creat object to represent MPU6050 and SSD1306
Adafruit_MPU6050 mpu;
Adafruit_SSD1306 display = Adafruit_SSD1306(128, 64, &Wire);

// Variables for HC-SR04 Ultrasonic Sensor
const int trigPin = 5;
const int echoPin = 18;
#define SOUND_SPEED 0.034 //define sound speed in cm/uS
#define CM_TO_INCH 0.393701
long duration;
float distanceCm;
float distanceInch;

// Objects and variables for MCP23X17
Adafruit_MCP23X17 mcp;
#define LIMIT_SWITCH 12     // MCP23XXX pin LIMIT_SWITCH is connected to
 
void setup() {
  // Serial monitor setup
  Serial.begin(115200);
  // while (!Serial);
  Serial.println("MPU6050+OLED+HC-SR04+PCA9685+MCP23X17 with limit switch demo");

  // Initialize PCA9685
  pca9685.begin();
 
  // Set PWM Frequency to 50Hz
  pca9685.setPWMFreq(50);

  pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
  pinMode(echoPin, INPUT); // Sets the echoPin as an Input

  if (!mpu.begin()) {
    Serial.println("Sensor init failed");
    while (1)
      yield();
  }
  Serial.println("Found a MPU-6050 sensor");

  // SSD1306_SWITCHCAPVCC = generate display voltage from 3.3V internally
  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { // Address 0x3C for 128x64
    Serial.println(F("SSD1306 allocation failed"));
    for (;;)
      ; // Don't proceed, loop forever
  }
  display.display();
  delay(500); // Pause for 2 seconds
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setRotation(0);

  if (!mcp.begin_I2C()) {
    Serial.println("Error with MCP23X17.");
    while (1);
  }
  // configure pin for output
  mcp.pinMode(LIMIT_SWITCH, INPUT);
}
 
void loop() {
  // Determine PWM pulse width
  pwm0 = map(posDegrees, 0, 180, SERVOMIN, SERVOMAX);
  pwm1 = map(posDegrees, 0, 180, SERVOMIN, SERVOMAX);
  // Write to PCA9685
  pca9685.setPWM(SER0, 0, pwm0);
  pca9685.setPWM(SER1, 0, pwm1);
  // Print to serial monitor
  Serial.print("Motor 0 & 1 = ");
  Serial.println(posDegrees);
  // Increment posDegrees by 1 if it is less than 180, otherwise reset to 0
  if (posDegrees == 180) 
    posDegrees = 0;
  else
    posDegrees++;

  // Clears the trigPin
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  // Sets the trigPin on HIGH state for 10 micro seconds
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  
  // Reads the echoPin, returns the sound wave travel time in microseconds
  duration = pulseIn(echoPin, HIGH);
  
  // Calculate the distance
  distanceCm = duration * SOUND_SPEED/2;
  
  // Convert to inches
  distanceInch = distanceCm * CM_TO_INCH;

  sensors_event_t a, g, temp;
  mpu.getEvent(&a, &g, &temp);

  display.clearDisplay();
  display.setCursor(0, 0);

  Serial.print("Accelerometer ");
  Serial.print("X: ");
  Serial.print(a.acceleration.x, 1);
  Serial.print(" m/s^2, ");
  Serial.print("Y: ");
  Serial.print(a.acceleration.y, 1);
  Serial.print(" m/s^2, ");
  Serial.print("Z: ");
  Serial.print(a.acceleration.z, 1);
  Serial.println(" m/s^2");

  display.println("Accelerometer - m/s^2");
  display.print(a.acceleration.x, 1);
  display.print(", ");
  display.print(a.acceleration.y, 1);
  display.print(", ");
  display.print(a.acceleration.z, 1);
  display.println("");

  Serial.print("Gyroscope ");
  Serial.print("X: ");
  Serial.print(g.gyro.x, 1);
  Serial.print(" rps, ");
  Serial.print("Y: ");
  Serial.print(g.gyro.y, 1);
  Serial.print(" rps, ");
  Serial.print("Z: ");
  Serial.print(g.gyro.z, 1);
  Serial.println(" rps");

  display.println("Gyroscope - rps");
  display.print(g.gyro.x, 1);
  display.print(", ");
  display.print(g.gyro.y, 1);
  display.print(", ");
  display.print(g.gyro.z, 1);
  display.println("");

  // Prints the distance in the Serial Monitor
  Serial.print("Distance (cm): ");
  Serial.println(distanceCm);
  Serial.print("Distance (inch): ");
  Serial.println(distanceInch);

  //Display distance in cm
  display.println("Distance: ");
  display.print(distanceCm);
  display.print(" cm");

  display.display();

  if (mcp.digitalRead(LIMIT_SWITCH) == HIGH)
  {
    Serial.println("Activated!");
  }
  else
  {
    Serial.println("Not activated.");
  }

  delay(100);
}