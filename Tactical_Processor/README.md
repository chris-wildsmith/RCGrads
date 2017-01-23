# Tactical Processor

This is the main control code that runs on the Raspberry Pi onboard the chariot. It is connected to the overhead image processor using WiFi and the mbed using ethernet. The output waypoint file from the waypoint generator can be transfered before running the program using an FTP connection.

The main program takes the waypoints from the file to know the plan of where to go and then uses the overhead coordinates from the overhead processor to calculate its current position. It then notes the current orientation and then calculates what orientation it needs to be to head to the next waypoint. It then uses an onboard IMU to actually carry out the turns as this means it doesn't have to rely on the slower updates from overhead.

It outputs the commands to the mbed using some predefined messages over the ethernet interface.
