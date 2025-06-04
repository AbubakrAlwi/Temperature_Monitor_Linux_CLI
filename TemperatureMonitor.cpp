#include "TemperatureMonitor.h"
#include <filesystem>
#include <fstream>
#include <sstream>

namespace fs = std::filesystem;

TemperatureMonitor::TemperatureMonitor() {
    findSensors();
}

void TemperatureMonitor::findSensors() {
    // Try /sys/class/hwmon/hwmon*/temp*_input
    for (const auto& entry : fs::directory_iterator("/sys/class/hwmon")) {
        for (const auto& subentry : fs::directory_iterator(entry.path())) {
            auto filename = subentry.path().filename().string();
            if (filename.find("temp") == 0 && filename.find("_input") != std::string::npos) {
                sensorFiles.push_back(subentry.path());
                // Try to read the label for user-friendly name
                std::string labelFile = subentry.path().parent_path().string() + "/" + filename.substr(0, filename.find("_input")) + "_label";
                std::ifstream label(labelFile);
                if (label) {
                    std::string labelName;
                    getline(label, labelName);
                    sensorNames.push_back(labelName);
                } else {
                    sensorNames.push_back(filename);
                }
            }
        }
    }
    // Fallback to /sys/class/thermal/thermal_zone*/temp
    if (sensorFiles.empty()) {
        for (const auto& entry : fs::directory_iterator("/sys/class/thermal")) {
            auto filename = entry.path().filename().string();
            if (filename.find("thermal_zone") == 0) {
                sensorFiles.push_back(entry.path().string() + "/temp");
                sensorNames.push_back(filename);
            }
        }
    }
}

std::vector<float> TemperatureMonitor::getTemperatures() const {
    std::vector<float> temps;
    for (const auto& file : sensorFiles) {
        temps.push_back(readTemperature(file));
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
    return sensorFiles.size();
}

std::string TemperatureMonitor::getSensorName(size_t index) const {
    if (index >= sensorNames.size()) return "Unknown";
    return sensorNames[index];
}
