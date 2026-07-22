# 🌤️ Project 6: Wi-Fi Weather Dashboard

<div align="center">

[![IIT Jammu Summer School 2026](https://img.shields.io/badge/IIT%20Jammu-Summer%20School%202026-blueviolet?style=for-the-badge&logo=education)](#)
[![Author](https://img.shields.io/badge/Author-Vraj%20Ramavat-orange?style=for-the-badge&logo=github)](https://github.com/Vraj-Ramavat)
[![Project](https://img.shields.io/badge/Project-P6-blue?style=for-the-badge)](#)
[![Platform](https://img.shields.io/badge/Platform-ESP32-teal?style=for-the-badge&logo=espressif)](#)
[![Status](https://img.shields.io/badge/Status-Completed-success?style=for-the-badge)](#)

</div>

## Components Used
- ESP32 Dev Board
- DHT22
- BMP280 (I2C)
- LDR + 10kΩ resistor
- OLED 0.96" — **SPI variant (SSD1306, 7-pin)** in place of kit sheet's I2C module

## ⚠️ Hardware Notes
- The BMP280 stays on I2C as documented (it only came in the I2C variant). Only the
  **display** moved from I2C to SPI, since the OLED in the kit is the 7-pin SPI SSD1306.
- Kit sheet lists DHT11; the sensor supplied is a **DHT22** (AM2302), so the sketch
  uses `DHTesp::DHT22`.

## Wiring Reference

| Component        | Pin       | ESP32 GPIO |
|-------------------|----------|------------|
| BMP280 VCC/GND    | —        | 3.3V / GND |
| BMP280 SDA/SCL    | I2C      | GPIO21 / GPIO22 (addr 0x76) |
| DHT22 DATA        | Data     | GPIO4 (10kΩ pull-up) |
| LDR divider       | Analog   | GPIO34 (3.3V → LDR → GPIO34 → 10kΩ → GND) |
| OLED D0 (SCK)     | Clock    | GPIO18 |
| OLED D1 (MOSI)    | Data     | GPIO23 |
| OLED RES          | Reset    | GPIO33 |
| OLED DC           | Data/Cmd | GPIO32 |
| OLED CS           | Chip Sel | GPIO5 |

## Libraries
`WiFi`, `ESPAsyncWebServer` (+ `AsyncTCP` dependency), `Adafruit_BMP280`, `DHTesp`, `Adafruit_SSD1306`, `Adafruit_GFX`

## Setup
1. Copy `config.h.example` → `config.h`, fill in your Wi-Fi SSID/password.
   `config.h` is in `.gitignore` — **never commit it**.
2. Wire per the table above.
3. Upload `p6_wifi_dashboard.ino`.
4. Open Serial Monitor at 115200 baud to see the assigned IP.

## Expected Output
- OLED shows SSID + IP on boot, then live sensor readings.
- Visiting `http://<esp32-ip>/` in a browser shows a live dashboard (auto-refresh 10s).
- `http://<esp32-ip>/data` returns JSON: `{temp, humidity, pressure, altitude, light}`.
- If Wi-Fi drops, the sketch retries every 30 seconds automatically.

## Bonus (Chart.js history)
Not implemented in this base version — the `/data` JSON endpoint is ready to be polled by a Chart.js script added to `buildHtmlPage()` for a trend graph.

## Demo Video
The demonstration video showing sensor readings, the live Wi-Fi web dashboard, and OLED output is available here:
- [Google Drive Demo Video](https://drive.google.com/file/d/1T4ZiVwI6QMQdbbKgNOEkscs-3Sj8QnoZ/view?usp=sharing)
- Located locally at: `demo video/video_link.txt`
