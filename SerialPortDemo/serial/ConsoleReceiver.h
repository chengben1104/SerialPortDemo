#pragma once

#include <QObject>
#include "SerialPort.h"

namespace saris::control {

class ConsoleReceiver : public SerialPortReceiver {

public:
    void onDataReceived(std::span<const uint8_t> data) override;

private:
    std::string buffer;
};

} // namespace saris::control
