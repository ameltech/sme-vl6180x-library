SmartEverything ST VL6180X  Proximity & Ambient Light Library
=============================================================

This is a library for the ST VL6180X component.

The VL6180X is the latest product based on ST’s patented FlightSenseTMtechnology. 
This is a ground-breaking technology allowing absolute distance to be measured independent of target reflectance. 
Instead of estimating the distance by measuring the amount of light reflected back from the object 
(which is significantly influenced by color and surface), the VL6180X precisely measures the time the light takes 
to travel to the nearest object and reflect back to the sensor (Time-of-Flight).

Combining an IR emitter, a range sensor and an ambient light sensor in a three-in-one ready-to-use reflowable package,
the VL6180X is easy to integrate and saves the end-product maker long and costly optical and mechanical design optimizations.

The module is designed for ultra low power operation.
Ranging and ALS measurements can be automatically performed at user defined intervals.
Multiple threshold and interrupt schemes are supported to minimize host operations.


[* ST VL6180X Home Page *](http://www.st.com/web/catalog/mmc/FM132/SC626/PF260441?icmp=pf260441_pron_p3609p_sep2014&sc=proximitysensor)

Host control and result reading is performed using an I2C interfac, no extra pin are required.

It was principally designed to work with the SmartEverything board, but could
be easily adapt and use on every Arduino and Arduino Certified boards.

[*Library is based on the useful project done by Kris Winer*](https://github.com/kriswiner/VL6180)

Written by Mik <smkk@amel-tech.com>.  

Repository Contents 
-------------------

* **/examples** - Example sketches for the library (.ino). Run these from the Arduino IDE. 
* **/src** - Source files for the library (.cpp, .h).
* **library.properties** - General library properties for the Arduino package manager.

Documentation
--------------

* **[Installing an Arduino Library Guide](http://www.arduino.cc/en/Guide/Libraries#toc3)** - How to install a SmartEverything library on the Arduino IDE using the Library Manager


License Information
-------------------

This product is _**open source**_! 

Please use, reuse, and modify these files as you see fit. Please maintain
attribution to Amel Tecnologie and release anything derivative under the same license.

Distributed as-is; no warranty is given.

