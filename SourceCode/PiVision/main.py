#https://medium.com/@thinhquyen9461/10-fruit-classification-using-traditional-machine-learning-for-beginner-275b6dcef837

import cv2
import numpy as np
import matplotlib.pyplot as plt


img = cv2.imread("images/TestImage3.jpeg")

image = np.zeros((400, 400, 3), dtype="uint8")
raw = image.copy()

low_green = np.array([25, 52, 72])
High_green = np.array([102, 255, 255])

low_blue = np.array([0, 0, 80])
high_blue = np.array([10, 10, 255])

RGB_img = cv2.cvtColor(img, cv2.COLOR_BGR2RGB)
HSV_img = cv2.cvtColor(img, cv2.COLOR_BGR2HSV)
mask = cv2.inRange(HSV_img, low_green, High_green)
Inv_Mask = 255 - mask
No_Green = cv2.bitwise_and(img, img, mask = Inv_Mask)



plt.imshow(No_Green)

plt.waitforbuttonpress()
plt.close('all')
