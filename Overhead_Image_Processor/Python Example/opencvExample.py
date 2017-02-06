import time
import cv2
import numpy as np
from PiVideoStream import PiVideoStream

# define range of red color in HSV
lower_red = np.array([0, 50, 50])
upper_red = np.array([10, 255, 255])

# define range of yellow color in HSV
#lower_yellow = np.array([20, 50, 50])
#upper_yellow = np.array([30, 255, 255])

# define range of blue color in HSV
lower_blue = np.array([110, 50, 50])
upper_blue = np.array([130, 255, 255])

# define range of green color in HSV
lower_green = np.array([50, 50, 50])
upper_green = np.array([70, 255, 255])

video_stream = PiVideoStream()
video_stream.start()

time.sleep(1)

while True:
    image = video_stream.read()

    # show the frame
    cv2.imshow("Frame", image)
    key = cv2.waitKey(1) & 0xFF

    hsv = cv2.cvtColor(image, cv2.COLOR_BGR2HSV)

    blue_mask = cv2.inRange(hsv, lower_blue, upper_blue)
    red_mask = cv2.inRange(hsv, lower_red, upper_red)
    green_mask = cv2.inRange(hsv, lower_green, upper_green)
#    yellow_mask = cv2.inRange(hsv, lower_yellow, upper_yellow)

    combined_mask = np.bitwise_or(blue_mask, red_mask)
    combined_mask = np.bitwise_or(combined_mask, green_mask)
 #   combined_mask = np.bitwise_or(combined_mask, yellow_mask)

    #res = cv2.bitwise_and(image, image, mask=mask)

    cv2.imshow('Blue Channel', blue_mask)
    cv2.imshow('Red Channel', red_mask)
    cv2.imshow('Green Channel', green_mask)
#    cv2.imshow('Yellow Channel', yellow_mask)
#   cv2.imshow('res', res)
    image, contours, hierarchy = cv2.findContours(red_mask, cv2.RETR_LIST, cv2.CHAIN_APPROX_SIMPLE)
    combined_mask2 = cv2.drawContours(combined_mask, contours, -1, (0, 255, 0), 3)

    cv2.imshow('Combined', combined_mask2)

    # if the `q` key was pressed, break from the loop
    if key == ord("q"):
        break

video_stream.stop()
cv2.destroyAllWindows()
