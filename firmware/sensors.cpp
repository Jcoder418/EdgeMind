
#include "sensors.h"
#include "config.h"
#include <Arduino.h>

// Simple sensor fusion: average of available sensors with basic scaling
float readSensor() {
  int raw1 = analogRead(SENSOR_PIN_1);
  int raw2 = analogRead(SENSOR_PIN_2);

  float val1 = raw1 * (SENSOR_SCALE_TO / SENSOR_MAX_RAW);
  float val2 = raw2 * (SENSOR_SCALE_TO / SENSOR_MAX_RAW);

  // Simple average fusion
  return (val1 + val2) / 2.0;
}

int readSensorRaw(int sensorIndex) {
  switch (sensorIndex) {
    case 1: return analogRead(SENSOR_PIN_1);
    case 2: return analogRead(SENSOR_PIN_2);
    default: return 0;
  }
}

