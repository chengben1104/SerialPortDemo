#pragma once

#include <mutex>
#include <deque>
#include <thread>
#include <functional>
#include <shared_mutex>
#include <condition_variable>
#include "SerialPort.h"
#include "SerialPortCmd.h"

namespace ao::SerialPort {

class Spectrometer : public SerialPortReceiver {
public:
    explicit Spectrometer(const std::string& com);
    ~Spectrometer();

    std::optional<int> read(SerialPortCmd cmd);
    bool write(SerialPortCmd cmd, int value);

private:
    std::mutex mtx;
    std::condition_variable cv;
    std::string buffer;
    SerialPort serial;
    bool waiting = false;
    bool writeOk = false;
    std::optional<int> readResult;

    void onDataReceived(std::span<const uint8_t> data) override;
    void onReadResponse(std::optional<int> value);
    void onWriteAck(bool ok);
};

} // namespace ao::SerialPort
