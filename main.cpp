#include <iostream>
#include <thread>
#include <chrono>
#include <iomanip>
#include "TemperatureMonitor.h"

const char* colors[] = {
    "\033[31m", // red
    "\033[32m", // green
    "\033[33m", // yellow
    "\033[34m", // blue
    "\033[35m", // magenta
    "\033[36m", // cyan
    "\033[91m", // light red
    "\033[92m", // light green
    "\033[93m", // light yellow
    "\033[94m", // light blue
    "\033[0m"   // reset (end color)
};
const int numColors = sizeof(colors)/sizeof(colors[0]) - 1; // last one is reset

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
            int colorIdx = i % numColors;
            std::cout << colors[colorIdx]
                      << monitor.getSensorName(i) << " (" << monitor.getSensorLabel(i) << "): ";
            if (temps[i] < 0) {
                std::cout << "N/A  ";
            } else {
                std::cout << temps[i] << "°C  ";
            }
            std::cout << colors[numColors]; // reset after each sensor
        }
        std::cout << std::flush;
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
    return 0;
}
