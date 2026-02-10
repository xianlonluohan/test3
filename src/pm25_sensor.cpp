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

bool s_flag_first_read = true;

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
  if (s_flag_first_read) {
    s_flag_first_read = false;
    for (uint8_t i = 0; i < adc_buff_max_; i++) {
      adc_buffer_[i] = adc_value;
      adc_buff_sum_ += adc_buffer_[i];
    }
    return adc_value;

  } else {
    adc_buff_sum_ -= adc_buffer_[0];

    for (uint8_t i = 0; i < adc_buff_max_ - 1; i++) {
      adc_buffer_[i] = adc_buffer_[i + 1];
    }
    adc_buffer_[adc_buff_max_ - 1] = adc_value;
    adc_buff_sum_ += adc_buffer_[adc_buff_max_ - 1];
    return adc_buff_sum_ / adc_buff_max_;
  }
}

}  // namespace em