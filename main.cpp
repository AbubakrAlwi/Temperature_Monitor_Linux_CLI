#include <iostream>
#include <thread>
#include <chrono>
#include <iomanip>
#include "TemperatureMonitor.h"

int main() {
    TemperatureMonitor monitor;

    if (monitor.sensorCount() == 0) {
        std::cerr << "No temperature sensors found.\n";
        return 1;
    }

    std::cout << "Temperature Monitor - Press Ctrl+C to exit\n";
    std::cout << std::fixed << std::setprecision(1);

    while (true) {
        auto temps = monitor.getTemperatures();
        std::cout << "\r";
        for (size_t i = 0; i < temps.size(); ++i) {
            std::cout << monitor.getSensorName(i) << ": ";
            if (temps[i] < 0) {
                std::cout << "N/A  ";
            } else {
                std::cout << temps[i] << "°C  ";
            }
        }
        std::cout << std::flush;
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
    return 0;
}
