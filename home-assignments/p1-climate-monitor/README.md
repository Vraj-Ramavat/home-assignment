# Project 1: Smart Room Climate Monitor

## Components Used
- ESP32 Dev Board
- DHT22 Temperature & Humidity Sensor
- OLED 0.96" — **SPI variant (SSD1306, 7-pin)**, not the I2C module listed in the kit sheet
- Active Buzzer
- Red LED + Green LED + 220Ω resistors

## ⚠️ Hardware Notes
- **OLED**: kit sheet specifies an I2C OLED (4-pin: GND/VCC/SDA/SCL). The module actually
  supplied is the **7-pin SPI SSD1306** (GND, VCC, D0, D1, RES, DC, CS). This build
  uses `Adafruit_SSD1306` in SPI mode instead of I2C. If you're issued the 4-pin
  I2C version, swap the constructor to `Adafruit_SSD1306(128,64,&Wire,-1)` and wire
  SDA→GPIO21, SCL→GPIO22 instead.
- **Temp/Humidity sensor**: kit sheet specifies DHT11, but the sensor actually
  supplied is a **DHT22** (also called AM2302) — same 3 wires (VCC/DATA/GND) and
  same 10kΩ pull-up requirement, but a different bit-timing protocol. The sketch
  is set to `DHTesp::DHT22` accordingly; if you're issued a real DHT11, switch
  that one constant back.

## Wiring Reference

| Component        | Pin        | ESP32 GPIO |
|-------------------|-----------|------------|
| DHT22 DATA        | Data      | GPIO4 (10kΩ pull-up to 3.3V) |
| DHT22 VCC/GND     | —         | 3.3V / GND |
| OLED VCC/GND      | —         | 3.3V / GND (never 5V) |
| OLED D0 (SCK)     | Clock     | GPIO18 (HW SPI) |
| OLED D1 (MOSI)    | Data      | GPIO23 (HW SPI) |
| OLED RES          | Reset     | GPIO21 |
| OLED DC           | Data/Cmd  | GPIO2 |
| OLED CS           | Chip Sel  | GPIO5 |
| Red LED           | Anode     | GPIO25 → 220Ω → LED → GND |
| Green LED         | Anode     | GPIO26 → 220Ω → LED → GND |
| Buzzer            | +         | GPIO27 → GND |

## Libraries
- `DHTesp` (by beegee-tokyo)
- `Adafruit_SSD1306` + `Adafruit_GFX` (SPI mode)

## How to Run
1. Install libraries above via Arduino Library Manager.
2. Wire per the table.
3. Select board: ESP32 Dev Module, upload `p1_climate_monitor.ino`.
4. Open Serial Monitor at 115200 baud.

## Expected Output
- OLED shows live Temp/Hum + comfort status, alternating with daily max/min every 5s.
- Serial Monitor prints CSV: `millis,temp,humidity,status` every 5 seconds.
- Buzzer + Red LED trigger above 38°C or 80% humidity; Green LED otherwise.

## Bonus Implemented
Daily max/min tracker using `millis()`, shown on OLED on a rotating page.

## Demo Video
The demo video link for this project is:
- [Google Docs Demo Video Link](https://docs.google.com/document/d/16FluyBkVb70zNfUl3FhwSKrU-X1en0yS2nnmOrMLoH4/edit?usp=sharing)

