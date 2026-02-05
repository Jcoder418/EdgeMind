import tensorflow as tf
import numpy as np

# Dummy sensor dataset
X = np.array([
    [30], [35], [40], [45], [50]
])  # sensor value
y = np.array([
    [0], [0], [1], [1], [1]
])  # decision (0=OFF, 1=ON)

model = tf.keras.Sequential([
    tf.keras.layers.Dense(8, activation='relu', input_shape=(1,)),
    tf.keras.layers.Dense(1, activation='sigmoid')
])

model.compile(optimizer='adam',
              loss='binary_crossentropy',
              metrics=['accuracy'])

model.fit(X, y, epochs=100)

# Convert to TFLite
converter = tf.lite.TFLiteConverter.from_keras_model(model)
tflite_model = converter.convert()

with open("edgemind_model.tflite", "wb") as f:
    f.write(tflite_model)

print("Saved edgemind_model.tflite")
