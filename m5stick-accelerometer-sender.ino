#include <ArduinoOSC.h>
#include <M5StickC.h>

#include "settings.h"

float accX = 0.0F;
float accY = 0.0F;
float accZ = 0.0F;

float gyroX = 0.0F;
float gyroY = 0.0F;
float gyroZ = 0.0F;

float pitch = 0.0F;
float roll = 0.0F;
float yaw = 0.0F;

void setup() {
  M5.begin();
  M5.IMU.Init();

  // WiFi stuff
  WiFi.begin(SSID, PASS);

  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    M5.Lcd.println("Connecting");
  }

  M5.Lcd.println("Connected");

  OscWiFi.publish(HOST, PORT, "/1/gyro", gyroX, gyroY, gyroZ);
  OscWiFi.publish(HOST, PORT, "/1/accel", accX, accY, accZ);
}

void loop() {
  M5.IMU.getGyroData(&gyroX, &gyroY, &gyroZ);
  M5.IMU.getAccelData(&accX, &accY, &accZ);

  OscWiFi.update();
  M5.update();
}
