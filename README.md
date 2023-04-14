# Friend Detector by Ricardo Oliveira, forked by Skickar 9/30/2018

This project requires: A NodeMCU, a mini-breadboard (or full sized one), and a 4 pin RGB LED. 

 The function of this code is to read nearby Wi-Fi traffic in the form of packets. These packets are compared to a list of MAC addresses we wish to track, and if the MAC address of a packet matches one on the list, we turn on a colored LED that is linked to the user owning the device. 

 For example, when my roommate comes home, the	transmissions from his phone will be detected and cause the blue LED to turn on until his phone is no longer detected. It can detect more than one phone at a time, meaning if my phone (red) and my roommate's phone (blue) are both home, the LED will show purple. 

## For more information on the design go to: https://www.hackster.io/ricardooliveira/esp8266-friend-detector-12542e

