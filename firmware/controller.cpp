#include "controller.h"
#include <Arduino.h>

#define RELAY_PIN 25

void setupController() {
  pinMode(RELAY_PIN, OUTPUT);
}

void controlActuator(float decision) {
  if (decision > 0.5) {
    digitalWrite(RELAY_PIN, HIGH);
  } else {
    digitalWrite(RELAY_PIN, LOW);
  }
}
