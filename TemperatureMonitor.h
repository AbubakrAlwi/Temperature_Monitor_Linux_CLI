#ifndef TEMPERATURE_MONITOR_H
#define TEMPERATURE_MONITOR_H

#include <vector>
#include <string>

class TemperatureMonitor {
public:
    TemperatureMonitor();
    std::vector<float> getTemperatures() const;
    size_t sensorCount() const;
    std::string getSensorName(size_t index) const;
private:
    std::vector<std::string> sensorFiles;
    std::vector<std::string> sensorNames;
    void findSensors();
    float readTemperature(const std::string& sensorFile) const;
};

#endif // TEMPERATURE_MONITOR_H
