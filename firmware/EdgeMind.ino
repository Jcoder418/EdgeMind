#include "sensors.h"
#include "ai_inference.h"
#include "controller.h"

void setup() {
  Serial.begin(115200);
  setupController();
  setupAI();
}

void loop() {
  float sensorValue = readSensor();
  float decision = runInference(sensorValue);

  controlActuator(decision);

  Serial.print("Sensor: ");
  Serial.print(sensorValue);
  Serial.print(" | Decision: ");
  Serial.println(decision);

  delay(500);
}
