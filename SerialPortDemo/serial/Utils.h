#pragma once

#include "SerialPortCmd.h"
#include <string>
#include <optional>

namespace ao::SerialPort {

std::string cmd2String(
    SerialPortCmd cmd, std::optional<int> value = std::nullopt);

} // namespace ao::SerialPort