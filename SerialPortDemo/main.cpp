#include "Client.h"
#include <QtWidgets/QApplication>
#include "serial/ConsoleReceiver.h"
#include "serial/SerialPort.h"
#include "iostream"

int main(int argc, char* argv[])
{
    saris::control::ConsoleReceiver receiver;

    // 程序打开 COM15，串口工具打开 COM16
    try {
        saris::control::SerialPort port("COM15", &receiver);
        std::cout << "Serial port opened\n";

        while (true) {
            std::this_thread::sleep_for(std::chrono::seconds(1));
            const char* cmd = "r tper\r\n";
            port.write(std::span<const uint8_t>(
                reinterpret_cast<const uint8_t*>(cmd), strlen(cmd)));

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
