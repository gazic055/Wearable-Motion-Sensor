// Basic demo for accelerometer readings from Adafruit MPU6050

#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>
#include <Wire.h>
#include <math.h>
#include <BluetoothSerial.h>

Adafruit_MPU6050 mpu;

float gfromaX;
float gfromaY;
float gfromaZ;
float gyroX;
float gyroY;
float gyroZ;
float time = 0.001;
int fallDetected = 0;
byte buffer[24];

BluetoothSerial SerialBT; //this is a BluetoothSerial object, testing bluetooth serial connection, with the raspberry pi

void setup(void) {
  Serial.begin(115200);
  while (!Serial) {
    delay(10); // will pause until serial console opens
  }

  SerialBT.begin("ESP32_BT"); //This will be the name of the ESP32 device for Bluetooth connection.
  Serial.println("Bluetooth device is ready to pair.\n");

  Serial.println("Adafruit MPU6050 test!");
  // Try to initialize!
  if (!mpu.begin()) {
    Serial.println("Failed to find MPU6050 chip");
    SerialBT.println("Failed to find MPU6050 chip");
    while (1) {
      delay(10);
    }
  }
  Serial.println("MPU6050 Found!");

  mpu.setAccelerometerRange(MPU6050_RANGE_8_G);
  mpu.setGyroRange(MPU6050_RANGE_250_DEG);
  mpu.setFilterBandwidth(MPU6050_BAND_21_HZ);
  Serial.println("");
  delay(100);
}


void loop() {

  /* Get new sensor events with the readings */
  sensors_event_t a, g, temp;
  mpu.getEvent(&a, &g, &temp);

  /* Print out the values */
  Serial.print("AccelX:");
  gfromaX = a.acceleration.x / 9.81;
  deltaX = (gfromaX*9.81 * (time*time))/2
  Serial.print(a.acceleration.x);
  Serial.print(",");
  Serial.print("AccelY:");
  gfromaY = a.acceleration.y / 9.81;
  deltaY = (gfromaY*9.81 * (time*time))/2
  Serial.print(a.acceleration.y);
  Serial.print(",");
  Serial.print("AccelZ:");
  gfromaZ = a.acceleration.z / 9.81;
  deltaZ = (gfromaZ*9.81 * (time*time))/2
  Serial.print(a.acceleration.z);
  Serial.print(", ");

  Serial.print("gfromaX:");
  Serial.print(gfromaX);
  Serial.print(",");
  Serial.print("gfromaY:");
  Serial.print(gfromaY);
  Serial.print(",");
  Serial.print("gfromaZ:");
  Serial.print(gfromaZ);
  Serial.print(". ");
  Serial.print("FallDetected:");
  Serial.print(fallDetected);

  Serial.print(". ");
  Serial.print("GyroX:");
  Serial.print(g.gyro.x);
  gyroX = g.gyro.x;
  gyroY = g.gyro.y;
  gyroZ = g.gyro.z;
  Serial.print(",");
  Serial.println("");

  Serial.print("DeltaX:");
  Serial.print(deltaX);
  Serial.print("DeltaY:");
  Serial.print(deltaY);
  Serial.print("DeltaZ:");
  Serial.print(deltaZ);



  memcpy(&buffer[0], &gfromaX, sizeof(float));
  memcpy(&buffer[4], &gfromaY, sizeof(float));
  memcpy(&buffer[8], &gfromaZ, sizeof(float));
  memcpy(&buffer[12], &gyroX, sizeof(float));
  memcpy(&buffer[16], &gyroY, sizeof(float));
  memcpy(&buffer[20], &gyroZ, sizeof(float));



  SerialBT.write(buffer, sizeof(buffer));


  //delay(10);
}
