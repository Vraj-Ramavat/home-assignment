# Project 3: Ultrasonic Parking Assistant

## Components Used
- Arduino Uno R3
- HC-SR04 Ultrasonic Sensor
- Active Buzzer
- Red, Yellow, Green LEDs
- OLED 0.96" — **SPI variant (SSD1306, 7-pin)** used instead of the kit sheet's I2C module

## ⚠️ Hardware Note
Kit sheet lists an I2C OLED (SDA→A4, SCL→A5). The module supplied is the 7-pin
SPI SSD1306, so this build wires it over hardware SPI instead (SCK=D13, MOSI=D11
on Uno, fixed by hardware).

## Wiring Reference

| Component      | Pin      | Arduino Pin |
|-----------------|---------|-------------|
| HC-SR04 VCC/GND | —       | 5V / GND |
| HC-SR04 TRIG    | Trigger | A2 |
| HC-SR04 ECHO    | Echo    | A3 |
| Buzzer          | +       | D6 (PWM, `tone()`) |
| Green LED       | Anode   | D2 → 220Ω → GND |
| Yellow LED      | Anode   | D3 → 220Ω → GND |
| Red LED         | Anode   | D4 → 220Ω → GND |
| OLED VCC/GND    | —       | 5V or 3.3V per module / GND |
| OLED D0 (SCK)   | Clock   | D13 (HW SPI) |
| OLED D1 (MOSI)  | Data    | D11 (HW SPI) |
| OLED RES        | Reset   | D12 |
| OLED DC         | Data/Cmd| D8 |
| OLED CS         | Chip Sel| D7 |

## Libraries
`Adafruit_SSD1306`, `Adafruit_GFX` (SPI mode)

## How to Run
1. Wire per the table.
2. Upload `p3_parking_sensor.ino`.
3. Open Serial Monitor at 115200 baud.

## Expected Output
- OLED shows live distance in cm (large font) + a proximity bar graph.
- 4 zones: SAFE (>60cm, green, silent), CAUTION (30–60cm, yellow, slow beep), CLOSE
  (15–30cm, yellow+red, fast beep), DANGER (<15cm, red, continuous tone).
- Serial Monitor logs distance + zone every 500ms.

## Physics Note
`distance = pulseIn(ECHO, HIGH) * 0.034 / 2` — the sensor emits a 40kHz ultrasonic burst;
ECHO stays HIGH for the round-trip time. Speed of sound ≈ 0.034 cm/µs, and dividing by 2
accounts for the sound traveling to the object and back.

## Bonus Challenge (not implemented)
Dual HC-SR04 (front + back) with non-blocking parallel timing — left as a future extension.

## Demo Video
The demonstration video showing distance measurements, zone transitions, and OLED readout is available here:
- [Google Drive Demo Video](https://drive.google.com/file/d/1i5nrpRfMtIrRix0Z7caPhr_TxXc5F2cz/view?usp=sharing)
- Located locally at: `demo video/video_link.txt`
