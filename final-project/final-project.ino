#include <WiFi.h>
#include <WiFiUDP.h>

const char* ssid = "DVA257";
const char* pass = "DVA257-IoT";
const int senderPort = 7000;
const char* raspberryIP = "192.168.0.103";
const int raspberryPort = 9000;

IPAddress remoteIP;
int remotePort;

WiFiUDP wifiUdpConnection;

const int Led_Red = 5;
const int buttonPin = 4;
const int sensorMin = 0;
const int sensorMax = 4095;
const int flameSensorPin = 33; // Replace with your flame sensor pin
const int photoresistorPin = 32; // Replace with your light sensor pin

void Serial_setup() {
  Serial.begin(115200);
  Serial.println("Serial communication is connected.");
}

void WiFi_setup() {
  Serial.print("This device is connecting to WiFi ...");
  WiFi.begin(ssid, pass);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
  }
  Serial.print("This device is connected to WiFi with IP address: ");
  Serial.println(WiFi.localIP());
}

void setup() {
  Serial_setup();
  WiFi_setup();
  wifiUdpConnection.begin(senderPort);
  pinMode(Led_Red, OUTPUT);
  pinMode(buttonPin, INPUT_PULLUP);
}

void loop() {
  int count = 0;

  while (1) {
    count++;

    // Read and print the intensity of light from the photoresistor
    int lightSensorValue = analogRead(photoresistorPin);
    Serial.print("Intensity of light in the environment: ");
    Serial.println(lightSensorValue, DEC);

    // Check if the button is pressed to turn off the alarm
    if (digitalRead(buttonPin) == LOW) {
      Serial.println("Button pressed - Turning off the alarm");
      analogWrite(Led_Red, 0); // Turn off the red light
      delay(1000); // Optional delay to avoid multiple readings from a single press
      return; // Exit the loop
    }

    // Read and process the flame sensor value
    int flameSensorReading = analogRead(flameSensorPin);
    Serial.print("Flame Sensor Reading: ");
    Serial.println(flameSensorReading);

    if (flameSensorReading >= 150 && flameSensorReading < 1000) {
      Serial.println("** Close Fire **");
    } else if (flameSensorReading >= 1000 && flameSensorReading < 3000) {
      Serial.println("** Distant Fire **");
    } else if (flameSensorReading >= 3000) {
      Serial.println("No Fire");
    }

    // Sending a packet to Raspberry Pi with analog sensor values
    wifiUdpConnection.beginPacket(raspberryIP, raspberryPort);
    wifiUdpConnection.printf("%d, %d, %d", lightSensorValue, flameSensorReading, count);
    wifiUdpConnection.endPacket();
    Serial.println("WiFi sent");

    if (flameSensorReading >= 150 && flameSensorReading < 1000) {

      // Flash the red light continuously
      while (true) {
        analogWrite(Led_Red, 255);  // Turn on the red light
        delay(500);
        analogWrite(Led_Red, 0);    // Turn off the red light
        delay(500);

        // Check if the button is pressed to turn off the alarm during flashing
        if (digitalRead(buttonPin) == LOW) {
          Serial.println("Button pressed - Turning off the alarm");
          analogWrite(Led_Red, 0); // Turn off the red light
          delay(200); // Optional delay to avoid multiple readings from a single press
          return; // Exit the loop
        }
      }
    }

    
    delay(500); // Delay between sensor readings (2 seconds)
  }
}
