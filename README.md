Hosts {#hosts}
=====================

The hosts system handles special outputs like text, lights and other types of messages and 
inputs from analog controls like joysticks, buttons and pedals. The hosts map the inputs
from the analog signals to the event system. 

Architecture
------------

Hosts are dynamically loaded shared library objects (.so on Linux, .dll on Windows) with a
standardized interface. The interface is defined in C in the @ref host.h file. 

Source for hosts
----------------

This repository contains some standard hosts. They can be downloaded, compiled
and then installed on the machine. Some hosts may can be received from packages, 
if their complexity serves a custom repository.

[TOC]

Standard Hosts
--------------

  * [USB][EXTERNAL] @subpage host_arduino
  * [NETWORK][EXTERNAL] @subpage host_raspberry_pi_gpio
  * [KEYBOARD][INTERNAL] @subpage host_pc_keyboard
