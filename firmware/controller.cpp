
#include "controller.h"
#include "config.h"
#include <Arduino.h>

static unsigned long last_inference_ts = 0;

void setupController() {
  pinMode(RELAY_PIN, OUTPUT);
  pinMode(STATUS_LED_PIN, OUTPUT);
  // Setup PWM channel if supported (ESP32)
  ledcSetup(CONTROL_PWM_CHANNEL, CONTROL_PWM_FREQ, CONTROL_PWM_RESOLUTION);
  ledcAttachPin(RELAY_PIN, CONTROL_PWM_CHANNEL);
}

void controlActuator(float decision) {
  // decision expected 0.0 - 1.0
  if (decision < 0) decision = 0;
  if (decision > 1) decision = 1;

  int maxDuty = (1 << CONTROL_PWM_RESOLUTION) - 1;
  int duty = (int)(decision * maxDuty);
  ledcWrite(CONTROL_PWM_CHANNEL, duty);

  // Blink status LED when actuator active
  digitalWrite(STATUS_LED_PIN, duty > 0 ? HIGH : LOW);

  last_inference_ts = millis();
}

void emergencyStop() {
  ledcWrite(CONTROL_PWM_CHANNEL, 0);
  digitalWrite(STATUS_LED_PIN, LOW);
}

