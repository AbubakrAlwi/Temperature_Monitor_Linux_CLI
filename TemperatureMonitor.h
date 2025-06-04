#ifndef TEMPERATURE_MONITOR_H
#define TEMPERATURE_MONITOR_H

#include <vector>
#include <string>

struct SensorInfo {
    std::string chipName;    // e.g., "coretemp"
    std::string label;       // e.g., "Package id 0" or "temp1"
    std::string filePath;    // full path to temp*_input
};

class TemperatureMonitor {
public:
    TemperatureMonitor();
    std::vector<float> getTemperatures() const;
    size_t sensorCount() const;
    std::string getSensorName(size_t index) const;
    std::string getSensorLabel(size_t index) const;
private:
    std::vector<SensorInfo> sensors;
    void findSensors();
    float readTemperature(const std::string& sensorFile) const;
};

#endif // TEMPERATURE_MONITOR_H
