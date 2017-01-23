# Rampaging Chariots - Graduate Team

This repository contains all of the code for the graduate entry for the Rampaging Chariots competition. 

The parts of the repository are as follows:
 - mbed - This is the microcontroller code that handles the communication with the motor control boards. This receives messages from the Raspberry Pi over ethernet. This code is written in C and is designed to be used in the online mbed IDE (https://developer.mbed.org/compiler/) so this code is just an export for reference.
 - Overhead Image Processor - This is the code that runs on the laptop connected to the webcam which is mounted over the arena. This is written in MatLab
 - Tactical Processor - This is the code that runs on the Raspberry Pi that is onboard the chariot. This is written in Python
 - Waypoint Generator - This is the Windows based tool that allows you to create waypoints for the chariot to follow and generates the file that the tactical processor code takes in to work out where to go next. This code is written in C#.
