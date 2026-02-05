#ifndef CONFIG_H
#define CONFIG_H

// Pin configuration
#define SENSOR_PIN_1 34
#define SENSOR_PIN_2 35
#define RELAY_PIN 25
#define STATUS_LED_PIN 2

// Control parameters
#define CONTROL_PWM_CHANNEL 0
#define CONTROL_PWM_FREQ 5000
#define CONTROL_PWM_RESOLUTION 8 // 8-bit resolution

// Safety / behavior
#define SAFETY_TIMEOUT_MS 5000 // turn actuator off if no inference for this period

// Sensor calibration / scaling
#define SENSOR_MAX_RAW 4095.0
#define SENSOR_SCALE_TO 100.0

#endif // CONFIG_H
