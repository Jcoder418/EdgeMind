# EdgeMind

EdgeMind is a lightweight on-device AI decision system for real-time control using an ESP32 and TensorFlow Lite Micro. It reads sensor data, runs a tiny neural model locally, and toggles an actuator (relay/motor) based on decisions.

**Quick Overview**
- **Inputs:** sensor(s) connected to the ESP32
- **Model:** Tiny TFLite model in `model/edgemind_model.tflite`
- **Output:** relay or motor driver controlled from `firmware/controller.*`

**Repository Layout**
- **data/**: training dataset (`data/dataset.csv`)
- **model/**: training script and model files (`model/train_model.py`, `model/edgemind_model.tflite`, `model/model.h`)
- **firmware/**: Arduino firmware and AI/sensor/controller code (`firmware/EdgeMind.ino`, `firmware/*.h`, `firmware/*.cpp`)
- **docs/**: architecture diagrams and flowcharts

**Quick Start (train locally)**
1. Create a Python virtual environment (optional): `python -m venv .venv` && `source .venv/bin/activate` (or use your platform equivalent).
2. Install minimal deps: `pip install numpy tensorflow` (use `tensorflow-cpu` on low-resource hosts).
3. Train and export a TFLite model:

```bash
python model/train_model.py
```

This writes `edgemind_model.tflite` to `model/`.

4. Convert the `.tflite` file to a C array for inclusion on the ESP32 (examples below).

**Convert TFLite → C source**
- On Linux/macOS/WSL: `xxd -i model/edgemind_model.tflite > model/edgemind_model.cc` then adapt and include the generated array in `model/model.h`.
- Alternatively use the `xxd` equivalent or Python script to embed the bytes.

**Firmware (ESP32)**
1. Open `firmware/EdgeMind.ino` in the Arduino IDE or PlatformIO.
2. Ensure the generated `model` C array is compiled into the project and `model.h` exposes `edgemind_model` and its length.
3. Flash to your ESP32 and monitor the serial output at `115200` baud.

**Design notes & pointers**
- `model/train_model.py` contains a small example network and writes `edgemind_model.tflite`.
- `firmware/ai_inference.*` shows how to use TFLite Micro interpreter and a tensor arena.
- `firmware/sensors.*` and `firmware/controller.*` contain the hardware interface and simple ON/OFF logic.

**Next steps & ideas**
- Add multiple sensors and sensor fusion.
- Quantize the model to 8-bit for smaller footprint and faster inference.
- Add CI to automatically build and size the firmware binary.
- Provide a helper script to convert `.tflite` → `.h`/.cc and update `model/model.h` automatically.

**Files to review**
- [model/train_model.py](model/train_model.py)
- [firmware/EdgeMind.ino](firmware/EdgeMind.ino)
- [model/model.h](model/model.h)

If you want, I can convert the generated TFLite model to a C array and embed it into `model/model.h`, add CI, or adapt the firmware for STM32 or Raspberry Pi Pico. Which would you like next?

---

**New features added**
- `--quantize` option for `model/train_model.py` to produce a dynamically quantized TFLite model.
- `model/convert_tflite_to_c.py` — helper script to convert a `.tflite` file into a `.cc` and minimal `model.h` exposing `edgemind_model` and `edgemind_model_len`.
- `requirements.txt` for Python dependencies and a `.gitignore`.

Example commands:

```bash
# Train and export a quantized tflite
python model/train_model.py --epochs 200 --quantize --out model/edgemind_model.tflite

# Convert to C source/header (writes model/edgemind_model.cc and model/model.h)
python model/convert_tflite_to_c.py model/edgemind_model.tflite model/edgemind_model.cc model/model.h

# Build/flash firmware with your preferred tool (PlatformIO / Arduino)
```

If you'd like, I can run the conversion for you (you'll need to run training locally or provide the `edgemind_model.tflite` file), then embed the generated `.cc` into `firmware/` and update the Arduino project to compile it automatically.
