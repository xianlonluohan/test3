/**
 * @example read_dust.ino
 */

#include "pm25_sensor.h"

namespace {
#if defined(ESP32)
const uint8_t kILedPin = 14;
const uint8_t kDustPin = 15;
#else
const uint8_t kILedPin = 8;
const uint8_t kDustPin = A1;
#endif

emakefun::Pm25Sensor g_pm25_sensor(kILedPin, kDustPin);
}  // namespace

void setup() {
  Serial.begin(115200);
  Serial.println(String(F("pm25 sensor lib version: ")) + emakefun::Pm25Sensor::Version());
  g_pm25_sensor.Init();
  Serial.println(F("setup successful"));
}

void loop() {
  Serial.println(String("dust: ") + g_pm25_sensor.Read());
  delay(100);
}