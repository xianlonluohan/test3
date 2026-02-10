#pragma once

#ifndef _EM_PM25_SENSOR_H_
#define _EM_PM25_SENSOR_H_

#include <Arduino.h>
#include <Wire.h>

/**
 * @file pm25_sensor.h
 */

namespace em {

/**
 * @~Chinese
 * @class Pm25Sensor
 * @brief Pm25Sensor是用于PM2.5灰尘传感器模块的驱动类，用于读取灰尘浓度。
 */
/**
 * @~English
 * @class Pm25Sensor
 * @brief Pm25Sensor is a driver class for PM2.5 dust sensor module, used for reading dust concentration.
 */
class Pm25Sensor {
 public:
  /**
   * @~Chinese
   * @brief 构造函数。
   * @param[in] iled_pin ILED引脚。
   * @param[in] dust_pin 电压模拟量输出引脚。
   */
  /**
   * @~English
   * @brief Constructor.
   * @param[in] iled_pin ILED pin.
   * @param[in] dust_pin Dust pin.
   */
  Pm25Sensor(const uint8_t iled_pin, const uint8_t dust_pin);

  void Init();

  /**
   * @~Chinese
   * @brief 读取传感器测量的灰尘浓度，单位ug/m3。
   * @return 测量到的灰尘浓度值，单位ug/m3。
   */
  /**
   * @~English
   * @brief Read the dust concentration measured by the sensor, in units of ug/m3.
   * @return The measured dust concentration value, in units of ug/m3.
   */
  float Read() const;

 private:
  Pm25Sensor(const Pm25Sensor &) = delete;
  Pm25Sensor &operator=(const Pm25Sensor &) = delete;

  uint16_t Filter(const uint16_t adc_value) const;

  const uint8_t adc_buff_max = 10;

  uint8_t iled_pin_ = 0;
  uint8_t dust_pin_ = 0;

  uint16_t adc_buffer_[adc_buff_max] = {0};

  uint32_t adc_buff_sum_ = 0;
};

}  // namespace em
#endif