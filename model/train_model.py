import argparse
import os
import tensorflow as tf
import numpy as np


def build_and_train(epochs=100):
    # Dummy sensor dataset
    X = np.array([[30], [35], [40], [45], [50]], dtype=np.float32)
    y = np.array([[0], [0], [1], [1], [1]], dtype=np.float32)

    model = tf.keras.Sequential([
        tf.keras.layers.Dense(8, activation='relu', input_shape=(1,)),
        tf.keras.layers.Dense(1, activation='sigmoid')
    ])

    model.compile(optimizer='adam',
                  loss='binary_crossentropy',
                  metrics=['accuracy'])

    model.fit(X, y, epochs=epochs)
    return model


def export_tflite(model, output_path, quantize=False):
    converter = tf.lite.TFLiteConverter.from_keras_model(model)
    if quantize:
        # Apply dynamic range quantization (small binary size, no representative dataset needed)
        converter.optimizations = [tf.lite.Optimize.DEFAULT]
    tflite_model = converter.convert()

    os.makedirs(os.path.dirname(output_path), exist_ok=True)
    with open(output_path, "wb") as f:
        f.write(tflite_model)

    print(f"Saved {output_path}")


def main():
    parser = argparse.ArgumentParser(description="Train a tiny model and export a TFLite file")
    parser.add_argument("--epochs", type=int, default=100)
    parser.add_argument("--quantize", action="store_true", help="Apply dynamic range quantization")
    parser.add_argument("--out", type=str, default="edgemind_model.tflite", help="Output tflite path")

    args = parser.parse_args()

    model = build_and_train(epochs=args.epochs)
    export_tflite(model, args.out, quantize=args.quantize)


if __name__ == "__main__":
    main()
