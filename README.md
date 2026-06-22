# ESP32 STB Wi-Fi Remote

Turn your Set-Top Box into a Wi-Fi controlled device using an ESP32-C3.

This project allows an ESP32 to directly inject remote control commands into the output line of the Set-Top Box's IR receiver. Unlike traditional IR blasters, no IR LED is required. Commands are transmitted directly to the STB's decoder circuitry, resulting in reliable operation over Wi-Fi.

The project was developed and tested on a 7Star Digital Set-Top Box but can be adapted to other Set-Top Boxes by capturing and replacing the remote timing arrays.

---

## Features

* Wi-Fi controlled Set-Top Box
* No IR LED required
* Direct IR receiver line injection
* ESP32-C3 compatible
* Lightweight web interface
* Android app support
* Power, OK, Navigation Buttons
* Number Keys 0-9
* Menu, Exit, Mute, Recall
* Easily adaptable to other Set-Top Boxes

---

## Hardware Required

* ESP32-C3 Super Mini
* Set-Top Box
* Soldering Iron
* Jumper Wires
* Double-Sided Tape
* Multimeter (recommended)

---

## How It Works

The ESP32 connects to the Set-Top Box's IR receiver output line.

When a button is pressed on the web interface or Android app:

1. ESP32 receives the HTTP request.
2. ESP32 replays the stored timing sequence.
3. The timing sequence is injected directly into the IR receiver output line.
4. The Set-Top Box interprets the command exactly as if it came from the original remote.

### Architecture

Phone / Android App
↓
Wi-Fi
↓
ESP32-C3
↓
IR Receiver Output Line
↓
Set-Top Box

---

## Wiring

### Example Wiring

ESP32 GPIO5 -> IR Receiver Output

ESP32 GND -> STB Ground

ESP32 5V -> STB USB 5V

### Important

Powering the ESP32 directly from the STB's 3.3V rail may not provide enough current for Wi-Fi operation.

Powering from the STB USB 5V rail is recommended.

---

## Installation

### 1. Upload Firmware

Open the Arduino sketch and update:

```cpp
const char* ssid = "YOUR_WIFI_NAME";
const char* password = "YOUR_WIFI_PASSWORD";
```

Upload the sketch to the ESP32-C3.

### 2. Connect Hardware

Connect:

* GPIO5 to IR receiver output
* GND to STB ground
* 5V to STB USB 5V

### 3. Power On

Power the Set-Top Box.

Open Serial Monitor and note the ESP32 IP address.

### 4. Open Web Interface

Visit:

```text
http://ESP32_IP_ADDRESS
```

Example:

```text
http://192.168.1.103
```

---

## Android Application

The Android application communicates with the ESP32 using HTTP requests over the local Wi-Fi network.

Update the ESP32 IP address before building the APK.

---

## Supported Buttons

### Navigation

* Up
* Down
* Left
* Right
* OK

### System

* Power
* Menu
* Exit
* Mute
* Recall

### Number Keys

* 0
* 1
* 2
* 3
* 4
* 5
* 6
* 7
* 8
* 9

---

## Adapting To Other Set-Top Boxes

This project can be adapted to other Set-Top Boxes.

### Step 1 - Upload Decoder Firmware

Upload the decoder sketch.

Connect:

```text
GPIO4 -> IR Receiver Output
GND   -> STB Ground
```

### Step 2 - Capture Signals

Press each button on the original remote and record:

* Protocol
* Hex Code
* Raw Timing Array

### Step 3 - Replace Timing Arrays

Replace the timing arrays in the transmitter firmware.

### Step 4 - Upload Updated Firmware

Flash the modified transmitter sketch.

The Android application and web interface generally do not require modifications.

---

## Repository Structure

```text
Arduino/
├── Decoder/
│   └── Decoder.ino
│
├── Transmitter/
│   └── STB_Remote.ino
│
├── Timing_Examples/
│   └── 7Star_Remote_Codes.txt
│
Android/
├── Source_Code/
└── APK/
│
Images/
├── Wiring.jpg
├── ESP32_Inside_STB.jpg
├── Android_App.png
└── Web_Interface.png
```

---

## Future Improvements

* Voice Control
* Tailscale Remote Access
* Home Assistant Integration
* Channel Selection API
* Volume Level API
* Additional STB Profiles

---

## Tested Hardware

### Microcontroller

* ESP32-C3 Super Mini

### Set-Top Box

* 7Star Digital Set-Top Box

---

## Disclaimer

This project requires soldering and modification of Set-Top Box hardware.

Proceed carefully and at your own risk.

Always verify voltages using a multimeter before connecting power to the ESP32.

---

## License

MIT License

Feel free to modify, improve and redistribute the project.
