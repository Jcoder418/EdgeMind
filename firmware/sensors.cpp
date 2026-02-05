#include "sensors.h"
#include <Arduino.h>

float readSensor() {
  // Example: analog pin 34, scale to 0-100
  int raw = analogRead(34);
  return raw * (100.0 / 4095.0);
}
