import time
import cv2
import numpy as np
from PiVideoStream import PiVideoStream

# Note: In OpenCV HSV, H values range from 0-180
# Define range of red color in HSV
lower_red = np.array([160, 70, 70])
upper_red = np.array([180, 255, 255])

# Define range of yellow color in HSV
lower_yellow = np.array([20, 70, 70])
upper_yellow = np.array([30, 255, 255])

# Define range of blue color in HSV
lower_blue = np.array([90, 70, 70])
upper_blue = np.array([150, 255, 255])

# Define range of green color in HSV
lower_green = np.array([45, 70, 70])
upper_green = np.array([85, 255, 255])

# Create the video stream object
video_stream = PiVideoStream()
# Start the video stream thread
video_stream.start()

# Wait for the camera to start
time.sleep(1)
try:
    while True:
        # Read the latest image from the video
        image = video_stream.read()

        # show the frame
        cv2.imshow("Frame", image)
        key = cv2.waitKey(1) & 0xFF

        # Blur the image to reduce noise
        cv2.medianBlur(image, 5)

        # Convert the image from BGR colourspace to HSV
        hsv = cv2.cvtColor(image, cv2.COLOR_BGR2HSV)

        # Create masks of the various colours in the image
        blue_mask = cv2.inRange(hsv, lower_blue, upper_blue)
        red_mask = cv2.inRange(hsv, lower_red, upper_red)
        green_mask = cv2.inRange(hsv, lower_green, upper_green)
        yellow_mask = cv2.inRange(hsv, lower_yellow, upper_yellow)

        # Create one combined mask of all of the colours
        combined_mask = np.bitwise_or(blue_mask, red_mask)
        combined_mask = np.bitwise_or(combined_mask, green_mask)
        combined_mask = np.bitwise_or(combined_mask, yellow_mask)

        # Do some some processing to combine smaller or very close areas
        combined_mask = cv2.erode(combined_mask, None, iterations=2)
        combined_mask = cv2.dilate(combined_mask, None, iterations=2)

        # Find the contours in the combined mask
        combined_contours = cv2.findContours(combined_mask.copy(), cv2.RETR_EXTERNAL, cv2.CHAIN_APPROX_SIMPLE)[-2]

        # Check that we have found some contours
        if len(combined_contours) > 0:
            # Find the largest contour in the mask
            biggest_combined_contour = max(combined_contours, key=cv2.contourArea)

            # Find the moment (weighted average of the pixel intensities) of the biggest contour
            M = cv2.moments(biggest_combined_contour)

            # Find the centre of the contour
            centre_of_combined_contour = (int(M["m10"] / M["m00"]), int(M["m01"] / M["m00"]))

            # Get the coordinates and size of a rectangle that will contain all of the biggest area
            x, y, w, h = cv2.boundingRect(biggest_combined_contour)

            # Draw the rectangle on the combined mask
            cv2.rectangle(combined_mask, (x, y), (x+w, y+h), (200, 0, 0), 2)

        # Show all of the masks on screen
        cv2.imshow('Blue Channel', blue_mask)
        cv2.imshow('Red Channel', red_mask)
        cv2.imshow('Green Channel', green_mask)
        cv2.imshow('Yellow Channel', yellow_mask)
        cv2.imshow('Combined', combined_mask)

        # if the `q` key was pressed, break from the loop
        if key == ord("q"):
            break

finally:
    # The application has quit so close down gracefully
    # Stop the video stream thread
    video_stream.stop()
    # Close all windows that OpenCV created
    cv2.destroyAllWindows()

