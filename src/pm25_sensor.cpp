/**
 * @file pm25_sensor.cpp
 */

#include "pm25_sensor.h"

namespace em {

namespace {
constexpr float kCovRatio = 0.2;
constexpr uint16_t kNoDustVoltage = 600;

#if defined(ESP32)
constexpr uint16_t kSysVoltage = 3300;
constexpr uint16_t kAdcMaxValue = 4096;
#else
constexpr uint16_t kSysVoltage = 5000;
constexpr uint16_t kAdcMaxValue = 1024;
#endif

static const uint8_t s_adc_buff_max = 10;

bool g_flag_first_read = true;

uint16_t g_adc_buffer[s_adc_buff_max] = {0};

uint32_t g_adc_buff_sum = 0;

}  // namespace

Pm25Sensor::Pm25Sensor(const uint8_t iled_pin, const uint8_t dust_pin) : iled_pin_(iled_pin), dust_pin_(dust_pin) {
}

void Pm25Sensor::Init() {
  pinMode(iled_pin_, OUTPUT);
  digitalWrite(iled_pin_, LOW);
}

float Pm25Sensor::Read() const {
  digitalWrite(iled_pin_, HIGH);
  delayMicroseconds(280);

  uint16_t adc_value = analogRead(dust_pin_);

  delayMicroseconds(40);
  digitalWrite(iled_pin_, LOW);

  adc_value = Filter(adc_value);

  const float voltage = (kSysVoltage / kAdcMaxValue) * adc_value * 11;

  if (voltage >= kNoDustVoltage) {
    return (voltage - kNoDustVoltage) * kCovRatio;
  } else {
    return 0;
  }
}

uint16_t Pm25Sensor::Filter(const uint16_t adc_value) const {
  if (g_flag_first_read) {
    g_flag_first_read = false;
    for (uint8_t i = 0; i < s_adc_buff_max; i++) {
      g_adc_buffer[i] = adc_value;
      g_adc_buff_sum += g_adc_buffer[i];
    }
    return adc_value;

  } else {
    g_adc_buff_sum -= g_adc_buffer[0];

    for (uint8_t i = 0; i < s_adc_buff_max - 1; i++) {
      g_adc_buffer[i] = g_adc_buffer[i + 1];
    }
    g_adc_buffer[s_adc_buff_max - 1] = adc_value;
    g_adc_buff_sum += g_adc_buffer[s_adc_buff_max - 1];
    return g_adc_buff_sum / s_adc_buff_max;
  }
}

}  // namespace em