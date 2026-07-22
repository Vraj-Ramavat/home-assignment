# 🏆 Project 10: Full IoT Home Automation Hub (Capstone)

<div align="center">

[![IIT Jammu Summer School 2026](https://img.shields.io/badge/IIT%20Jammu-Summer%20School%202026-blueviolet?style=for-the-badge&logo=education)](#)
[![Author](https://img.shields.io/badge/Author-Vraj%20Ramavat-orange?style=for-the-badge&logo=github)](https://github.com/Vraj-Ramavat)
[![Project](https://img.shields.io/badge/Project-P10%20(Capstone)-blue?style=for-the-badge)](#)
[![Platform](https://img.shields.io/badge/Platform-ESP32-teal?style=for-the-badge&logo=espressif)](#)
[![Status](https://img.shields.io/badge/Status-Completed-success?style=for-the-badge)](#)

</div>

## Components Used
- ESP32 Dev Board
- DHT22, MQ-2, PIR HC-SR501, LDR
- 2-Channel Relay Module (Fan + Light)
- OLED 0.96" — **SPI variant (SSD1306, 7-pin)**, adapted from the kit sheet's I2C spec
- Buzzer, Red/Green LEDs, 2 push buttons

## ⚠️ Hardware Notes
- Kit sheet lists an I2C OLED; this build uses the actual 7-pin SPI SSD1306 module
  over hardware SPI (SCK=GPIO18, MOSI=GPIO23) — see table below.
- Kit sheet lists DHT11; the sensor supplied is a **DHT22** (AM2302), so the sketch
  uses `DHTesp::DHT22`.

## System Architecture (text diagram)
```
[DHT22] [MQ-2] [PIR] [LDR]  --5s poll-->  readSensors()
                                    |
                                    v
                          applyAutomationRules()
                          (gas safety > fan rule > light rule)
                                    |
                    -----------------------------------
                    |                |                |
              [Relay: Fan]    [Relay: Light]     [Buzzer/RedLED]
                    |                |                |
                    -----------------------------------
                                    |
                +-------------------+-------------------+
                |                                        |
      AsyncWebServer (port 80)                 MQTT publish (30s)
      / dashboard, /data JSON,                  broker.hivemq.com
      /fan/toggle, /light/toggle                topic: iitjammu/<you>/home
                                    |
                              OLED (3 pages, 5s cycle)
```

## Automation Rules
1. **Fan (Relay 1)**: AUTO ON if temp > 32°C, AUTO OFF if temp < 28°C (hysteresis). Manual button/web toggle overrides for 10 minutes.
2. **Light (Relay 2)**: AUTO ON if LDR < 20% AND PIR motion. AUTO OFF if LDR > 60% or no motion for 3 minutes. Manual override for 10 minutes.
3. **Gas safety**: if MQ-2 > 60%, buzzer + Red LED on, **both relays force OFF** regardless of manual override, and `alert:true` is published/shown immediately.

## Wiring Reference

| Component        | Pin       | ESP32 GPIO |
|-------------------|----------|------------|
| DHT22 DATA        | Data     | GPIO4 (10kΩ pull-up) |
| MQ-2 AOUT         | Analog   | GPIO35 |
| PIR OUT           | Digital  | GPIO13 |
| LDR divider       | Analog   | GPIO34 |
| Relay IN1 (Fan)   | Control  | GPIO26 (active-LOW) |
| Relay IN2 (Light) | Control  | GPIO27 (active-LOW) |
| Buzzer            | +        | GPIO14 |
| Red LED (gas)     | Anode    | GPIO25 → 220Ω → GND |
| Green LED (OK)    | Anode    | GPIO2 → 220Ω → GND |
| Fan override btn  | one leg  | GPIO0 (INPUT_PULLUP), other leg → GND |
| Light override btn| one leg  | GPIO32 (INPUT_PULLUP), other leg → GND |
| OLED D0 (SCK)     | Clock    | GPIO18 |
| OLED D1 (MOSI)    | Data     | GPIO23 |
| OLED RES          | Reset    | GPIO19 |
| OLED DC           | Data/Cmd | GPIO21 |
| OLED CS           | Chip Sel | GPIO5 |

## Libraries
`WiFi`, `ESPAsyncWebServer`, `PubSubClient` (MQTT), `DHTesp`, `Adafruit_SSD1306`, `Adafruit_GFX`

## Setup
1. Copy `config.h.example` → `config.h`; fill in Wi-Fi + a name for your MQTT topic (gitignored).
2. Wire per the table.
3. Upload `p10_home_hub.ino`.
4. Open Serial Monitor at 115200 for the assigned IP.

## Expected Output
- Web dashboard at `http://<ip>/` with live readings + Fan/Light toggle buttons.
- `/data` returns JSON: `{temp, humidity, gas, pir, light, fan, light_relay, alert}`.
- MQTT publishes the same JSON every 30s to `iitjammu/<yourname>/home` on `broker.hivemq.com` — verify with MQTT Explorer.
- OLED cycles 3 pages every 5s: Temp/Humidity → Gas/PIR/Light → Relay states/Uptime.
- Uptime shown as `Nd Nh Nm` on both OLED and dashboard.

## Bonus (Preferences persistence + factory reset)
Not implemented in this base sketch — the ESP32 `Preferences` library can persist
`fanManual`/`lightManual` state across reboot as a follow-up enhancement.

## Demo Video
The demonstration video showing all automation rules, manual overrides, the web dashboard, and MQTT topic messages is available here:
- [Google Drive Demo Video](https://drive.google.com/file/d/1LCE_cEdUZ_KnvtIQAJcFI2XYPHYNZcPI/view?usp=sharing)
- Located locally at: `demo video/video_link.txt`
