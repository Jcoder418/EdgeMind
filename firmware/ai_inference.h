#ifndef AI_INFERENCE_H
#define AI_INFERENCE_H

void setupAI();
// Returns decision in range 0.0 - 1.0 (probability or mapped value)
float runInference(float sensorValue);

// Call periodically to check model/arena health (returns true if OK)
bool aiHealthCheck();

#endif // AI_INFERENCE_H
