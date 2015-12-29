Hosts {#hosts}
=====================

The hosts system handles special outputs like text, lights and other types of messages and 
inputs from analog controls like joysticks, buttons and pedals. The hosts map the inputs
from the analog signals to the event system. 

Architecture
------------

Hosts are dynamically loaded shared library objects (.so on Linux, .dll on Windows) with a
standardized interface. The interface is defined in C in the @ref host.h file. 

[TOC]

Standard Hosts
--------------

  * [USB][EXTERNAL] @subpage host_arduino
  * [NETWORK][EXTERNAL] @subpage host_raspberry_pi_gpio
  * [KEYBOARD][INTERNAL] @subpage host_pc_keyboard
