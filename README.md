# Wearable Multi-Sensor Integration System using ESP32

## Overview
This project focuses on the integration of multiple sensors into a wearable system using the ESP32 microcontroller. The system is designed to acquire real-time physiological and environmental data while maintaining efficient communication using the I²C protocol.

The project demonstrates reliable sensor interfacing, power management, and continuous data acquisition, forming a strong foundation for wearable health monitoring and safety systems.

---

## Objectives
- Integrate multiple sensors using a shared I²C communication bus  
- Perform sensor initialization and connectivity verification  
- Acquire continuous real-time sensor data  
- Analyze raw signal behavior (noise, fluctuations, stability)  
- Implement a compact and power-efficient wearable hardware setup  

---

## Hardware Components

- ESP WROOM 32 MCU Module (ESP32)  
- MAX30102 Heart Rate and SpO₂ Sensor  
- MPU-6050 3-Axis Accelerometer and Gyroscope  
- AHT10 Temperature & Humidity Sensor  
- INA219 Current / Power Monitoring Module  
- WLY902030 3.7V 500mAh LiPo Battery  
- TP4056 Li-ion Battery Charging Module (with protection)  
- AMS1117-3.3V Voltage Regulator Module  
- Breadboard and Jumper Wires  

---

## System Architecture

The ESP32 acts as the central controller and communicates with all sensors using the I²C protocol.

### I²C Connections
- SDA → GPIO 21  
- SCL → GPIO 22  

All sensors share:
- Common 3.3V supply  
- Common ground  

---

## Sensors Description

### MAX30102 (PPG Sensor)
- Measures heart rate and blood oxygen (SpO₂)  
- Uses red and infrared light (photoplethysmography)  
- Outputs raw IR and Red signal values  

### MPU-6050
- 3-axis accelerometer and gyroscope  
- Provides motion and orientation data  
- Useful for movement tracking and fall detection  

### AHT10
- Digital temperature and humidity sensor  
- Provides calibrated environmental data  
- Low power consumption  

### INA219
- Measures voltage, current, and power  
- Used for battery monitoring and power analysis  

---

## Power Management System

- **LiPo Battery (3.7V, 500mAh)** powers the system  
- **TP4056 Module** handles battery charging and protection  
- **AMS1117-3.3V Regulator** provides stable 3.3V output for ESP32 and sensors  

This setup ensures safe, portable, and continuous operation suitable for wearable devices.

---

## Features
- Multi-sensor integration using I²C  
- Real-time data acquisition from all sensors  
- Sensor connectivity testing and initialization  
- Battery voltage and current monitoring  
- Compact and portable hardware setup  

---

## Data Acquisition

The system continuously reads:
- IR and Red values (MAX30102)  
- Acceleration and gyroscope data (MPU6050)  
- Temperature and humidity (AHT10)  
- Battery voltage and current (INA219)  

Data is displayed via serial output and can be logged for further analysis.

---

## Observations

### Sensor Noise
- MAX30102 signals are sensitive to motion and contact  
- Raw data contains fluctuations and requires filtering  

### Hardware Challenges
- Incorrect wiring leads to sensor detection failure  
- Stable power supply is essential for consistent readings  

### Wearable Constraints
- Motion and placement affect sensor accuracy  
- Signal stability varies with real-world usage  

---

## Future Scope
- Apply digital signal processing (DSP) for noise reduction  
- Calculate heart rate (BPM) and SpO₂ accurately  
- Implement BLE communication for wireless data transfer  
- Develop a mobile application for real-time monitoring  
- Optimize PCB design for compact wearable form  

---

## Technologies Used
- ESP32 (Embedded Systems)  
- Arduino IDE (C/C++)  
- I²C Communication Protocol  
- Serial Monitoring  
- Embedded Sensor Integration  

---

## Author
Keerthi Harsha  
Electronics and Communication Engineering
