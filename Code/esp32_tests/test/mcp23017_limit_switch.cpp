// Reads a limit switch attached to a MCP23XXX pin.
#include <Adafruit_MCP23X17.h>

#define LIMIT_SWITCH 12     // MCP23XXX pin LIMIT_SWITCH is connected to

Adafruit_MCP23X17 mcp;

void setup() {
  Serial.begin(115200);
  //while (!Serial);
  Serial.println("MCP23xxx Limit Switch Test!");

  // uncomment appropriate mcp.begin
  if (!mcp.begin_I2C()) {
  //if (!mcp.begin_SPI(CS_PIN)) {
    Serial.println("Error.");
    while (1);
  }

  // configure pin for output
  mcp.pinMode(LIMIT_SWITCH, INPUT);

  Serial.println("Looping...");
}

void loop() {
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