# Overhead Image Processor

This code is the overhead image processing code. This code ran in MatLab on a laptop which had a camera attached that was mounted over the arena.

The chariot top was made up of three colours. The main middle section of the chariot was red which is what the code would look for to start with. Once it found that then it would look for the two coloured end of the top, one being green and the other being blue. From this the code could work out where the chariot was in the image and then use the two coloured ends to work out the orientation.

This information would then be passed to the onboard tactical processor by WiFi.
The intention originally was also to have this code send details of the locations of the obstacles within the arena but this was never added.
