/*
 * @Author: ben.cheng(ben.cheng@Robotrak.cn)
 * @Date: 2026-01-19 13:14:23
 * @LastEditors: ben.cheng(ben.cheng@Robotrak.cn)
 * @LastEditTime: 2026-01-20 16:32:51
 * @FilePath: \SerialPortDemo\SerialPortDemo\serial\Spectrometer.cpp
 * @Description:
 *
 * Copyright (c) 2026 by Robotrak, All Rights Reserved.
 */
#include "Spectrometer.h"
#include "iostream"
#include "Utils.h"
#include <string_view>

namespace {

constexpr auto timeout = std::chrono::milliseconds(2000);

bool isSuccessCmd(const std::string_view& stream)
{
    // 找第一个 '>'
    auto pos = stream.find('>');
    if (pos == std::string::npos)
        return false;

    // 只能有一个 '>'
    if (stream.find('>', pos + 1) != std::string::npos)
        return false;

    // '>' 后至少还有两个字符
    if (pos + 2 >= stream.size())
        return false;

    char c1 = static_cast<char>(
        std::tolower(static_cast<unsigned char>(stream[pos + 1])));
    char c2 = static_cast<char>(
        std::tolower(static_cast<unsigned char>(stream[pos + 2])));

    return c1 == 'o' && c2 == 'k';
}

std::optional<int> parseIntBeforeSlash(const std::string_view& stream)
{
    if (stream.empty())
        return std::nullopt;

    // 1. 手动遍历，找第一个 '/'
    std::size_t pos = 0;
    while (pos < stream.size() && stream[pos] != '\r') {
        ++pos;
    }

    // 2. '/' 必须存在，且不能在第一个位置
    if (pos == 0 || pos == stream.size())
        return std::nullopt;

    // 3. '/' 前面的子串
    std::string_view left(stream.data(), pos);

    // 4. 转 int
    int value = 0;
    auto [ptr, ec] =
        std::from_chars(left.data(), left.data() + left.size(), value);

    // 5. 校验完整解析
    if (ec != std::errc{} || ptr != left.data() + left.size())
        return std::nullopt;

    return value;
}

} // namespace

namespace ao::SerialPort {

Spectrometer::Spectrometer(const std::string& com)
    : serial(com, this)
{
}

Spectrometer::~Spectrometer()
{
    cv.notify_all();
}

std::optional<int> Spectrometer::writeCmd(SerialPortCmd cmd)
{
    std::unique_lock lk(mtx);

    waiting = true;
    readResult.reset();

    std::string cmdStr = ao::SerialPort::cmd2String(cmd);
    std::span<const uint8_t> msg{
        reinterpret_cast<const uint8_t*>(cmdStr.data()), cmdStr.size()
    };

    // spdlog::info("send: {}", cmdStr);
    serial.write(msg);
    bool ok = cv.wait_for(lk, timeout, [&] { return !waiting; });

    if (!ok) {
        waiting = false;
        return std::nullopt;
    }

    return readResult;
}

bool Spectrometer::writeCmd(SerialPortCmd cmd, int value)
{
    std::unique_lock lk(mtx);

    waiting = true;
    writeOk = false;

    std::string cmdStr = ao::SerialPort::cmd2String(cmd, value);
    std::span<const uint8_t> msg{
        reinterpret_cast<const uint8_t*>(cmdStr.data()), cmdStr.size()
    };

    // spdlog::info("send: {}", cmdStr);
    serial.write(msg);
    bool ok = cv.wait_for(lk, timeout, [&] { return !waiting; });

    if (!ok) {
        waiting = false;
        return false;
    }

    return writeOk;
}

void Spectrometer::onDataReceived(std::span<const uint8_t> data)
{
    {
        std::lock_guard lock{ mtx };
        buffer.clear();
        buffer.append(reinterpret_cast<const char*>(data.data()), data.size());
        // spdlog::info("recv: {}", buffer);
    }

    if (isSuccessCmd(buffer)) {
        bool isWriteCmd = buffer.front() == '>';
        if (isWriteCmd)
            onWriteAck(true);

        else
            onReadResponse(parseIntBeforeSlash(buffer));
    }
    else {
        writeOk = false;
        readResult = std::nullopt;
    }

    cv.notify_one();
}

void Spectrometer::onReadResponse(std::optional<int> value)
{
    std::lock_guard lk(mtx);
    if (!waiting)
        return;

    readResult = value;
    waiting = false;

    // spdlog::info(
    //     "read cmd: {}",
    //     value.has_value() ? std::to_string(value.value()) : "nullopt");
}

void Spectrometer::onWriteAck(bool ok)
{
    std::lock_guard lk(mtx);
    if (!waiting)
        return;

    writeOk = ok;
    waiting = false;

    // spdlog::info("write cmd: {}", ok);
}

} // namespace ao::SerialPort
