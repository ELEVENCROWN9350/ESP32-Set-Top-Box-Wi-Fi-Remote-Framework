# 7Star STB Wi-Fi Remote

This project converts a 7Star Digital Set-Top Box into a Wi-Fi controlled device using an ESP32-C3.
Instead of transmitting infrared signals, the ESP32 directly injects decoded remote-control signals into the output line of the STB's IR receiver.
The result is a fast and reliable Wi-Fi remote that can be controlled from a web browser or Android application.


## Features

- Wi-Fi remote control
- Web interface
- Android app support
- No IR LED required
- Direct receiver-line injection
- Power, OK, Navigation buttons
- Number keys 0-9
- Menu, Exit, Mute, Recall
- ESP32-C3 compatible


## Hardware Required

- ESP32-C3 Super Mini
- 7Star Digital Set-Top Box
- Soldering Iron
- Jumper Wire
- Double-sided Tape


## Wiring

ESP32 GPIO5  -> IR Receiver Output Line
ESP32 GND    -> STB Ground
ESP32 5V     -> STB USB 5V


## Installation

1. Flash the Arduino sketch.
2. Update Wi-Fi credentials.
3. Connect wiring.
4. Power the ESP32 from the STB USB port.
5. Open the ESP32 IP address in a browser.


## Android App

The Android app communicates with the ESP32 using HTTP requests over the local Wi-Fi network.
*Update the ESP32 IP address inside MainActivity.kt before building the APK.*





