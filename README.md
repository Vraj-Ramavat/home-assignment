# IIT Jammu Summer School 2026 — IoT & Drones Home Assignments

10 projects, code + wiring + README for each, ready to push under
`/home-assignments/<project-name>/` as required by the submission rules.

## ⚠️ Hardware Substitution Notes
**OLED (P1, P3, P4, P6, P8, P9, P10):** The kit sheet specifies a **4-pin I2C OLED (SSD1306)**, but the module actually
supplied is a **7-pin SPI OLED (GND, VCC, D0, D1, RES, DC, CS)**. Every sketch
that uses the OLED has been rewired and recoded for SPI instead of I2C — using
`Adafruit_SSD1306` with the SPI constructor and hardware SPI pins. If your kit
issues the 4-pin I2C version instead, swap the constructor to
`Adafruit_SSD1306(128,64,&Wire,-1)` and wire SDA/SCL per the original sheet.

**Temp/Humidity sensor (P1, P4, P6, P10):** The kit sheet specifies **DHT11**, but the sensor actually supplied is a
**DHT22 (AM2302)**. Same 3-wire hookup (VCC/DATA/GND) and same 10kΩ pull-up
requirement, but a different bit-timing protocol — all four sketches are set to
`DHTesp::DHT22`. If you're issued a real DHT11, switch that one constant back
per project.

## Folder Index
| Folder | Project |
|--------|---------|
| `p1-climate-monitor/` | Smart Room Climate Monitor (ESP32) |
| `p2-gas-fire-alert/` | Gas & Fire Safety Alert (Arduino Uno) |
| `p3-parking-sensor/` | Ultrasonic Parking Assistant (Arduino Uno) |
| `p4-plant-monitor/` | Smart Plant Watering Monitor (ESP32) |
| `p5-bt-light-control/` | Bluetooth Home Light Controller (ESP32) |
| `p6-wifi-dashboard/` | Wi-Fi Weather Dashboard (ESP32) |
| `p7-security-cam/` | Motion Security Camera (ESP32-CAM) |
| `p8-pressure-logger/` | Pressure & Altitude Logger (ESP32) |
| `p9-stepper-controller/` | Stepper Motor Positioner (Arduino Uno) |
| `p10-home-hub/` | Full Home Automation Hub — capstone (ESP32) |

## Before You Push
1. `git init` in this folder (or copy contents into your existing repo at `/home-assignments/`).
2. For P6/P7/P10: copy each `config.h.example` → `config.h` and fill in your own Wi-Fi
   credentials — `config.h` is already gitignored, don't remove that.
3. Make at least 3 commits per project you submit (`feat:`, `fix:`, `docs:`), per the program's submission rules.
4. Record your 60–90s demo video per project and link it (Google Drive) in that project's README.
5. Test each sketch standalone on the actual hardware before combining/pushing — the code
   here follows the assignment's logic closely but board revisions/library versions can shift pin behavior.

## Bonus Marks
Attempting all 10 (not just 5) earns up to 10 bonus marks — this repo includes code +
README for all 10, so you're covered either way.
