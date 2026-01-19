/*
 * @Author: ben.cheng(ben.cheng@Robotrak.cn)
 * @Date: 2026-01-19 13:14:23
 * @LastEditors: ben.cheng(ben.cheng@Robotrak.cn)
 * @LastEditTime: 2026-01-19 13:18:21
 * @FilePath: \SerialPortDemo\SerialPortDemo\serial\ConsoleReceiver.cpp
 * @Description:
 *
 * Copyright (c) 2026 by Robotrak, All Rights Reserved.
 */
#include "ConsoleReceiver.h"
#include "iostream"

namespace saris::control {

void ConsoleReceiver::onDataReceived(std::span<const uint8_t> data)
{
    std::string s(data.begin(), data.end());
    std::cout << "recv: " << s << std::endl;
}

} // namespace saris::control
