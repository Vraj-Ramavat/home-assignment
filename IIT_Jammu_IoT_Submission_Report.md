# IIT Jammu Summer School 2026 — IoT & Drones Home Assignments Submission Report

---

## 👤 Student Submission Details

* **Name**: [Please enter your name here]
* **Contact Number**: [Please enter your contact number here]
* **Email Address**: ramavatvraj@gmail.com
* **GitHub Repository Link**: [https://github.com/Vraj-Ramavat/home-assignment](https://github.com/Vraj-Ramavat/home-assignment)
* **Google Drive Demo Video Folder**: [Google Drive Folder containing all Project Videos](https://drive.google.com/drive/folders/11xXk5HcE5a5OeeX7RsooTPi0qlOb1i7U?usp=sharing)

---

## 📝 Submission Executive Summary

This report documents the design, hardware wiring configuration, code logic, and functional verification of **8 out of the 10 assignments** completed for the IIT Jammu Summer School 2026 IoT & Drones program. 

### Core Hardware Adaptations & Code Optimizations:
1. **SPI OLED Conversion**: Adapted all project drawings (P1, P3, P4, P6, P8, P9, P10) to operate over high-speed hardware SPI using the 7-pin SPI SSD1306 module supplied in the kit.
2. **DHT22 Protocol Integration**: Configured all climate-sensing projects to read using the DHT22 (AM2302) protocol to match the physical sensor.
3. **Buzzer State Transition Bugfixes**: Patented code fixes in P2 and P3 using static transition state variables, correcting a bug where continuous alarms from the "Danger" state droned on when switching to intermittent warning states.
4. **Hysteresis Auto-Resume logic**: Optimized P4 to continuously evaluate soil moisture thresholds during manual overrides, allowing it to transition to the correct state instantly when the override expires.
5. **Real-time OLED Updates**: Corrected target setting refresh logic on P9, allowing the target angle display to update in real-time when the potentiometer is rotated.
6. **OLED Startup & Zero Display Latency Fixes**: Programmed P8 and P10 to run initial sensor reads in `setup()` and skip startup page switch delays. This prevents initial 5-second black screens and zeroed parameters.

---

## 📂 Detailed Project Documentation

### 🛠️ Project 1: Smart Room Climate Monitor
* **Description**: A live climate station that monitors temperature and humidity on an OLED display, triggering a buzzer and a red LED alarm when temperature exceeds 38°C or humidity exceeds 80%.
* **Difficulty**: Beginner
* **Components Used**: ESP32 Dev Board, DHT22 Sensor, 7-pin SPI OLED, Active Buzzer, Red/Green LEDs, 220Ω resistors.
* **Wiring Table**:
  | Component | Component Pin | ESP32 GPIO Pin |
  | :--- | :--- | :--- |
  | **DHT22** | DATA | GPIO4 (with 10kΩ pull-up to 3.3V) |
  | **DHT22** | VCC / GND | 3.3V / GND |
  | **Red LED** | Anode | GPIO25 (through 220Ω) |
  | **Green LED**| Anode | GPIO26 (through 220Ω) |
  | **Buzzer** | Anode (+) | GPIO27 |
  | **SPI OLED** | D0 (CLK) / D1 (MOSI) | GPIO18 / GPIO23 (HW SPI) |
  | **SPI OLED** | RES / DC / CS | GPIO21 / GPIO2 / GPIO5 |
  | **SPI OLED** | VCC / GND | 3.3V / GND |
* **Expected Output**: OLED displays Temp, Hum, and Comfort Index (COOL/COMFORT/HOT/DANGER). Red LED & Buzzer trigger if thresholds are crossed; otherwise Green LED remains ON.
* **Demo Video Link**: [Project 1 Demo Video](https://drive.google.com/drive/folders/11xXk5HcE5a5OeeX7RsooTPi0qlOb1i7U?usp=sharing) (Located in the Main Drive Folder)

---

### 🛠️ Project 2: Gas & Fire Safety Alert System
* **Description**: A dual-sensor safety device utilizing an MQ-2 gas sensor and an infrared flame sensor. Features three alert levels: Safe (green LED), Warning (yellow LED + slow beep), and Danger (red LED + continuous alarm).
* **Difficulty**: Beginner
* **Components Used**: Arduino Uno R3, MQ-2 Gas Sensor, Flame Sensor, Active Buzzer, Red/Yellow/Green LEDs, 220Ω resistors.
* **Wiring Table**:
  | Component | Component Pin | Arduino Uno Pin |
  | :--- | :--- | :--- |
  | **MQ-2** | AOUT / VCC / GND | A0 / 5V / GND |
  | **Flame Sensor** | DO / AO / VCC / GND | D7 / A1 / 5V / GND |
  | **Green LED** | Anode | D10 (through 220Ω) |
  | **Yellow LED**| Anode | D11 (through 220Ω) |
  | **Red LED** | Anode | D12 (through 220Ω) |
  | **Buzzer** | Anode (+) | D9 (PWM) |
  | **Silence Button** | Signal | D8 (INPUT_PULLUP, other leg -> GND) |
* **Expected Output**: Green LED lights up when safe. Gas > 30% triggers yellow LED and 1 beep/sec. Gas > 60% or flame detected (active-low signal) triggers Red LED and continuous alarm. Pressing the Silence Button mutes the alarm for 30s.
* **Demo Video Link**: [Project 2 Demo Video on Google Drive](https://drive.google.com/file/d/1aXetJgAu9GgYf4GEAz94JnL8eWgjovdT/view?usp=sharing)

---

### 🛠️ Project 3: Ultrasonic Parking Assistant
* **Description**: Replicates a vehicle parking sensor system. As obstacles approach the HC-SR04 rangefinder, the OLED displays distance in cm, LED indicators transition, and the buzzer beep frequency scales dynamically.
* **Difficulty**: Beginner–Int.
* **Components Used**: Arduino Uno R3, HC-SR04 Ultrasonic Sensor, Active Buzzer, Red/Yellow/Green LEDs, 7-pin SPI OLED, 220Ω resistors.
* **Wiring Table**:
  | Component | Component Pin | Arduino Uno Pin |
  | :--- | :--- | :--- |
  | **HC-SR04** | TRIG / ECHO / VCC / GND | A2 / A3 / 5V / GND |
  | **Buzzer** | Anode (+) | D6 (PWM) |
  | **Green LED** | Anode | D2 (through 220Ω) |
  | **Yellow LED**| Anode | D3 (through 220Ω) |
  | **Red LED** | Anode | D4 (through 220Ω) |
  | **SPI OLED** | D0 (CLK) / D1 (MOSI) | D13 / D11 (HW SPI) |
  | **SPI OLED** | RES / DC / CS | D12 / D8 / D7 |
  | **SPI OLED** | VCC / GND | 5V (or 3.3V) / GND |
* **Expected Output**: OLED displays distance in large font + a proximity bar.
  * **>60cm**: Green LED ON, silent (SAFE).
  * **30-60cm**: Yellow LED ON, beep every 800ms (CAUTION).
  * **15-30cm**: Yellow + Red LEDs ON, beep every 300ms (CLOSE).
  * **<15cm**: Red LED ON, continuous beep (DANGER).
* **Demo Video Link**: [Project 3 Demo Video on Google Drive](https://drive.google.com/file/d/1i5nrpRfMtIrRix0Z7caPhr_TxXc5F2cz/view?usp=sharing)

---

### 🛠️ Project 4: Smart Plant Watering Monitor
* **Description**: Monitors plant health by reading capacitive soil moisture and ambient temperature. Automatically drives a relay load (simulated pump) using hysteresis and allows 5-second manual override watering.
* **Difficulty**: Intermediate
* **Components Used**: ESP32 Dev Board, Capacitive Soil Moisture Sensor, DHT22 Sensor, 2-Channel Relay Module, Red/Green LEDs, 7-pin SPI OLED, Push button, resistors.
* **Wiring Table**:
  | Component | Component Pin | ESP32 GPIO Pin |
  | :--- | :--- | :--- |
  | **Soil Sensor** | AOUT / VCC / GND | GPIO35 / 3.3V / GND |
  | **DHT22** | DATA / VCC / GND | GPIO4 (with 10kΩ pull-up) / 3.3V / GND |
  | **Relay Module** | DC+ (VCC) / DC- (GND) | 5V (Vin) / GND |
  | **Relay Module** | CH1 (IN1) / CH2 (IN2) | GPIO26 (active-LOW) / GPIO27 (Unused) |
  | **Push Button** | Signal | GPIO0 (INPUT_PULLUP) |
  | **SPI OLED** | D0 (CLK) / D1 (MOSI) | GPIO18 / GPIO23 (HW SPI) |
  | **SPI OLED** | RES / DC / CS | GPIO14 / GPIO27 / GPIO5 |
  | **SPI OLED** | VCC / GND | 3.3V / GND |
* **Expected Output**: OLED prints Soil %, Temperature, and status (DRY/OPTIMAL/WET) with a soil moisture bar graph. Pump triggers ON when soil < 30%, and only turns OFF when soil > 40%. Button forces pump ON for 5 seconds.
* **Demo Video Link**: [Project 4 Demo Video on Google Drive](https://drive.google.com/file/d/1lmV34iSDWoWjnpJLRm2e--SWh8PrlMBD/view?usp=sharing)

---

### 🛠️ Project 6: Wi-Fi Weather Dashboard
* **Description**: Hosts a local asynchronous web server on the ESP32 to serve a live HTML weather dashboard showing temperature, humidity, barometric pressure, altitude, and ambient light level.
* **Difficulty**: Intermediate–Adv.
* **Components Used**: ESP32 Dev Board, DHT22 Sensor, BMP280 Sensor (I2C), LDR, 7-pin SPI OLED, 10kΩ resistor.
* **Wiring Table**:
  | Component | Component Pin | ESP32 GPIO Pin |
  | :--- | :--- | :--- |
  | **BMP280** | SDA / SCL / VCC / GND | GPIO21 / GPIO22 / 3.3V / GND |
  | **DHT22** | DATA / VCC / GND | GPIO4 / 3.3V / GND |
  | **LDR** | Wiper (Voltage Divider) | GPIO34 (3.3V -> LDR -> GPIO34 -> 10kΩ -> GND) |
  | **SPI OLED** | D0 (CLK) / D1 (MOSI) | GPIO18 / GPIO23 (HW SPI) |
  | **SPI OLED** | RES / DC / CS | GPIO33 / GPIO32 / GPIO5 |
  | **SPI OLED** | VCC / GND | 3.3V / GND |
* **Expected Output**: OLED displays SSID and local IP address upon connection. Accessing `http://<ip>/` serves an HTML dashboard with auto-refresh every 10s. Background color changes (Blue = cool, Orange = hot). `/data` returns raw JSON.
* **Demo Video Link**: [Project 6 Demo Video on Google Drive](https://drive.google.com/file/d/1T4ZiVwI6QMQdbbKgNOEkscs-3Sj8QnoZ/view?usp=sharing)

---

### 🛠️ Project 8: IoT Pressure & Altitude Logger
* **Description**: Tracks atmospheric pressure trends over time. Saves a 24-point history of readings. Calculates rising/falling trends, and reads a potentiometer to set local altitude baseline for sea-level pressure compensation.
* **Difficulty**: Int.–Advanced
* **Components Used**: ESP32 Dev Board, BMP280 Sensor (I2C), 10kΩ Potentiometer, Red + Green LEDs, 7-pin SPI OLED.
* **Wiring Table**:
  | Component | Component Pin | ESP32 GPIO Pin |
  | :--- | :--- | :--- |
  | **BMP280** | SDA / SCL / VCC / GND | GPIO21 / GPIO22 / 3.3V / GND |
  | **Potentiometer** | Wiper / Outer Pins | GPIO34 / 3.3V & GND |
  | **Green LED** | Anode | GPIO25 (through 220Ω) |
  | **Red LED** | Anode | GPIO26 (through 220Ω) |
  | **SPI OLED** | D0 (CLK) / D1 (MOSI) | GPIO18 / GPIO23 (HW SPI) |
  | **SPI OLED** | RES / DC / CS | GPIO33 / GPIO32 / GPIO5 |
  | **SPI OLED** | VCC / GND | 3.3V / GND |
* **Expected Output**: OLED alternates every 5s between Page 1 (Pressure, Temp, Altitude) and Page 2 (Trend arrow). Green LED indicates stable/rising pressure; Red LED indicates falling pressure (rain warning).
* **Demo Video Link**: [Project 8 Demo Video on Google Drive](https://drive.google.com/file/d/1mDGfASfnVX1Ro6ogJCD_d_MwIuqGKbg5/view?usp=sharing)

---

### 🛠️ Project 9: Stepper Motor Precision Positioner
* **Description**: A precision motor control station where a potentiometer maps to target angles (0-360°), CW/CCW buttons step the motor exactly 45°, and a third button configures logical home.
* **Difficulty**: Advanced
* **Components Used**: Arduino Uno R3, 28BYJ-48 Stepper Motor, ULN2003 Driver Board, 10kΩ Potentiometer, 3 Push Buttons, 7-pin SPI OLED, 10kΩ pull-down resistors.
* **Wiring Table**:
  | Component | Component Pin | Arduino Uno Pin |
  | :--- | :--- | :--- |
  | **ULN2003** | IN1 / IN2 / IN3 / IN4 | D8 / D9 / D10 / D7 |
  | **Potentiometer** | Wiper / Outer Pins | A0 / 5V & GND |
  | **CW Button** | Signal | D2 (INPUT_PULLUP) |
  | **CCW Button**| Signal | D3 (INPUT_PULLUP) |
  | **Home Button**| Signal | D4 (INPUT_PULLUP) |
  | **SPI OLED** | D0 (CLK) / D1 (MOSI) | D13 / D11 (HW SPI) |
  | **SPI OLED** | RES / DC / CS | A1 / D6 / D5 |
  | **SPI OLED** | VCC / GND | 5V / GND |
* **Expected Output**: Potentiometer rotation changes "Target Angle" on OLED immediately. CW/CCW button clicks drive the stepper motor 512 steps (45°) in the respective direction. Home button sets current position as 0° (logical home).
* **Demo Video Link**: [Project 9 Demo Video on Google Drive](https://drive.google.com/file/d/1I_Rf7ZraENPMrwaVtghnoviXfk_Dg3WQ/view?usp=sharing)

---

### 🛠️ Project 10: Full IoT Home Automation Hub (Capstone)
* **Description**: A comprehensive smart home controller linking DHT22, MQ-2, PIR, and LDR sensors. Dynamically controls a fan relay (temp hysteresis) and a light relay (light threshold + motion trigger). Provides a local HTML server dashboard and publishes sensor payloads to HiveMQ MQTT broker.
* **Difficulty**: Capstone
* **Components Used**: ESP32 Dev Board, DHT22, MQ-2, PIR, LDR, 2-Channel Relay Module, Active Buzzer, Red/Green LEDs, 2 Buttons, 7-pin SPI OLED.
* **Wiring Table**:
  | Component | Component Pin | ESP32 GPIO Pin |
  | :--- | :--- | :--- |
  | **DHT22** | DATA / VCC / GND | GPIO4 (with 10kΩ pull-up) / 3.3V / GND |
  | **MQ-2** | AOUT / VCC / GND | GPIO35 / 5V / GND |
  | **PIR Sensor** | OUT / VCC / GND | GPIO13 / 5V / GND |
  | **LDR** | Wiper (Voltage Divider) | GPIO34 / 3.3V & GND |
  | **Relay Module** | DC+ (VCC) / DC- (GND) | 5V (Vin) / GND |
  | **Relay Module** | CH1 (Fan) / CH2 (Light) | GPIO26 / GPIO27 (active-LOW) |
  | **Buzzer** | Anode (+) | GPIO14 |
  | **Red LED** | Anode | GPIO25 (through 220Ω) |
  | **Green LED**| Anode | GPIO2 (System Status OK) |
  | **Fan Button**| Signal | GPIO0 (INPUT_PULLUP) |
  | **Light Button**| Signal | GPIO32 (INPUT_PULLUP) |
  | **SPI OLED** | D0 (CLK) / D1 (MOSI) | GPIO18 / GPIO23 (HW SPI) |
  | **SPI OLED** | RES / DC / CS | GPIO19 / GPIO21 / GPIO5 |
  | **SPI OLED** | VCC / GND | 3.3V / GND |
* **Expected Output**:
  * OLED cycles 3 pages (Temp/Hum -> Gas/PIR/Light -> Relay/Uptime).
  * Fan triggers ON above 32°C, OFF below 28°C.
  * Light triggers ON if light < 20% AND motion detected, OFF if light > 60% or no motion for 3 minutes.
  * Gas > 60% shuts down all relays, activates buzzer, and red LED.
  * Web dashboard shows live dashboard. MQTT publishes JSON payloads every 30s to `iitjammu/<username>/home`.
* **Demo Video Link**: [Project 10 Demo Video on Google Drive](https://drive.google.com/file/d/1LCE_cEdUZ_KnvtIQAJcFI2XYPHYNZcPI/view?usp=sharing)
