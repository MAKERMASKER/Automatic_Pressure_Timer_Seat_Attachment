
#include "mpu9250.h"
#include<Wire.h>

///* An Mpu9250 object with the MPU-9250 sensor on I2C bus 0 with address 0x68 */
//Mpu9250 imu(&Wire, 0x68);
//int status;

const int MPU_addr=0x68;
int16_t AcX,AcY,AcZ,Tmp,GyX,GyY,GyZ;
 
int minVal=265;
int maxVal=402;
 
double x;
double y;
double z;

void setup() {
  /* Serial to display data */
//  Serial.begin(115200);
//  while(!Serial) {}
//  /* Start communication */
//  if (!imu.Begin()) {
//    Serial.println("IMU initialization unsuccessful");
//    while(1) {}

Wire.begin();
Wire.beginTransmission(MPU_addr);
Wire.write(0x6B);
Wire.write(0);
Wire.endTransmission(true);
Serial.begin(9600);
  }
//}

void loop() {
//  /* Read the sensor */
//  if (imu.Read()) {
//    /* Display the data */
//    Serial.print(imu.accel_x_mps2(), 6);
//    Serial.print("\t");
//    Serial.print(imu.accel_y_mps2(), 6);
//    Serial.print("\t");
//    Serial.print(imu.accel_z_mps2(), 6);
//    Serial.print("\t");
//    Serial.print(imu.gyro_x_radps(), 6);
//    Serial.print("\t");
//    Serial.print(imu.gyro_y_radps(), 6);
//    Serial.print("\t");
//    Serial.print(imu.gyro_z_radps(), 6);
//    Serial.print("\t");
//    Serial.print(imu.mag_x_ut(), 6);
//    Serial.print("\t");
//    Serial.print(imu.mag_y_ut(), 6);
//    Serial.print("\t");
//    Serial.print(imu.mag_z_ut(), 6);
//    Serial.print("\t");
//    Serial.println(imu.die_temperature_c(), 6);
//  }
//  delay(100);

Wire.beginTransmission(MPU_addr);
Wire.write(0x3B);
Wire.endTransmission(false);
Wire.requestFrom(MPU_addr,14,true);
AcX=Wire.read()<<8|Wire.read();
AcY=Wire.read()<<8|Wire.read();
AcZ=Wire.read()<<8|Wire.read();
int xAng = map(AcX,minVal,maxVal,-90,90);
int yAng = map(AcY,minVal,maxVal,-90,90);
int zAng = map(AcZ,minVal,maxVal,-90,90);

x= RAD_TO_DEG * (atan2(-yAng, -zAng)+PI);
y= RAD_TO_DEG * (atan2(-xAng, -zAng)+PI);
z= RAD_TO_DEG * (atan2(-yAng, -xAng)+PI);
 
Serial.print("AngleX= ");
Serial.println(x);
 
Serial.print("AngleY= ");
Serial.println(y);
 
Serial.print("AngleZ= ");
Serial.println(z);
Serial.println("-----------------------------------------");
delay(400);
}
