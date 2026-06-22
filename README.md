ESP32 STB Wi-Fi Remote

Turn your Set-Top Box into a Wi-Fi controlled device using an ESP32-C3.

This project allows an ESP32 to directly inject remote control commands into the output line of the Set-Top Box's IR receiver. Unlike traditional IR blasters, no IR LED is required. Commands are transmitted directly to the STB's decoder circuitry, resulting in reliable operation over Wi-Fi.

The project was developed and tested on a 7Star Digital Set-Top Box but can be adapted to other Set-Top Boxes by capturing and replacing the remote timing arrays.

Features
Wi-Fi controlled Set-Top Box
No IR LED required
Direct IR receiver line injection
ESP32-C3 compatible
Lightweight web interface
Android app support
Supports Power, OK, Navigation, Number Keys and Menu functions
Easily adaptable to other Set-Top Boxes
Hardware Required
ESP32-C3 Super Mini
Set-Top Box
Soldering Iron
Jumper Wires
Double-Sided Tape (for mounting)
Multimeter (recommended)
How It Works

The ESP32 connects to the Set-Top Box's IR receiver output line.

When a button is pressed on the web interface or Android app:

ESP32 receives the HTTP request.
ESP32 replays the stored timing sequence.
The timing sequence is injected directly into the IR receiver output line.
The Set-Top Box interprets the command exactly as if it came from the original remote.

Architecture:

Phone / Android App
↓
Wi-Fi
↓
ESP32-C3
↓
IR Receiver Output Line
↓
Set-Top Box

Wiring

Example wiring used during development:

ESP32 GPIO5 -> IR Receiver Output

ESP32 GND -> STB Ground

ESP32 5V -> STB USB 5V

Important:

Powering the ESP32 directly from the STB's 3.3V rail may not provide enough current for Wi-Fi operation.

It is recommended to power the ESP32 from a stable 5V source such as the STB USB port.

Installation
1. Upload Firmware

Open the Arduino sketch and update:

const char* ssid = "YOUR_WIFI_NAME";
const char* password = "YOUR_WIFI_PASSWORD";

Upload the sketch to the ESP32-C3.

2. Connect Hardware

Connect:

GPIO5 to IR receiver output
GND to STB ground
5V to STB USB 5V
3. Power On

Power the Set-Top Box.

Open Serial Monitor and note the ESP32 IP address.

4. Open Web Interface

Visit:

http://ESP32_IP_ADDRESS

Example:

http://192.168.1.103

The remote control page should appear.

Android App

An Android application is included for easier control.

Update the ESP32 IP address inside the application source code before building:

http://192.168.1.xxx

Build and install the APK.

The app communicates with the ESP32 using simple HTTP requests over the local Wi-Fi network.

Supported Buttons

Current implementation includes:

Power
OK
Up
Down
Left
Right
Mute
Recall
Menu
Exit
Number Keys 0-9

Additional buttons can easily be added.

Adapting To Other Set-Top Boxes

This project is not limited to 7Star STBs.

To adapt it to another model:

Step 1 - Upload Decoder Firmware

Upload the decoder sketch.

Connect:

GPIO4 -> IR Receiver Output

GND -> STB Ground

Step 2 - Capture Signals

Press each button on the original remote and record:

Protocol
Hex Code
Raw Timing Array
Step 3 - Replace Timing Arrays

Replace the timing arrays in the transmitter firmware with the newly captured values.

Step 4 - Upload Updated Firmware

Flash the modified transmitter sketch.

The web interface and Android application can remain unchanged.

Repository Structure

Arduino/
├── Decoder/
│ └── Decoder.ino
│
├── Transmitter/
│ └── STB_Remote.ino
│
├── Timing_Examples/
│ └── 7Star_Remote_Codes.txt
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

Future Improvements
Voice Control
Tailscale Remote Access
Home Assistant Integration
Channel Selection API
Volume Level API
Support for Additional STB Models
Disclaimer

This project requires soldering and modification of Set-Top Box hardware.

Proceed carefully and at your own risk.

Always verify voltages with a multimeter before connecting power to the ESP32.

Tested Hardware
ESP32-C3 Super Mini
7Star Digital Set-Top Box

Additional hardware compatibility reports are welcome.

License

MIT License

Feel free to modify, improve, and share the project.
