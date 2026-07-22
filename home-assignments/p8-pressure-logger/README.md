# Project 8: IoT Pressure & Altitude Logger

## Components Used
- ESP32 Dev Board
- BMP280 (I2C)
- OLED 0.96" — **SPI variant (SSD1306, 7-pin)** used instead of the kit sheet's I2C module
- Potentiometer 10kΩ
- Red + Green LEDs

## ⚠️ Hardware Note
BMP280 stays on I2C. Only the OLED moved to SPI, since the physical module in
the kit is the 7-pin SPI SSD1306, not the 4-pin I2C one the sheet describes.

## Wiring Reference

| Component        | Pin       | ESP32 GPIO |
|-------------------|----------|------------|
| BMP280 VCC/GND    | —        | 3.3V / GND (never 5V) |
| BMP280 SDA/SCL    | I2C      | GPIO21 / GPIO22 |
| Potentiometer     | outer pins | 3.3V / GND |
| Potentiometer     | wiper    | GPIO34 |
| Green LED         | Anode    | GPIO25 → 220Ω → GND |
| Red LED           | Anode    | GPIO26 → 220Ω → GND |
| OLED D0 (SCK)     | Clock    | GPIO18 |
| OLED D1 (MOSI)    | Data     | GPIO23 |
| OLED RES          | Reset    | GPIO33 |
| OLED DC           | Data/Cmd | GPIO32 |
| OLED CS           | Chip Sel | GPIO5 |

## Libraries
`Adafruit_BMP280`, `Adafruit_SSD1306`, `Adafruit_GFX`

## How to Run
1. Run an I2C scanner sketch first to confirm the BMP280 address (0x76 or 0x77) — the
   sketch tries 0x76 first, falls back to 0x77.
2. Wire per the table.
3. Upload `p8_pressure_logger.ino`.
4. Open Serial Monitor at 115200 baud.

## Expected Output
- Serial prints pressure/temp/altitude/trend every 30 seconds.
- OLED alternates every 5s between: Page 1 (pressure/temp/altitude), Page 2 (trend arrow).
- Green LED = stable/rising, Red LED = falling.
- Potentiometer sets local altitude (0–2000m) used to compensate sea-level pressure.

## Sea-Level Pressure Formula
`P0 = P / (1 - altitude/44330)^5.255` — the barometric formula relates the pressure
measured at a known altitude to what it would read at sea level, so trend comparisons
stay meaningful regardless of where you are. The potentiometer stands in for a manual
"set my local altitude" control since GPS isn't in the kit.

## Bonus (MQTT to HiveMQ)
Not implemented in this base sketch — pressure/trend JSON can be published to `broker.hivemq.com` on topic `iitjammu/<yourname>/pressure` using `PubSubClient` as a follow-up.

## Demo Video
The demonstration video showing potentiometer baseline altitude configuration, OLED page toggling, and trend prediction is available here:
- [Google Drive Demo Video](https://drive.google.com/file/d/1mDGfASfnVX1Ro6ogJCD_d_MwIuqGKbg5/view?usp=sharing)
- Located locally at: `demo video/video_link.txt`
