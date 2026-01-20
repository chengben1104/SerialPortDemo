#include "Utils.h"
#include <format>

namespace {

using namespace ao::SerialPort;

std::string cmdToString(SerialPortCmd cmd)
{
    switch (cmd) {
    // Image controls
    case SerialPortCmd::RO_SensorWidth:
        return "snsw";
    case SerialPortCmd::RW_CenteredWidthAlign8:
        return "widt";
    case SerialPortCmd::RW_BinningMode:
        return "binn";
    case SerialPortCmd::RW_OutMode:
        return "mode";
    case SerialPortCmd::RW_OutputFrequency:
        return "clfq";
    case SerialPortCmd::RW_ReverseReading:
        return "revr";
    case SerialPortCmd::RW_TestPatterns:
        return "srce";
    case SerialPortCmd::RW_TestImageHeight:
        return "Tsth";
    case SerialPortCmd::RW_TestImageConstant:
        return "Tstc";

    // Integration and trigger controls
    case SerialPortCmd::RW_LinePeriod:
        return "tper";
    case SerialPortCmd::RO_LinePeriodMin:
        return "tpmi";
    case SerialPortCmd::RO_AcquisitionLineRate:
        return "-";
    case SerialPortCmd::RW_ExposureTime:
        return "tint";
    case SerialPortCmd::RO_ExposureTimeMin:
        return "timi";
    case SerialPortCmd::RO_ExposureTimeMax:
        return "tima";
    case SerialPortCmd::RW_TriggerJitter:
        return "tjit";
    case SerialPortCmd::RW_TriggerMode:
        return "sync";
    case SerialPortCmd::RW_TriggerMissed:
        return "trgm";

    // Gain and offset controls
    case SerialPortCmd::RW_AnalogPreAmplifierGain:
        return "pamp";
    case SerialPortCmd::RW_DigitalGain:
        return "gain";
    case SerialPortCmd::RW_DigitalOffset:
        return "offs";

    // Flat field correction controls
    case SerialPortCmd::RW_FFCEnable:
        return "ffcp";
    case SerialPortCmd::WO_FPNReset:
        return "rsto";
    case SerialPortCmd::WO_PRNUReset:
        return "rstg";
    case SerialPortCmd::RW_FPNCalibrationControl:
        return "calo";
    case SerialPortCmd::RW_PRNUCalibrationControl:
        return "calg";

    // Save and restore camera settings
    case SerialPortCmd::RW_UserSetLoad:
        return "rcfg";
    case SerialPortCmd::WO_UserSetSave:
        return "scfg";

    // Save and restore FFC settings
    case SerialPortCmd::RW_RestoreFFC:
        return "rffc";
    case SerialPortCmd::WO_SaveFFC:
        return "sffc";

    // Camera states
    case SerialPortCmd::RO_CameraState:
        return "stat";
    case SerialPortCmd::WO_RebootCamera:
        return "boot";

    // Save/restore line
    case SerialPortCmd::RW_PlaySingleLine:
        return "play";
    case SerialPortCmd::WO_RecordCurrentLine:
        return "recl";

    // Camera privileges
    case SerialPortCmd::RW_PrivilegeLevel:
        return "lock";

    default:
        return "";
    }
}

} // namespace

namespace ao::SerialPort {

std::string cmd2String(SerialPortCmd cmd, std::optional<int> value)
{
    if (value.has_value()) {
        return std::format(
            "{}{}{}{}{}",
            "w",
            " ",
            cmdToString(cmd),
            " ",
            std::to_string(value.value()),
            "\r");
    }

    return std::format("{}{}{}{}", "r", " ", cmdToString(cmd), "\r");
}

} // namespace ao::SerialPort
