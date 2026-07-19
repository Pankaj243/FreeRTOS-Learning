# 🚗 FreeRTOS Vehicle Health Monitoring System

A real-time Vehicle Health Monitoring System developed using **FreeRTOS** in **C** with **Python-based alarm monitoring**. The project simulates multiple vehicle sensors, processes sensor data using FreeRTOS tasks, and generates alerts when sensor values exceed predefined thresholds.

---

## 📌 Project Overview

This project demonstrates the implementation of a real-time embedded application using FreeRTOS concepts such as:

- Task Management
- Queue Communication
- Mutex Synchronization
- Real-Time Sensor Simulation
- Threshold-Based Alarm System
- Embedded C and Python Integration

The system simulates four important vehicle parameters:

- 🌡 Temperature
- 🚗 Vehicle Speed
- 🔋 Battery Voltage
- 🛞 Tire Pressure

Sensor data is periodically generated, transmitted through a FreeRTOS queue, displayed on a dashboard, stored in a file, and monitored by a Python application that generates audible alarms whenever abnormal conditions are detected.

---

# System Architecture

```
+-----------------------------+
|     Temperature Task        |
+-----------------------------+

+-----------------------------+
|        Speed Task           |
+-----------------------------+

+-----------------------------+
|    Battery Voltage Task     |
+-----------------------------+

+-----------------------------+
|      Pressure Task          |
+-----------------------------+
              |
              |
              V
       FreeRTOS Queue
              |
              V
+-----------------------------+
|      Dashboard Task         |
|-----------------------------|
| Update latest sensor values |
| Print Dashboard             |
| Write sensor_data.txt       |
+-----------------------------+
              |
              |
              V
+-----------------------------+
|      Python Monitor         |
|-----------------------------|
| Read sensor_data.txt        |
| Check Thresholds            |
| Generate Alarm              |
+-----------------------------+
```

---

# Features

- FreeRTOS Multi-Tasking
- Queue-Based Inter-Task Communication
- Mutex for Shared Resource Protection
- Real-Time Sensor Simulation
- Dashboard Display
- Python Alarm Monitoring
- Threshold-Based Warning System
- File-Based Communication between C and Python

---

# Simulated Sensors

| Sensor | Normal Range | Alarm Condition |
|---------|-------------:|----------------:|
| Temperature | 20°C - 100°C | >100°C |
| Speed | 0 - 120 km/h | >120 km/h |
| Battery Voltage | 11.8V - 14.2V | <11.8V or >14.2V |
| Tire Pressure | 30 - 34 PSI | <30 PSI or >34 PSI |

---

# Technologies Used

- C
- FreeRTOS
- Visual Studio
- Python
- Windows Simulator
- Git
- GitHub

---

# Project Structure

```
Vehicle_Monitor_System
│
├── FreeRTOS
│   ├── main.c
│   ├── FreeRTOSConfig.h
│   └── ...
│
├── Python
│   └── sensor_alarm.py
│
├── Output
│   └── sensor_data.txt
│
├── README.md
└── .gitignore
```

---

# How It Works

1. Each sensor task periodically generates simulated data.
2. Sensor data is sent to a FreeRTOS Queue.
3. Dashboard Task receives sensor values.
4. Dashboard updates the latest sensor readings.
5. Sensor values are written to `sensor_data.txt`.
6. Python continuously monitors the file.
7. If any value crosses its threshold, an audible alarm is generated.

---

# Sample Console Output

```
------------------------------------------
Temperature : 98.00 C
Speed       : 75 km/h
Battery     : 12.80 V
Pressure    : 32.40 PSI
------------------------------------------
```

When thresholds are exceeded:

```
***** WARNING *****
High Temperature

***** WARNING *****
Overspeed

***** WARNING *****
Low Battery Voltage
```

---

# FreeRTOS Concepts Demonstrated

- Task Creation
- Task Scheduling
- Queue
- Mutex
- Inter-Task Communication
- Real-Time Monitoring
- Synchronization

---

# Future Enhancements

- UART Communication with STM32
- Live Python Dashboard (Tkinter/PyQt)
- Real-Time Graph Plotting
- Data Logging with Timestamp
- CAN Bus Integration
- Automotive ECU Simulation
- Fault Injection Testing

---

# Author

**Pankaj Kumbhar**

Embedded Software Engineer

Skills:
- Embedded C
- C
- Python
- FreeRTOS
- CAN
- Automotive Embedded Systems

---

## License

This project is open-source and available under the MIT License.