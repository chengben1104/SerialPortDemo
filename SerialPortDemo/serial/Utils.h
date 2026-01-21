/*
 * @Author: ben.cheng(ben.cheng@Robotrak.cn)
 * @Date: 2026-01-20 17:12:36
 * @LastEditors: ben.cheng(ben.cheng@Robotrak.cn)
 * @LastEditTime: 2026-01-21 16:06:57
 * @FilePath: \SerialPortDemo\SerialPortDemo\serial\Utils.h
 * @Description:
 *
 * Copyright (c) 2026 by Robotrak, All Rights Reserved.
 */
#pragma once

#include "SerialPortCmd.h"
#include <string>
#include <optional>

namespace ao::SerialPort {

std::string cmd2String(
    SerialPortCmd cmd, std::optional<int> value = std::nullopt);

} // namespace ao::SerialPort