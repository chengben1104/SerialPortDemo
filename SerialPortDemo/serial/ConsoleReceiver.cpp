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
    buffer.append(reinterpret_cast<const char*>(data.data()), data.size());
    //std::cout << "recv: " << buffer << std::endl;

    std::size_t pos;
    while ((pos = buffer.find('\r')) != std::string::npos) {
        std::string line = buffer.substr(0, pos);
        buffer.erase(0, pos + 1);
        std::cout << "recv: " << line << std::endl;
    }
}

} // namespace saris::control
