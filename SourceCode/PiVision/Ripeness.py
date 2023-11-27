import os
import cv2
import numpy as np
from matplotlib import pyplot as plt

#os.system("fswebcam -r 640x480 -v -S 10 --set brightness=50% --no-banner ~/output/plant.png")

RGB_img = cv2.imread("unripe.png")

 
lower_red=np.array([0,0,50], dtype = "uint8")
upper_red=np.array([60,55,255], dtype = "uint8")

maskred = cv2.inRange(RGB_img, lower_red,upper_red)
reddetected_output = cv2.bitwise_and(RGB_img, RGB_img, mask = maskred)

no_red = cv2.countNonZero(maskred)
print('The number of red pixels are: ' +str(no_red))

if no_red < 7000:
    print("Unripe")
elif 7001 < no_red and no_red < 9000:
    print("Semiripe")
elif 9001 < no_red:
    print("Ripe")

cv2.imshow("RGB", RGB_img)
cv2.imshow("RED", reddetected_output)

cv2.waitKey(0)
cv2.destroyAllWindows()
