# ⚙️ Project 9: Stepper Motor Precision Positioner

<div align="center">

[![IIT Jammu Summer School 2026](https://img.shields.io/badge/IIT%20Jammu-Summer%20School%202026-blueviolet?style=for-the-badge&logo=education)](#)
[![Author](https://img.shields.io/badge/Author-Vraj%20Ramavat-orange?style=for-the-badge&logo=github)](https://github.com/Vraj-Ramavat)
[![Project](https://img.shields.io/badge/Project-P9-blue?style=for-the-badge)](#)
[![Platform](https://img.shields.io/badge/Platform-Arduino%20Uno-teal?style=for-the-badge&logo=arduino)](#)
[![Status](https://img.shields.io/badge/Status-Completed-success?style=for-the-badge)](#)

</div>

## Components Used
- Arduino Uno R3
- Stepper Motor 28BYJ-48 + ULN2003 Driver
- Potentiometer 10kΩ
- Push Buttons ×3 (CW, CCW, Home)
- OLED 0.96" — **SPI variant (SSD1306, 7-pin)**, adapted from the kit sheet's I2C spec

## ⚠️ Hardware Note & Pin Reassignment
The kit's OLED is the 7-pin SPI SSD1306, not the I2C module in the sheet. Since
hardware SPI on the Uno fixes **SCK=D13** and **MOSI=D11**, the stepper driver
pins from the original sheet (8, 9, 10, 11) had to shift off D11. This build uses
**IN1=D8, IN2=D9, IN3=D10, IN4=D7** (same IN1‑IN3‑IN2‑IN4 wiring order the
Stepper library expects) so the OLED's SPI lines stay conflict-free.

## Wiring Reference

| Component        | Pin        | Arduino Pin |
|-------------------|-----------|-------------|
| ULN2003 VCC/GND   | —         | 5V / GND |
| ULN2003 IN1       | Control   | D8 |
| ULN2003 IN2       | Control   | D9 |
| ULN2003 IN3       | Control   | D10 |
| ULN2003 IN4       | Control   | D7 |
| Potentiometer     | outer pins| 5V / GND |
| Potentiometer     | wiper     | A0 |
| CW button         | one leg   | D2 (INPUT_PULLUP), other leg → GND |
| CCW button        | one leg   | D3 (INPUT_PULLUP), other leg → GND |
| Home button        | one leg  | D4 (INPUT_PULLUP), other leg → GND |
| OLED D0 (SCK)     | Clock     | D13 (HW SPI) |
| OLED D1 (MOSI)    | Data      | D11 (HW SPI) |
| OLED RES          | Reset     | A1 |
| OLED DC           | Data/Cmd  | D6 |
| OLED CS           | Chip Sel  | D5 |

## Libraries
`Stepper` (Arduino core), `Adafruit_SSD1306`, `Adafruit_GFX`

## How to Run
1. Wire per the table — **note the IN4 pin is D7, not D11** as in the original sheet.
2. Upload `p9_stepper_controller.ino`.
3. Open Serial Monitor at 115200 baud.

## Expected Output
- Potentiometer sets the target angle (0–360°) shown on OLED.
- CW/CCW buttons rotate the motor 45° per press; Home button zeroes the logical position (no movement).
- OLED shows: `Current: x° | Target: y° | Dir: CW/CCW | Steps: n`.

## 28BYJ-48 Notes
The motor has a 1:64 gear reduction, so **4096 half-steps = 1 full output-shaft
revolution** (2048 steps in this sketch's step count corresponds to the library's
internal full-step counting — the gearing is what gives the fine 360°/4096 ≈ 0.088°
resolution per half-step, far finer than the motor's own 32 steps/rev before gearing).
Do not exceed ~15 RPM or it will skip steps under load.

## Bonus (Acceleration ramp, +2 marks)
Not implemented in this base version — a soft-start/soft-stop ramp (5→15 RPM over the first/last 20 steps) can be added by varying `setSpeed()` between `step()` calls.

## Demo Video
The demonstration video showing potentiometer target adjustment, buttons moving the stepper motor, and real-time OLED updates is available here:
- [Google Drive Demo Video](https://drive.google.com/file/d/1I_Rf7ZraENPMrwaVtghnoviXfk_Dg3WQ/view?usp=sharing)
- Located locally at: `demo video/video_link.txt`
