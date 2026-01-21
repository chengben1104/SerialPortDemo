/*
 * @Author: ben.cheng(ben.cheng@Robotrak.cn)
 * @Date: 2026-01-20 17:12:36
 * @LastEditors: ben.cheng(ben.cheng@Robotrak.cn)
 * @LastEditTime: 2026-01-21 10:21:15
 * @FilePath: \SerialPortDemo\SerialPortDemo\main.cpp
 * @Description:
 *
 * Copyright (c) 2026 by Robotrak, All Rights Reserved.
 */

#include "Client.h"
#include <QtWidgets/QApplication>
#include "serial/Spectrometer.h"
#include "serial/SerialPort.h"
#include "iostream"
#include "serial/SerialPortCmd.h"

int main(int argc, char* argv[])
{
    using namespace ao::SerialPort;

    try {
        Spectrometer spectrometer("COM15");
        std::cout << "Serial port opened\n";

        std::cout << std::boolalpha;

         while (true) {
         std::this_thread::sleep_for(std::chrono::seconds(2));
         auto value = spectrometer.writeCmd(SerialPortCmd::RO_SensorWidth);
         std::cout << "readCmd: " << (value.has_value() ? value.value() : -10000)
                   << std::endl;

         std::this_thread::sleep_for(std::chrono::seconds(2));
         std::cout << "writeCmd: "
                   << spectrometer.writeCmd(SerialPortCmd::RW_LinePeriod, 500)
                   << std::endl;

        std::this_thread::sleep_for(std::chrono::seconds(2));
        std::cout << "writeCmd: "
                  << spectrometer.writeCmd(SerialPortCmd::RW_ExposureTime, 420)
                  << std::endl;
         }
    }
    catch (const asio::system_error& e) {
        std::cerr << "Open serial failed: " << e.what() << std::endl;
    }

    // QApplication a(argc, argv);
    // Client w;
    // w.show();
    // return a.exec();
}
