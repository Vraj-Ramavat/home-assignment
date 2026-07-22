# Project 4: Smart Plant Watering Monitor

## Components Used
- ESP32 Dev Board
- Capacitive Soil Moisture Sensor
- DHT22
- 2-Channel Relay Module
- OLED 0.96" — **SPI variant (SSD1306, 7-pin)**, adapted from the kit sheet's I2C spec
- Push button (manual override)

## ⚠️ Hardware Notes
- Kit sheet lists an I2C OLED. This build uses the actual 7-pin SPI SSD1306 module,
  wired over hardware SPI (SCK=GPIO18, MOSI=GPIO23).
- Kit sheet lists DHT11; the sensor actually supplied is a **DHT22** (AM2302) —
  same 3-wire hookup, but the sketch is set to `DHTesp::DHT22` to match its
  bit-timing protocol.

## Wiring Reference

| Component        | Pin       | ESP32 GPIO |
|-------------------|----------|------------|
| Soil sensor VCC/GND | —      | 3.3V / GND (never 5V) |
| Soil sensor AOUT  | Analog   | GPIO35 |
| DHT22 DATA        | Data     | GPIO4 (10kΩ pull-up to 3.3V) |
| Relay DC+ (VCC)   | Power    | 5V (Vin) |
| Relay DC- (GND)   | Ground   | GND |
| Relay CH1 (IN1)   | Control  | GPIO26 (active-LOW) |
| Relay CH2 (IN2)   | Control  | GPIO27 (Unused in P4) |
| Push button       | one leg  | GPIO0 (INPUT_PULLUP), other leg → GND |
| OLED D0 (SCK)     | Clock    | GPIO18 |
| OLED D1 (MOSI)    | Data     | GPIO23 |
| OLED RES          | Reset    | GPIO14 |
| OLED DC           | Data/Cmd | GPIO27 |
| OLED CS           | Chip Sel | GPIO5 |

## Libraries
`DHTesp`, `Adafruit_SSD1306`, `Adafruit_GFX`

## Calibration
Before use, log raw `analogRead(34)` values with the sensor in dry air and fully
submerged in water, then update `DRY_RAW` / `WET_RAW` at the top of the sketch.
Values used here (3200 dry / 1200 wet) are placeholders — **replace with your
own measured values** and note them in your submission.

## How to Run
1. Wire per the table, calibrate the sensor.
2. Upload `p4_plant_monitor.ino` (ESP32 Dev Module).
3. Open Serial Monitor at 115200 baud.

## Expected Output
- OLED shows Soil %, Temp, Status + moisture bar graph.
- Relay (pump) turns ON below 30% moisture, OFF above 40% (hysteresis prevents rapid switching).
- Manual button forces 5s of watering, then resumes auto mode.

## Bonus (Wi-Fi + ThingSpeak)
Not implemented in this base sketch — left as an extension once Wi-Fi credentials are added via a `config.h` (gitignored).

## Demo Video
The demonstration video showing sensor readings, OLED updates, and automatic/manual relay triggering is available here:
- [Google Drive Demo Video](https://drive.google.com/file/d/1lmV34iSDWoWjnpJLRm2e--SWh8PrlMBD/view?usp=sharing)
- Located locally at: `demo video/video_link.txt`
