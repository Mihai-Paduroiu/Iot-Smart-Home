
# IoT System: ESP32 Data Transmission to Raspberry Pi  

## Description  
This project implements an IoT system where an ESP32 microcontroller collects data from a flame sensor and a photoresistor and transmits the readings to a Raspberry Pi using UDP communication. The system also includes an LED alarm that flashes during a fire event and a button to reset the alarm.  

---

## Features  
- Reads environmental light intensity using a photoresistor.  
- Detects fire levels using a flame sensor.  
- Transmits sensor readings to a Raspberry Pi using UDP protocol.  
- LED alarm flashes during a fire event with a reset button to turn off the alarm.  

---

## Technologies Used  
- **Microcontroller**: ESP32.  
- **Sensors**:  
  - Flame Sensor.  
  - Photoresistor (Light Sensor).  
- **Actuator**: Red LED for alarm indication.  
- **Communication Protocol**: UDP (Wi-Fi).  
- **Programming Language**: C/C++.  
- **Tools**: Arduino IDE for development.  

---

## Hardware Requirements  
- **ESP32** Microcontroller.  
- **Flame Sensor** (Connected to GPIO 33).  
- **Photoresistor** (Connected to GPIO 32).  
- **LED** (Connected to GPIO 5).  
- **Push Button** (Connected to GPIO 4).  
- **Raspberry Pi** (Configured to receive UDP packets).  

---

## Wiring Diagram  
| Component        | ESP32 Pin  |  
|------------------|------------|  
| Flame Sensor     | GPIO 33    |  
| Photoresistor    | GPIO 32    |  
| Red LED          | GPIO 5     |  
| Button           | GPIO 4     |  

---

## Installation  

### 1. ESP32 Setup  
1. Open the code in the Arduino IDE.  
2. Install the ESP32 board manager from the **Boards Manager**.  
3. Connect the ESP32 to your computer.  
4. Upload the code to the ESP32.  

### 2. Raspberry Pi Setup  
1. Connect the Raspberry Pi to the same Wi-Fi network as the ESP32.  
2. Configure the Raspberry Pi to listen on UDP port 9000 for incoming packets.  

---

## Usage  
1. Power on the ESP32 and Raspberry Pi.  
2. Observe sensor readings (light intensity and flame level) on the ESP32’s Serial Monitor.  
3. Data packets are transmitted to the Raspberry Pi in the format:  
   ```
   <light_sensor_value>, <flame_sensor_reading>, <count>
   ```
4. When a fire is detected:  
   - The LED alarm flashes.  
   - Press the button connected to GPIO 4 to reset the alarm.  

---

## Sensor Thresholds  
- **Flame Sensor**:  
  - Close Fire: 150 - 999.  
  - Distant Fire: 1000 - 2999.  
  - No Fire: ≥ 3000.  
- **Photoresistor**: Reads light intensity as an analog value (0 - 4095).  

---

## Notes  
- Adjust the Wi-Fi SSID and password in the code to match your network:  
  ```cpp
  const char* ssid = "Your_WiFi_SSID";
  const char* pass = "Your_WiFi_Password";
  ```
- Update the Raspberry Pi’s IP address in the code:  
  ```cpp
  const char* raspberryIP = "Your_Raspberry_Pi_IP";
  ```

---

## Contact  
For questions or support, feel free to reach out:  
**Email**: [your.email@example.com]  
**GitHub**: [GitHub Profile Link]  

--- 

This README provides all necessary details for understanding, setting up, and running the project. Let me know if you'd like further customization!"# Iot-Smart-Home" 
