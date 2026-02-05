#include "ai_inference.h"
#include "model.h"
#include <TensorFlowLite.h>
#include <tensorflow/lite/micro/all_ops_resolver.h>
#include <tensorflow/lite/micro/micro_interpreter.h>

constexpr int kTensorArenaSize = 2 * 1024;
uint8_t tensor_arena[kTensorArenaSize];

static tflite::MicroInterpreter* interpreter = nullptr;
static TfLiteTensor* input = nullptr;
static TfLiteTensor* output = nullptr;

void setupAI() {
  static tflite::AllOpsResolver resolver;
  static tflite::MicroInterpreter static_interpreter(
      tflite::GetModel(edgemind_model),
      resolver,
      tensor_arena,
      kTensorArenaSize
  );
  interpreter = &static_interpreter;
  interpreter->AllocateTensors();
  input = interpreter->input(0);
  output = interpreter->output(0);
}

float runInference(float sensorValue) {
  if (!interpreter) return 0.0f;
  input->data.f[0] = sensorValue;
  interpreter->Invoke();
  return output->data.f[0];
}
