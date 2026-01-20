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

        while (true) {
            std::this_thread::sleep_for(std::chrono::seconds(1));
            auto value = spectrometer.writeCmd(SerialPortCmd::RO_SensorWidth);
            std::cout << "readCmd: "
                      << (value.has_value() ? value.value() : -10000)
                      << std::endl;

            std::this_thread::sleep_for(std::chrono::seconds(1));
            std::cout << "writeCmd: "
                      << spectrometer.writeCmd(
                             SerialPortCmd::RW_OutputFrequency, 1)
                      << std::endl;

            std::this_thread::sleep_for(std::chrono::seconds(1));
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
