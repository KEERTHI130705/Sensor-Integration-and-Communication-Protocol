#include <Wire.h>
#include "MAX30105.h"
#include "heartRate.h"
#include <Adafruit_AHTX0.h>
#include <Adafruit_INA219.h>
#include <Adafruit_MPU6050.h>

// ===== BLE =====
#include <BLEDevice.h>
#include <BLEServer.h>
#include <BLEUtils.h>
#include <BLE2902.h>
BLECharacteristic *pCharacteristic;
bool deviceConnected = false;
class MyServerCallbacks: public BLEServerCallbacks {
 void onConnect(BLEServer* pServer) { deviceConnected = true; }
 void onDisconnect(BLEServer* pServer) {
 deviceConnected = false;
 BLEDevice::startAdvertising();
 }
};

// ===== SENSORS =====
MAX30105 particleSensor;
Adafruit_AHTX0 aht;
Adafruit_INA219 ina219;
Adafruit_MPU6050 mpu;
// ===== THRESHOLDS =====
#define HR_MIN 60
#define HR_MAX 100
#define SPO2_MIN 95
#define TEMP_MAX 37
#define FALL_THRESHOLD 2.5
#define BATTERY_MIN 3.3
// ===== BUFFERS =====
#define SIZE 5
float HR_Buffer[SIZE] = {0};
float Temp_Buffer[SIZE] = {0};
float Acc_Buffer[SIZE] = {0};
int indexBuffer = 0;
// ===== BPM =====
long lastBeat = 0;
float bpm = 0;
int finalBPM = 0;
const long fingerThreshold = 30000;
// ===== SpO2 =====
float irAvg = 0, redAvg = 0;
float spo2 = 0;
// ===== BATTERY =====
float voltageAvg = 0;
// ===== FUNCTION =====
float movingAverage(float *buf) {
 float sum = 0;
 for (int i = 0; i < SIZE; i++) sum += buf[i];
 return sum / SIZE;
}


void setup() {
 Serial.begin(115200);
 Wire.begin(21, 22);
 // MAX30102
 if (!particleSensor.begin(Wire, I2C_SPEED_FAST)) while (1);
 particleSensor.setup(0x1F, 4, 2, 100, 411, 4096);
 // AHT10
 if (!aht.begin()) while (1);
 // INA219
 if (!ina219.begin()) while (1);
 // MPU6050
 if (!mpu.begin()) while (1);
 mpu.setAccelerometerRange(MPU6050_RANGE_2_G);
 // BLE
 BLEDevice::init("ZENV_Device");
 BLEServer *server = BLEDevice::createServer();
 server->setCallbacks(new MyServerCallbacks());
 BLEService *service = server->createService("1234");
 pCharacteristic = service->createCharacteristic(
 "5678",
 BLECharacteristic::PROPERTY_NOTIFY | BLECharacteristic::PROPERTY_READ
 );
 pCharacteristic->addDescriptor(new BLE2902());
 service->start();
 BLEDevice::getAdvertising()->start();
}


void loop() {
  
 // ===== 1. DATA ACQUISITION =====
 long ir = particleSensor.getIR();
 long red = particleSensor.getRed();
 sensors_event_t hum, temp;
 aht.getEvent(&hum, &temp);
 sensors_event_t a, g, t;
 mpu.getEvent(&a, &g, &t);
 float voltage = ina219.getBusVoltage_V();
  
 // ===== 2. FILTERING =====
 // ---- HEART RATE ----
 if (ir > fingerThreshold && checkForBeat(ir)) {
 long delta = millis() - lastBeat;
 lastBeat = millis();
 bpm = 60 / (delta / 1000.0);
 if (bpm > 40 && bpm < 180) {
 HR_Buffer[indexBuffer] = bpm;
 finalBPM = movingAverage(HR_Buffer);
 }
 } else {
 finalBPM = 0;
 }
  
 // ---- TEMPERATURE ----
 Temp_Buffer[indexBuffer] = temp.temperature;
 float temperature = movingAverage(Temp_Buffer);
  
 // ---- ACCELERATION (FALL DETECTION) ----
 float ax = a.acceleration.x / 9.81;
 float ay = a.acceleration.y / 9.81;
 float az = a.acceleration.z / 9.81;
 float accMag = sqrt(ax*ax + ay*ay + az*az);
 Acc_Buffer[indexBuffer] = accMag;
 float accFiltered = movingAverage(Acc_Buffer);
  
 // ---- SpO2 CONTINUOUS ----
 if (ir > 50000) {
 irAvg = 0.9 * irAvg + 0.1 * ir;
 redAvg = 0.9 * redAvg + 0.1 * red;
 float irAC = ir - irAvg;
 float redAC = red - redAvg;
 if (irAvg > 0 && redAvg > 0) {
 float R = (redAC / redAvg) / (irAC / irAvg);
 spo2 = -45.060 * R * R + 30.354 * R + 94.845;
 if (spo2 > 100) spo2 = 100;
 if (spo2 < 0) spo2 = 0;
 }
 } else {
 spo2 = 0;
 }
  
 // ---- BATTERY ----
 voltageAvg = 0.9 * voltageAvg + 0.1 * voltage;
 // ===== 3. HEALTH ANALYSIS =====
 String HR_Status = (finalBPM < HR_MIN || finalBPM > HR_MAX) ? "Abnormal" : "Normal";
 String SpO2_Status = (spo2 < SPO2_MIN) ? "Low" : "Normal";
 String Temp_Status = (temperature > TEMP_MAX) ? "High" : "Normal";
 bool Fall = (accFiltered > FALL_THRESHOLD);
 String Battery_Status = (voltageAvg < BATTERY_MIN) ? "Low" : "Normal";

  
 // ===== 4. UPDATE BUFFER =====
 indexBuffer = (indexBuffer + 1) % SIZE;

  
 // ===== 5. BLE DATA =====
 String data = String(finalBPM) + "," +
 String((int)spo2) + "," +
 String((int)temperature) + "," +
 Battery_Status + "," +
 String(Fall) + "," +
 HR_Status + "," +
 SpO2_Status + "," +
 Temp_Status;
 Serial.println(data);
 if (deviceConnected) {
 pCharacteristic->setValue(data.c_str());
 pCharacteristic->notify();
 }
 delay(200);
}
