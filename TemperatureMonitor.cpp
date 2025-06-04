#include "TemperatureMonitor.h"
#include <filesystem>
#include <fstream>
#include <sstream>

namespace fs = std::filesystem;

TemperatureMonitor::TemperatureMonitor() {
    findSensors();
}

void TemperatureMonitor::findSensors() {
    for (const auto& hwmonEntry : fs::directory_iterator("/sys/class/hwmon")) {
        // Read the chip name from /sys/class/hwmon/hwmonX/name
        std::string chipName;
        std::ifstream nameFile(hwmonEntry.path() / "name");
        if (nameFile) {
            std::getline(nameFile, chipName);
        } else {
            chipName = hwmonEntry.path().filename().string();
        }

        // Find all temp*_input in this hwmon device
        for (const auto& subentry : fs::directory_iterator(hwmonEntry.path())) {
            std::string filename = subentry.path().filename().string();
            if (filename.find("temp") == 0 && filename.find("_input") != std::string::npos) {
                // Try to read the label (e.g., temp1_label)
                std::string labelFile = (hwmonEntry.path() / (filename.substr(0, filename.find("_input")) + "_label")).string();
                std::ifstream labelStream(labelFile);
                std::string label;
                if (labelStream && std::getline(labelStream, label)) {
                    // Use the human-friendly label
                } else {
                    label = filename; // Fallback
                }
                sensors.push_back({chipName, label, subentry.path()});
            }
        }
    }

    // Fallback to /sys/class/thermal/thermal_zone*/temp
    if (sensors.empty()) {
        for (const auto& entry : fs::directory_iterator("/sys/class/thermal")) {
            auto filename = entry.path().filename().string();
            if (filename.find("thermal_zone") == 0) {
                sensors.push_back({filename, "temp", entry.path().string() + "/temp"});
            }
        }
    }
}

std::vector<float> TemperatureMonitor::getTemperatures() const {
    std::vector<float> temps;
    for (const auto& sensor : sensors) {
        temps.push_back(readTemperature(sensor.filePath));
    }
    return temps;
}

float TemperatureMonitor::readTemperature(const std::string& sensorFile) const {
    std::ifstream file(sensorFile);
    if (!file.is_open()) return -1.0f;
    int tempMilliC;
    file >> tempMilliC;
    return tempMilliC / 1000.0f;
}

size_t TemperatureMonitor::sensorCount() const {
    return sensors.size();
}

std::string TemperatureMonitor::getSensorName(size_t index) const {
    if (index >= sensors.size()) return "Unknown";
    return sensors[index].chipName;
}

std::string TemperatureMonitor::getSensorLabel(size_t index) const {
    if (index >= sensors.size()) return "Unknown";
    return sensors[index].label;
}
