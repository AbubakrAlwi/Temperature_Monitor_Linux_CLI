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

## Build Instructions

```sh
git clone https://github.com/YOUR_USERNAME/temperature-monitor.git
cd temperature-monitor
g++ -std=c++17 -o temp_monitor main.cpp TemperatureMonitor.cpp
./temp_monitor
