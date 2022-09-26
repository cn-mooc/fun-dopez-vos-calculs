import tensorflow as tf

print("TensorFlow version:", tf.__version__)
print("Is there any GPUs? ", tf.test.is_gpu_available())
print("Num GPUs Available: ", len(tf.config.list_physical_devices('GPU')))

if tf.config.list_physical_devices('GPU'):
  print("TensorFlow **IS** using the GPU")
else:
  print("TensorFlow **IS NOT** using the GPU")

print("Initialize a tf.constant matrix")
x = tf.constant([[1., 2., 3.],
                 [4., 5., 6.]])

print("tf.constant= ",x)
print("tf.constant.shape= ", x.shape)
print("tf.constant.dtype= ", x.dtype)
