# 🚨 Project 2: Gas & Fire Safety Alert System

<div align="center">

[![IIT Jammu Summer School 2026](https://img.shields.io/badge/IIT%20Jammu-Summer%20School%202026-blueviolet?style=for-the-badge&logo=education)](#)
[![Author](https://img.shields.io/badge/Author-Vraj%20Ramavat-orange?style=for-the-badge&logo=github)](https://github.com/Vraj-Ramavat)
[![Project](https://img.shields.io/badge/Project-P2-blue?style=for-the-badge)](#)
[![Platform](https://img.shields.io/badge/Platform-Arduino%20Uno-teal?style=for-the-badge&logo=arduino)](#)
[![Status](https://img.shields.io/badge/Status-Completed-success?style=for-the-badge)](#)

</div>

## Components Used
- Arduino Uno R3
- MQ-2 Gas Sensor
- Flame Sensor
- Active Buzzer
- Red, Yellow, Green LEDs + 220Ω resistors
- Push button (bonus: silence)

## Wiring Reference

| Component        | Pin              | Arduino Pin |
|-------------------|-----------------|-------------|
| MQ-2 VCC/GND      | —                | 5V / GND |
| MQ-2 AOUT         | Analog           | A0 |
| Flame Sensor VCC/GND | —             | 5V / GND |
| Flame Sensor DO   | Digital           | D7 |
| Flame Sensor AO   | Analog (optional) | A1 |
| Green LED         | Anode             | D10 → 220Ω → GND |
| Yellow LED        | Anode             | D11 → 220Ω → GND |
| Red LED           | Anode             | D12 → 220Ω → GND |
| Buzzer            | +                 | D9 (PWM) |
| Silence Button    | one leg           | D8 (INPUT_PULLUP), other leg → GND |

## Libraries
None beyond Arduino core (`tone()` used for buzzer patterns).

## How to Run
1. Wire per the table. Power on and **wait ~2 minutes** for the MQ-2 heater to stabilize.
2. Upload `p2_gas_fire_alert.ino` to Arduino Uno.
3. Open Serial Monitor at 115200 baud.

## Expected Output
- Serial prints `GAS: xx% | FLAME: NONE/DETECTED | STATUS: SAFE/WARNING/DANGER` every second.
- Green/Yellow/Red LEDs switch with state; buzzer beeps once/sec in WARNING, continuous in DANGER.
- Flame sensor is **active-low**: digital output goes LOW when flame/IR light is detected, because the sensor's phototransistor pulls the line down at its threshold — that's why the code checks `== LOW`.

## Bonus Implemented
Silence button mutes the buzzer for 30s while keeping LEDs active; alarm auto-resumes if danger persists after the mute window.

## Demo Video
The demonstration video showing LED color changes, buzzer patterns, and sensor thresholds is available here:
- [Google Drive Demo Video](https://drive.google.com/file/d/1aXetJgAu9GgYf4GEAz94JnL8eWgjovdT/view?usp=sharing)
- Located locally at: `demo video/video_link.txt`
