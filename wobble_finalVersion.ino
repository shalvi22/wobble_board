#include <Wire.h>
#include <MPU6050.h>

MPU6050 mpu;

void setup() {
  Serial.begin(115200);
  Wire.begin();
  mpu.initialize();
  
  if (!mpu.testConnection()) {
    Serial.println("MPU6050 connection failed");
    while (1);
  }

  Serial.println("MPU6050 connection successful");
}

void loop() {
  int16_t ax, ay, az;
  int16_t gx, gy, gz;
  
  // Read raw accelerometer and gyroscope measurements from MPU6050
  mpu.getMotion6(&ax, &ay, &az, &gx, &gy, &gz);

  // Convert the raw accelerometer values to angles
  float angleX = atan(ax / sqrt(pow(ay, 2) + pow(az, 2))) * 180 / PI;
  float angleY = atan(ay / sqrt(pow(ax, 2) + pow(az, 2))) * 180 / PI;
  float angleZ = (atan(az / sqrt(pow(ax, 2) + pow(ay, 2))) * 180 / PI) - 90.00;

  // Print the angles in the desired format
  String dataPacket=String(angleX) + "," + String(angleY) + "," + String(angleZ);
  Serial.println(dataPacket);
}
