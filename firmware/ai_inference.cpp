
#include "ai_inference.h"
#include "model.h"
#include <TensorFlowLite.h>
#include <tensorflow/lite/micro/all_ops_resolver.h>
#include <tensorflow/lite/micro/micro_interpreter.h>
#include <Arduino.h>

constexpr int kTensorArenaSize = 8 * 1024; // increase arena for more complex models
static uint8_t tensor_arena[kTensorArenaSize];

static tflite::MicroInterpreter* interpreter = nullptr;
static TfLiteTensor* input = nullptr;
static TfLiteTensor* output = nullptr;
static bool interpreter_ok = false;

void setupAI() {
  static tflite::AllOpsResolver resolver;
  const tflite::Model* model = tflite::GetModel(edgemind_model);
  if (model->version() != TFLITE_SCHEMA_VERSION) {
    Serial.println("Model schema version mismatch");
    interpreter_ok = false;
    return;
  }

  static tflite::MicroInterpreter static_interpreter(
      model,
      resolver,
      tensor_arena,
      kTensorArenaSize
  );
  interpreter = &static_interpreter;
  TfLiteStatus s = interpreter->AllocateTensors();
  interpreter_ok = (s == kTfLiteOk);
  if (!interpreter_ok) {
    Serial.println("Failed to allocate tensors");
    return;
  }

  input = interpreter->input(0);
  output = interpreter->output(0);
}

float runInference(float sensorValue) {
  if (!interpreter_ok) return 0.0f;

  // Support both float and int8 inputs (basic handling)
  if (input->type == kTfLiteFloat32) {
    input->data.f[0] = sensorValue;
  } else if (input->type == kTfLiteInt8) {
    // Simple conversion using input scale/zero_point
    float scale = input->params.scale;
    int32_t z = input->params.zero_point;
    int8_t q = (int8_t)round(sensorValue / scale) + (int8_t)z;
    input->data.int8[0] = q;
  }

  TfLiteStatus invoked = interpreter->Invoke();
  if (invoked != kTfLiteOk) {
    Serial.println("Inference failed");
    return 0.0f;
  }

  if (output->type == kTfLiteFloat32) {
    return output->data.f[0];
  } else if (output->type == kTfLiteInt8) {
    float scale = output->params.scale;
    int32_t z = output->params.zero_point;
    return (output->data.int8[0] - z) * scale;
  }

  return 0.0f;
}

bool aiHealthCheck() {
  return interpreter_ok;
}

