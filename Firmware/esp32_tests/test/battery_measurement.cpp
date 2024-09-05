#include <Arduino.h>

float VBAT1 = 0.0f;
float VBAT1_prev = 0.0f;
float VBAT1_prev2 = 0.0f;
float VBAT1_prev3 = 0.0f;
float VBAT1_prev4 = 0.0f;

float VBAT2 = 0.0f;
float VBAT2_prev = 0.0f;
float VBAT2_prev2 = 0.0f;
float VBAT2_prev3 = 0.0f;
float VBAT2_prev4 = 0.0f;

float VBAT3 = 0.0f;
float VBAT3_prev = 0.0f;
float VBAT3_prev2 = 0.0f;
float VBAT3_prev3 = 0.0f;
float VBAT3_prev4 = 0.0f;

// the setup routine runs once when you press reset:
void setup() {
  Serial.begin(9600);
  // while (!Serial);
  Serial.println("Battery voltage measurement demo");
}

// the loop routine runs over and over again forever:
void loop() {
  float VBAT1 = (27.6f/22.0f) * 3.24f * float(analogRead(34)) / 4096.0f;  // LiPo battery
  float VBAT1_avg = (VBAT1 + VBAT1_prev + VBAT1_prev2 + VBAT1_prev3 + VBAT1_prev4) / 5.0f;

  Serial.print("Battery Voltage 1 Average = ");
  Serial.print(VBAT1_avg, 2);
  Serial.println(" V");

  VBAT1_prev4 = VBAT1_prev3;
  VBAT1_prev3 = VBAT1_prev2;
  VBAT1_prev2 = VBAT1_prev;
  VBAT1_prev = VBAT1;

  float VBAT2 = (1.68f/0.68f) * 3.19f * float(analogRead(35)) / 4096.0f;  // LiPo battery
  float VBAT2_avg = (VBAT2 + VBAT2_prev + VBAT2_prev2 + VBAT2_prev3 + VBAT2_prev4) / 5.0f;

  Serial.print("Battery Voltage 2 Average = ");
  Serial.print(VBAT2_avg, 2);
  Serial.println(" V");

  VBAT2_prev4 = VBAT2_prev3;
  VBAT2_prev3 = VBAT2_prev2;
  VBAT2_prev2 = VBAT2_prev;
  VBAT2_prev = VBAT2;

  float VBAT3 = (7.6f/2.0f) * 3.22f * float(analogRead(32)) / 4096.0f;  // LiPo battery
  float VBAT3_avg = (VBAT3 + VBAT3_prev + VBAT3_prev2 + VBAT3_prev3 + VBAT3_prev4) / 5.0f;

  Serial.print("Battery Voltage 3 Average = ");
  Serial.print(VBAT3_avg, 2);
  Serial.println(" V");

  VBAT3_prev4 = VBAT3_prev3;
  VBAT3_prev3 = VBAT3_prev2;
  VBAT3_prev2 = VBAT3_prev;
  VBAT3_prev = VBAT3;
}