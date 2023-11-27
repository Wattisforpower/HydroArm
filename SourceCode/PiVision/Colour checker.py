import os
import cv2
import numpy as np
import matplotlib.pyplot as plt

#lower_red=np.array([0,0,200], dtype = "uint8")
#upper_red=np.array([100,100,255], dtype = "uint8")
#os.system("fswebcam -r 640x480 -v -S 10 --set brightness=50% --no-banner ~/output/plant.png")
img = cv2.imread("plant.png")
RGB_img = cv2.cvtColor(img,cv2.COLOR_BGR2RGB)

#mask = cv2.inRange(RGB_img, lower_red,upper_red)
#detected_output = cv2.bitwise_and(RGB_img, RGB_img, mask = mask)

plt.imshow(RGB_img)
#cv2.imshow("RED", detected_output)

plt.waitforbuttonpress()
plt.close('all')

