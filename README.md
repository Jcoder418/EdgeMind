# EdgeMind

Nice choice 😄 EdgeMind is a strong, modern project starter for on-device AI decision systems (ESP32 + TensorFlow Lite Micro).

Project layout and starter code are included. Run `model/train_model.py` to generate `edgemind_model.tflite` and convert it to a C array for inclusion in `model.h`.

Quick steps:

1. (Optional) Create and activate a Python venv.
2. Install TensorFlow: `pip install tensorflow` (or `tensorflow-cpu`).
3. Run: `python model/train_model.py` to generate `model/edgemind_model.tflite`.
4. Convert the `.tflite` to a C array (use `xxd -i` or `xxd -i edgemind_model.tflite > model.cc`) and include in `model.h`.
5. Open `firmware/EdgeMind.ino` in Arduino IDE and flash to your ESP32.
