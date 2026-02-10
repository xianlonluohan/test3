#pragma once

#ifndef _EM_PM25_SENSOR_LIB_H_
#define _EM_PM25_SENSOR_LIB_H_

#include <WString.h>

/**
 * @file pm25_sensor_lib.h
 */

namespace em {
namespace pm25_sensor_lib {

/**
 * @~Chinese
 * @brief 主版本号。
 */
/**
 * @~English
 * @brief Major version number.
 */
constexpr uint8_t kVersionMajor = 1;

/**
 * @~Chinese
 * @brief 次版本号。
 */
/**
 * @~English
 * @brief Minor version number.
 */
constexpr uint8_t kVersionMinor = 0;

/**
 * @~Chinese
 * @brief 修订版本号。
 */
/**
 * @~English
 * @brief Patch version number.
 */
constexpr uint8_t kVersionPatch = 0;

/**
 * @~Chinese
 * @brief 获取版本号字符串。
 * @return 版本号字符串，格式为 major.minor.patch。
 */
/**
 * @~English
 * @brief Get the version number string.
 * @return The version number string in the format of major.minor.patch.
 */
String Version() {
  return String(kVersionMajor) + '.' + kVersionMinor + '.' + kVersionPatch;
}
}  // namespace pm25_sensor_lib
}  // namespace em
#endif