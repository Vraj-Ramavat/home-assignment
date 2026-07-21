/*
  Project 8: IoT Pressure & Altitude Logger
  Board: ESP32 Dev Board
  NOTE: OLED is the kit's actual 7-pin SPI SSD1306 (not I2C). BMP280 stays on I2C.
*/

#include <Wire.h>
#include <Adafruit_BMP280.h>
#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define POT_PIN    34
#define GREEN_LED  25
#define RED_LED    26

#define OLED_CS    5
#define OLED_DC    32
#define OLED_RESET 33
Adafruit_SSD1306 display(128, 64, &SPI, OLED_DC, OLED_RESET, OLED_CS);

Adafruit_BMP280 bmp;

#define LOG_SIZE 24
float pressureLog[LOG_SIZE];
int logIndex = 0;
bool logFilled = false;

unsigned long lastRead = 0;
const unsigned long READ_INTERVAL = 30UL * 1000UL; // 30s (demo cadence)
unsigned long lastPageSwitch = 0;
bool showPage2 = false;

float localAltitudeM = 0;
float lastPressure = 0, lastTemp = 0, lastAltitude = 0;
String lastTrend = "STABLE ->";

void setup() {
  Serial.begin(115200);
  Wire.begin(21, 22);
  if (!bmp.begin(0x76)) {
    Serial.println("BMP280 not found at 0x76, trying 0x77...");
    bmp.begin(0x77);
  }
  pinMode(GREEN_LED, OUTPUT);
  pinMode(RED_LED, OUTPUT);
  analogReadResolution(12);

  if (!display.begin(SSD1306_SWITCHCAPVCC)) {
    Serial.println("OLED init failed");
  }
  display.clearDisplay();
  display.display();

  // Read potentiometer and initial sensor values on boot to prevent zero display lag
  int potRaw = analogRead(POT_PIN);
  localAltitudeM = map(potRaw, 0, 4095, 0, 2000);
  
  float pressureHpa = bmp.readPressure() / 100.0F;
  float temp = bmp.readTemperature();
  float seaLevelP = pressureHpa / pow(1.0 - (localAltitudeM / 44330.0), 5.255);
  float altitude = bmp.readAltitude(seaLevelP);

  pressureLog[logIndex % LOG_SIZE] = pressureHpa;
  logIndex++;

  lastPressure = pressureHpa;
  lastTemp = temp;
  lastAltitude = altitude;
}

String trendArrow(float diff) {
  if (diff > 0.5) return "RISING /^";
  if (diff < -0.5) return "FALLING v";
  return "STABLE ->";
}

void loop() {
  // Potentiometer sets local altitude baseline 0-2000m
  int potRaw = analogRead(POT_PIN);
  localAltitudeM = map(potRaw, 0, 4095, 0, 2000);

  if (millis() - lastRead >= READ_INTERVAL) {
    lastRead = millis();

    float pressureHpa = bmp.readPressure() / 100.0F;
    float temp = bmp.readTemperature();

    // sea-level pressure compensation using known local altitude
    float seaLevelP = pressureHpa / pow(1.0 - (localAltitudeM / 44330.0), 5.255);
    float altitude = bmp.readAltitude(seaLevelP);

    pressureLog[logIndex % LOG_SIZE] = pressureHpa;
    logIndex++;
    if (logIndex >= LOG_SIZE) logFilled = true;

    int oldestIdx = logFilled ? (logIndex % LOG_SIZE) : 0;
    float diff = pressureHpa - pressureLog[oldestIdx];
    String trend = trendArrow(diff * 100); // *100 to compare vs 50 Pa = 0.5 hPa threshold

    digitalWrite(GREEN_LED, diff >= -0.5 ? HIGH : LOW);
    digitalWrite(RED_LED, diff < -0.5 ? HIGH : LOW);

    Serial.print("Pressure: "); Serial.print(pressureHpa); Serial.print(" hPa | ");
    Serial.print("Temp: "); Serial.print(temp); Serial.print(" C | ");
    Serial.print("Alt: "); Serial.print(altitude); Serial.print(" m | ");
    Serial.println(trend);

    // store for page 2
    lastTrend = trend;
    lastPressure = pressureHpa;
    lastTemp = temp;
    lastAltitude = altitude;
  }

  // Toggle OLED page every 5 seconds (bypass on boot to draw page 1 instantly)
  static bool firstRun = true;
  if (firstRun || millis() - lastPageSwitch > 5000) {
    if (firstRun) {
      firstRun = false;
    } else {
      showPage2 = !showPage2;
    }
    lastPageSwitch = millis();
    display.clearDisplay();
    display.setTextColor(SSD1306_WHITE);
    display.setTextSize(1);
    display.setCursor(0, 0);
    if (!showPage2) {
      display.print("Pressure: "); display.print(lastPressure, 1); display.println(" hPa");
      display.print("Temp: "); display.print(lastTemp, 1); display.println(" C");
      display.print("Alt: "); display.print(lastAltitude, 1); display.println(" m");
    } else {
      display.setTextSize(2);
      display.println("Trend:");
      display.println(lastTrend);
    }
    display.display();
  }
}
