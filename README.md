# Temperature Monitor (C++)

A lightweight, modern C++ command-line tool for monitoring system temperature sensors on Linux systems.

---

## Features

- **Automatic sensor detection**  
  Scans and displays all available temperature sensors (e.g. CPU, motherboard) using Linux sysfs.

- **Live updates**  
  Continuously displays sensor temperatures in real time.

- **Modular code**  
  Clean C++17 implementation split into reusable header and source files.

---

## Requirements

- Linux (x86, ARM, etc.)
- C++17 compatible compiler (g++ recommended)

---
## Notes

- **Linux Only:**  
  This program relies on Linux sysfs interfaces at `/sys/class/hwmon` and `/sys/class/thermal` to access hardware temperature sensors. It will not work on Windows or macOS.

- **Permissions:**  
  On some systems, sensor files may only be readable by the root user or users in specific groups (such as `sensors` or `adm`). If you see "N/A" or missing temperature readings, try running the program with elevated permissions using `sudo`.

- **Sensor Labels:**  
  The program attempts to read sensor names or labels where available, providing more user-friendly output. If no label is found, a default or generic name will be shown.
---
## Build Instructions

```sh
git clone https://github.com/AbubakrAlwi/Temperature_Monitor_Linux_CLI.git
cd Temperature_Monitor_Linux_CLI
g++ -std=c++17 -o temp_monitor main.cpp TemperatureMonitor.cpp
./temp_monitor
