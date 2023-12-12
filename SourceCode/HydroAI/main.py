import tensorflow as tf
import numpy as np
import os

TF_MODEL_FILE_PATH = 'MLModel/FruityClassifyer.tflite'

interpreter = tf.lite.Interpreter(model_path=TF_MODEL_FILE_PATH)

print(interpreter.get_signature_list())

classify_lite = interpreter.get_signature_runner('serving_default')

os.system("fswebcam -r 640x480 -v -S 10 --set brightness=50% --no-banner ~/output/plant.png")

#Input = 'TestImages/ripe.png'

Input = 'output/plant.png'

img = tf.keras.utils.load_img(
    Input, target_size=(200, 200)
)

img_array = tf.keras.utils.img_to_array(img)
img_array = tf.expand_dims(img_array, 0)

predictions_lite = classify_lite(sequential_input=img_array)['dense_1']
score_lite = tf.nn.softmax(predictions_lite)

class_names = ['Ripe', 'SemiRipe', 'Unripe']

print(
    "This image most likely belongs to {} with a {:.2f} percent confidence."
    .format(class_names[np.argmax(score_lite)], 100 * np.max(score_lite))
)