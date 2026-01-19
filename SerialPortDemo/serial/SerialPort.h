/*
 * @Author: qi.wang (qi.wang@robotrak.cn)
 * @Date: 2025-02-19 14:47:45
 * @LastEditors: qi.wang (qi.wang@robotrak.cn)
 * @LastEditTime: 2025-02-21 09:35:02
 * @FilePath: \saris\saris\src\control\driver\serial\SerialPort.h
 * @Description:
 *
 * reference: 28电机驱动协议-V38.pdf
 *
 * Copyright (c) 2025 by Robotrak, All Rights Reserved.
 */
#pragma once

#include <span>
#include <vector>
#include <string>
#include <thread>
#include <asio.hpp>

namespace saris::control {

struct SerialPortReceiver {
    virtual void onDataReceived(std::span<const uint8_t>) = 0;
};

class SerialPort {
public:
    SerialPort(const std::string& com, SerialPortReceiver* rcv);
    ~SerialPort();
    void write(std::span<const uint8_t> msg);

private:
    SerialPortReceiver* receiver{ nullptr };
    std::vector<uint8_t> received;
    asio::io_context io;
    asio::serial_port serial;
    std::jthread thread;

    void startRead();
};

} // namespace saris::control