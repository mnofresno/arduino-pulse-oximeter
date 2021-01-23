# Pulse-Oximeter With Arduino and MAX30100

## Description:

The aim of this project is to create an automatic pulse-oximeter device for monitoring the SpO2 blood saturation and the heart rate using the MAX30100 Arduino module.

The output of the measurement is shown in a white 0.96 128x64 OLED display.

The application runs on an Arduino Nano v3.0 Atmega 328 card.

## Dependencies:

This Arduino project depends on the following libraries:

* [Pulse oximeter driver](https://github.com/oxullo/Arduino-MAX30100)
* [Display driver](https://github.com/olikraus/u8g2)

## Connection diagram:

![Arduino connected with MAX30100 and OLED display](schematic.png "Connection diagram")

## Bill of materials:

* MAX30102 Pulse oximeter sensor (Costs approx. 3 U$D)
* Arduino NANO Atmega328 (Costs approx. 10 U$D)
* Display Oled 1.3 Blanco 128x64 I2c Delta Iot (Costs approx. 8 U$D)
* Various dupont jumper wires (Costs approx. 1 U$D)

Total cost: 22 U$D

## TODO:

* Add a dependency manager file that will allow us to download the libraries automatically
* Construct a 3D printable cabinet and upload his design
* Include some photos of the device
* Include some IOT features like pushing data to wifi
* Improve connection diagram

## DISCLAIMER:

This device is currently a work in progress and its stability or accuracy is not the best as it does not have a cabinet that keeps your finger in place and firmly pressed to measure.
<b>Do not rely solely on this device</b> as a critical medical decision-making process.