#ifndef CONTROLLER_H
#define CONTROLLER_H

void setupController();
// decision: 0.0 - 1.0 (maps to PWM duty or on/off)
void controlActuator(float decision);

// Turn actuator off immediately
void emergencyStop();

#endif // CONTROLLER_H
