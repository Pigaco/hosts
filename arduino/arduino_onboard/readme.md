Arduino On-Board code {#host_arduino_onboard}
=============================================

This code is compiled using the [arduino makefile](https://github.com/sudar/Arduino-Makefile), explained 
[here](http://hardwarefun.com/tutorials/compiling-arduino-sketches-using-makefile)

# Architecture

This onboard code provides the inputs and outputs for a single player. Each player 
input set (6 buttons with integrated LEDs + a 4 directional joystick with an action
button on top) is designated to a single arduino, which manages access over serial 
and connects to the host component on the host side (over USB).

## Required environment variables

The following environment variables are required to compile the arduino code:

    ARDUINO_DIR – Directory where Arduino is installed
    ARDMK_DIR – Directory where you have copied the makefile
    AVR_TOOLS_DIR – Directory where avr tools are installed
