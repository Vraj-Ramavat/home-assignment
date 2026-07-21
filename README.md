# IIT Jammu Summer School 2026 — IoT & Drones Home Assignments submission

This repository contains the completed home assignments submission for the **IIT Jammu Summer School 2026 (IoT & Drones Program)**. Out of the 10 assignments, **8 projects** (including the advanced Capstone Hub) have been successfully built, optimized, documented, and submitted.

---

## 📂 Submitted Projects Index

All project folders are organized under the `/home-assignments/` directory structure with complete source code, circuit schematics/wiring tables, execution guides, and demonstration video links.

| Project | Folder Path | Difficulty | Description | Core Components Used |
| :--- | :--- | :--- | :--- | :--- |
| **Project 1** | [`/home-assignments/p1-climate-monitor`](file:///h:/iit-jammu-home-assignments%20(1)/p1-climate-monitor) | Beginner | **Smart Room Climate Monitor**: Reads Temp/Humidity and triggers a buzzer/red LED alert when safety thresholds are breached. | ESP32, DHT22, SPI OLED, Buzzer, LEDs |
| **Project 2** | [`/home-assignments/p2-gas-fire-alert`](file:///h:/iit-jammu-home-assignments%20(1)/p2-gas-fire-alert) | Beginner | **Gas & Fire Safety Alert System**: Combines MQ-2 gas readings and flame sensor active-low inputs with warning/danger alarm patterns. | Arduino Uno, MQ-2, Flame Sensor, Buzzer, LEDs |
| **Project 3** | [`/home-assignments/p3-parking-sensor`](file:///h:/iit-jammu-home-assignments%20(1)/p3-parking-sensor) | Beginner–Int. | **Ultrasonic Parking Assistant**: Measures distance using HC-SR04, showing proximity on OLED and scaling buzzer beep frequency. | Arduino Uno, HC-SR04, SPI OLED, Buzzer, LEDs |
| **Project 4** | [`/home-assignments/p4-plant-monitor`](file:///h:/iit-jammu-home-assignments%20(1)/p4-plant-monitor) | Intermediate | **Smart Plant Watering Monitor**: Polls soil moisture, controls a pump relay using hysteresis logic, and handles manual button overrides. | ESP32, Soil Sensor, DHT22, Relay, SPI OLED, Button |
| **Project 6** | [`/home-assignments/p6-wifi-dashboard`](file:///h:/iit-jammu-home-assignments%20(1)/p6-wifi-dashboard) | Intermediate–Adv. | **Wi-Fi Weather Dashboard**: Hosts an AsyncWebServer on the ESP32 to serve a live HTML/JSON dashboard showing weather/light data. | ESP32, DHT22, BMP280, LDR, SPI OLED |
| **Project 8** | [`/home-assignments/p8-pressure-logger`](file:///h:/iit-jammu-home-assignments%20(1)/p8-pressure-logger) | Int.–Advanced | **IoT Pressure & Altitude Logger**: Compensates sea-level pressure using a potentiometer for altitude and logs a 24-point circular buffer. | ESP32, BMP280, Potentiometer, SPI OLED, LEDs |
| **Project 9** | [`/home-assignments/p9-stepper-controller`](file:///h:/iit-jammu-home-assignments%20(1)/p9-stepper-controller) | Advanced | **Stepper Motor Precision Positioner**: Controls a 28BYJ-48 stepper motor using CW/CCW buttons and tracks logical home in real-time. | Arduino Uno, Stepper + ULN2003, Potentiometer, Buttons, OLED |
| **Project 10** | [`/home-assignments/p10-home-hub`](file:///h:/iit-jammu-home-assignments%20(1)/p10-home-hub) | Capstone | **Full IoT Home Automation Hub**: Integrative smart hub handling multiple sensors, auto-relays, WiFi server, and MQTT publishing. | ESP32, DHT22, MQ-2, PIR, LDR, 2-Ch Relay, Buzzer, OLED |

*Note: Project 5 (Bluetooth Light Controller) and Project 7 (Motion Security Camera) were omitted to focus development on the remaining 8 core and capstone modules.*

---

## 🛠️ Summary of Components Utilized

Across the implemented projects, the following hardware components from the kit have been successfully integrated:

1. **Microcontrollers**:
   * **ESP32 Dev Board** (38-pin variant)
   * **Arduino Uno R3**
2. **Sensors**:
   * **DHT22 (AM2302)** (Temperature & Humidity)
   * **BMP280** (Barometric Pressure & Altitude)
   * **MQ-2** (Gas / Smoke detector)
   * **Flame Sensor** (Infrared phototransistor - active-low configuration)
   * **HC-SR04** (Ultrasonic rangefinder)
   * **PIR HC-SR501** (Motion sensor)
   * **LDR** (Light Dependent Resistor in voltage divider setup)
   * **Potentiometer (10kΩ)** (Analog altitude & target configuration input)
3. **Actuators & Displays**:
   * **7-pin SPI OLED (SSD1306, 128x64)** (Display outputs)
   * **2-Channel Relay Modules** (Active-low configuration for loads/pumps)
   * **Active Buzzers & LEDs** (Acoustic and optical indicators)
   * **Stepper Motor 28BYJ-48 + ULN2003 Driver Board**
   * **Push Buttons** (Manual overrides and digital command buttons)

---

## ⚙️ Key Technical Implementations & Code Optimizations

* **SPI OLED Adaptation**: The kit sheet originally specified a 4-pin I2C OLED display, but the supplied physical module was a 7-pin SPI variant. All OLED-enabled projects (P1, P3, P4, P6, P8, P9, P10) have been successfully rewired and configured using hardware SPI constructors (`&SPI`) and dedicated clock/data/control pin assignments to ensure fast, low-latency drawing.
* **DHT22 Protocol Configuration**: The sketches have been updated to utilize `DHTesp::DHT22` timing to match the AM2302 sensor supplied in the physical kit.
* **Buzzer Transition Safety**: Code fixes were implemented in P2 and P3 using state transition tracking to guarantee that continuous alarms are stopped immediately when changing states, preventing buzzer hang-ups.
* **Hysteresis Auto-Resume**: Improved the plant monitor (P4) auto-logic to continue tracking soil moisture during manual overrides, allowing it to resume the proper state instantly when the override timer expires.
* **Real-time OLED Updates**: Fixed target setting display refresh on Project 9, enabling instant OLED updates when the potentiometer is turned.
* **OLED & Boot Zero-Latency**: Optimized Projects 8 and 10 to fetch sensor readings in `setup()` and draw the home pages immediately, preventing black screens and zeroed parameters during the initial startup cycles.

---

## 📝 Submission Guidelines Followed

* **README Documents**: Each directory contains a dedicated README file illustrating components used, pin connections, installation guides, library dependencies, and expected outcomes.
* **Demo Videos**: Every project includes a `demo video/` folder containing a direct Google Drive link file (`video_link.txt` and a helper Markdown file) showing the features in action.
* **Descriptive Commit History**: Pushed commits follow standard prefix protocols (`feat:`, `docs:`, `fix:`) with a minimum of 3 commits per project.
* **Clean Repo Structure**: Pushed under the `/home-assignments/` path to match the course requirement.
