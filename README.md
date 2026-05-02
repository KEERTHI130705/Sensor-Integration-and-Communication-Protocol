# Smart Wearable Health Monitoring System using ESP32

## Overview
This project presents the development of a smart wearable prototype designed for continuous health monitoring and safety detection. The system integrates multiple sensors with an ESP32 microcontroller to collect real-time physiological and motion data.

The device measures heart rate, SpO₂, temperature, motion, and battery parameters, processes the data using filtering and analysis techniques, and transmits it wirelessly via BLE for live monitoring.

---

## Features
- Real-time Heart Rate (BPM) monitoring  
- SpO₂ (Blood Oxygen Level) measurement  
- Temperature monitoring  
- Fall detection using motion sensor  
- SOS / emergency alert system  
- Battery monitoring and power management  
- Wireless data transmission via BLE  
- Mobile app display (nRF Connect)  

---

## System Architecture
The system follows a modular wearable design:

1. Sensors collect physiological and motion data  
2. ESP32 processes data using filtering and calculations  
3. Data is transmitted via BLE  
4. Mobile app displays live parameters  

As shown in the system workflow, sensors communicate with ESP32 using I²C, and processed data is sent to a mobile application via BLE.

---

## Hardware Components

- ESP WROOM 32 MCU Module (ESP32)  
- MAX30102 Heart Rate and SpO₂ Sensor  
- MPU-6050 Accelerometer & Gyroscope  
- AHT10 Temperature & Humidity Sensor  
- INA219 Current / Power Monitoring Module  
- LiPo Battery (3.7V, 500mAh)  
- TP4056 Battery Charging Module  
- AMS1117-3.3V Voltage Regulator  
- Breadboard and Jumper Wires  

---

## Working Principle
The wearable device collects real-time data from multiple sensors:

- MAX30102 → Heart rate & SpO₂  
- AHT10 → Temperature  
- MPU6050 → Motion and fall detection  
- INA219 → Battery monitoring  

All sensors communicate with ESP32 using I²C. The ESP32 processes the data using filtering techniques, motion analysis, and threshold-based logic to improve accuracy.

The processed data is then transmitted via BLE to a mobile application (nRF Connect), where live values and alerts are displayed.

---

## Work Done

### Sensor Integration
- Interfaced MAX30102, MPU6050, AHT10, and INA219 with ESP32  
- Established I²C communication and verified sensor addresses  
- Initialized and configured all sensors  

### Data Processing
- Collected raw IR and Red signals  
- Observed noise due to motion and placement  
- Applied filtering techniques (EMA, Moving Average)  
- Implemented peak detection for BPM  
- Developed logic for SpO₂ estimation  

### Communication
- Configured BLE on ESP32  
- Transmitted real-time data to mobile app (nRF Connect)  

### Power System
- Implemented LiPo battery-powered system  
- Used TP4056 for charging and protection  
- Used AMS1117 for stable 3.3V supply  
- Monitored power using INA219  

### Validation & Debugging
- Tested system under different conditions  
- Fixed communication issues and unstable readings  
- Improved overall system reliability  

---

## Challenges

### Sensor Noise
- MAX30102 signals unstable due to motion and contact  
- MPU6050 produced false motion due to small vibrations  

### Communication Issues
- I²C address conflicts and wiring problems  
- BLE instability and intermittent disconnections  

### Data Accuracy
- BPM and SpO₂ required calibration  
- Filtering parameters needed tuning  

### Hardware Issues
- Power fluctuations affected readings  
- Loose connections caused inconsistent data  

---

## Future Enhancements
- Dedicated mobile application  
- GPS integration for location tracking  
- Improved battery efficiency  
- AI-based health prediction  
- Miniaturized wearable design (PCB + casing)  
- Additional sensors (ECG, BP, etc.)  

---

## Technologies Used
- ESP32 (Embedded Systems)  
- Arduino IDE (C/C++)  
- I²C Communication Protocol  
- BLE (Bluetooth Low Energy)  
- Digital Signal Processing (Filtering)  

---

## Team Contributions
This project was developed as a team effort, where each member contributed to different modules including sensor integration, BLE communication, signal processing, and system validation.

---

## Author
Keerthi Harsha  
Electronics and Communication Engineering
