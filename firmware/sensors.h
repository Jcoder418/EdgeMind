#ifndef SENSORS_H
#define SENSORS_H

// Read sensors and return fused value (0.0 - 100.0)
float readSensor();

// Read raw sensor by index (1-based). Returns raw ADC reading.
int readSensorRaw(int sensorIndex);

#endif // SENSORS_H
