Raspberry Pi GPIO Host {#host_raspberry_pi_gpio}
======================

This host utilizes the Raspberry Pi's GPIO pins to capture inputs from
a set of buttons. These inputs are captured using the [WiringPi](http://wiringpi.com/) 
library to register GPIO changes as interrupts and captures them. The captured
interrupts get converted to piga::GameControl values and are sent over 
the network to the main console host. 

This host therefore requires networking to be enabled on the console!
