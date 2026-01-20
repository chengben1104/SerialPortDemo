/*
 * @Author: ben.cheng(ben.cheng@Robotrak.cn)
 * @Date: 2026-01-19 18:07:44
 * @LastEditors: ben.cheng(ben.cheng@Robotrak.cn)
 * @LastEditTime: 2026-01-20 10:35:39
 * @FilePath: \SerialPortDemo\SerialPortDemo\serial\SerialPortCmd.h
 * @Description:
 *
 * Copyright (c) 2026 by Robotrak, All Rights Reserved.
 */
#pragma once

namespace ao::SerialPort {

enum class SerialPortCmd {
    // Image controls
    RO_SensorWidth = 0, // Sensor width: Sensor Physical Width
    RW_CenteredWidthAlign8,
    RW_BinningMode,
    RW_OutMode,
    RW_OutputFrequency, // Camera Link output frequency
    RW_ReverseReading,
    RW_TestPatterns,
    RW_TestImageHeight,
    RW_TestImageConstant,

    // Integration and trigger controls
    RW_LinePeriod,
    RO_LinePeriodMin,
    RO_AcquisitionLineRate,
    RW_ExposureTime,
    RO_ExposureTimeMin,
    RO_ExposureTimeMax,
    RW_TriggerJitter,
    RW_TriggerMode,
    RW_TriggerMissed,

    // Gain and offset controls
    RW_AnalogPreAmplifierGain,
    RW_DigitalGain,
    RW_DigitalOffset,

    // Flat field correction controls
    RW_FFCEnable,
    WO_FPNReset,
    WO_PRNUReset,
    RW_FPNCalibrationControl,
    RW_PRNUCalibrationControl,

    // Save and restore camera settings
    RW_UserSetLoad,
    WO_UserSetSave,

    // Save and restore FFC settings
    RW_RestoreFFC,
    WO_SaveFFC,

    // Camera states
    RO_CameraState,
    WO_RebootCamera,

    // Save/restore line
    RW_PlaySingleLine,
    WO_RecordCurrentLine,

    // Camera privileges
    RW_PrivilegeLevel,
};

} // namespace ao::SerialPort