/*
 * @Author: qi.wang (qi.wang@robotrak.cn)
 * @Date: 2025-02-19 14:47:41
 * @LastEditors: qi.wang (qi.wang@robotrak.cn)
 * @LastEditTime: 2025-02-19 16:25:26
 * @FilePath: \saris\saris\src\control\driver\serial\SerialPort.cpp
 * @Description:
 *
 * Copyright (c) 2025 by Robotrak, All Rights Reserved.
 */
#include "SerialPort.h"
#include <spdlog/spdlog.h>

namespace {

constexpr size_t buffer_size{ 1024 };

} // namespace

namespace ao::SerialPort {

SerialPort::SerialPort(const std::string& com, SerialPortReceiver* rcv)
    : serial(io, com), received(buffer_size), receiver(rcv)
{
    using asio::serial_port_base;

    serial.set_option(serial_port_base::baud_rate(9600));
    serial.set_option(serial_port_base::character_size(8));
    serial.set_option(serial_port_base::parity(serial_port_base::parity::none));
    serial.set_option(
        serial_port_base::stop_bits(serial_port_base::stop_bits::one));

    thread = std::jthread([this]() {
        startRead();
        io.run();
    });
}

SerialPort::~SerialPort()
{
    serial.cancel();
    io.restart();
}

void SerialPort::startRead()
{
    serial.async_read_some(
        asio::buffer(received),
        [this](const asio::error_code& error, std::size_t bytesTransferred) {
            if (!error) {
                receiver->onDataReceived({ received.data(), bytesTransferred });
                startRead();
            }
            else {
                spdlog::error("serial port read error: {}", error.message());
            }
        });
}

void SerialPort::write(std::span<const uint8_t> msg)
{
    serial.async_write_some(
        asio::buffer(msg.data(), msg.size()),
        [](const asio::error_code& error, std::size_t bytesTransferred) {
            if (error) {
                spdlog::error("serial port write error: {}", error.message());
            }
        });
}

} // namespace ao::SerialPort