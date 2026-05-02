# Wearable Sensor Integration System using ESP32

## Overview
This project focuses on the integration of multiple sensors into a wearable system using the ESP32 microcontroller. The system demonstrates reliable sensor interfacing, I²C-based communication, and real-time raw data acquisition.

The work primarily involves sensor bring-up, signal observation, and basic signal processing for physiological data. Advanced features such as BLE communication, mobile application, and emergency alerts are part of planned future development.

---

## Objectives
- Integrate multiple sensors using the I²C protocol  
- Perform sensor initialization and connectivity verification  
- Acquire real-time raw sensor data  
- Analyze signal behavior such as noise and instability  
- Apply basic filtering techniques for improved signal quality  

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

All sensors share a common 3.3V power supply and ground.

---

## Sensors Used

### MAX30102 (PPG Sensor)
- Measures heart rate and SpO₂ using photoplethysmography  
- Generates raw IR and Red signal values  
- Used for pulse detection and oxygen estimation  

### MPU-6050
- 3-axis accelerometer and gyroscope  
- Provides motion and orientation data  

### AHT10
- Digital temperature and humidity sensor  
- Provides environmental data for monitoring  

### INA219
- Measures voltage, current, and power  
- Used for battery monitoring and power analysis  

---

## Power System
- LiPo Battery (3.7V, 500mAh) powers the system  
- TP4056 module handles battery charging and protection  
- AMS1117 regulator provides stable 3.3V output  

---

## Work Done

### Sensor Integration
- Interfaced MAX30102, MPU6050, AHT10, and INA219 with ESP32  
- Established I²C communication and verified sensor detection  
- Initialized sensors and configured parameters  

### Data Acquisition
- Collected raw IR and Red signals from MAX30102  
- Read motion data from MPU6050  
- Measured temperature and humidity using AHT10  
- Monitored battery parameters using INA219  

### Signal Observation
- Observed noise in raw sensor data due to motion and placement  
- Identified fluctuations and instability in PPG signals  

### Basic Signal Processing
- Applied filtering techniques such as:
  - Moving Average  
  - Exponential Moving Average (EMA)  
- Implemented basic peak detection logic for heart rate estimation  
- Developed initial logic for BPM and SpO₂ calculation  

---

## Observations and Challenges

### Signal Noise
- MAX30102 signals are highly sensitive to motion  
- Improper finger placement causes unstable readings  
- Sudden spikes and drops affect accuracy  

### Filtering Challenges
- Raw data produced inconsistent outputs  
- Required tuning of filtering parameters  
- Difficulty in stabilizing BPM values  

### Hardware Issues
- Initial sensor detection failures due to wiring issues  
- Importance of stable power supply and connections  

---

## Planned Features (Future Work)
- Real-time Heart Rate (BPM) monitoring  
- SpO₂ (Blood Oxygen Level) calculation  
- Temperature monitoring  
- Fall detection using MPU6050  
- SOS / Emergency alert system  
- BLE communication for wireless data transfer  
- Mobile application for live data display  
- Battery monitoring and power optimization  

---

## Technologies Used
- ESP32 Microcontroller  
- Arduino IDE (Embedded C/C++)  
- I²C Communication Protocol  
- Serial Monitoring  
- Basic Digital Signal Processing (DSP)  

---

## Author
Keerthi Harsha  
