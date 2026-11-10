#include <Wire.h>

const uint8_t MPU_ADDR = 0x68;
const uint8_t REG_PWR_MGMT_1 = 0x6B;
const uint8_t REG_ACCEL_XOUT_H = 0x3B;

int16_t readInt16() {
  uint8_t hi = Wire.read();
  uint8_t lo = Wire.read();
  return (int16_t)((hi << 8) | lo);   // signed 16-bit
}

void setup() {
  Serial.begin(115200);
  Wire.begin(4,5);
  Wire.beginTransmission(MPU_ADDR);   // chip starts asleep: write 0 to wake it
  Wire.write(REG_PWR_MGMT_1);
  Wire.write(0);
  Wire.endTransmission(true);
}

void loop() {
  Wire.beginTransmission(MPU_ADDR);
  Wire.write(REG_ACCEL_XOUT_H);
  Wire.endTransmission(false);
  if (Wire.requestFrom((uint8_t)MPU_ADDR, (uint8_t)14, (uint8_t)true) != 14) {
    Serial.println("read failed");
    delay(500);
    return;
  }
  int16_t ax = readInt16();
  int16_t ay = readInt16();
  int16_t az = readInt16();
  readInt16();                         // temperature, skipped today
  int16_t gx = readInt16();
  int16_t gy = readInt16();
  int16_t gz = readInt16();

  Serial.print(ax); Serial.print(",");
  Serial.print(ay); Serial.print(",");
  Serial.print(az); Serial.print(",");
  Serial.print(gx); Serial.print(",");
  Serial.print(gy); Serial.print(",");
  Serial.println(gz);
  delay(100);
}