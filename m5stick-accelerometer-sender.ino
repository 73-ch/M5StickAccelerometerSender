#include <M5StickC.h>
#include <ArduinoOSC.h>

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

  M5.Axp.ScreenBreath(7);

  // WiFi stuff
  WiFi.begin(SSID, PASS);
  M5.Lcd.println("Connecting");

  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
  }

  M5.Lcd.println("Connected");

  OscWiFi.publish(HOST, PORT, BASE_PATH "/gyro", gyroX, gyroY, gyroZ);
  OscWiFi.publish(HOST, PORT, BASE_PATH "/accel", accX, accY, accZ);
}

void loop() {
  M5.IMU.getGyroData(&gyroX, &gyroY, &gyroZ);
  M5.IMU.getAccelData(&accX, &accY, &accZ);

  OscWiFi.update();
  M5.update();
}
