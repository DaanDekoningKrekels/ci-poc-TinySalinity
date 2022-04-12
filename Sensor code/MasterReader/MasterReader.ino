#include <Wire.h>

#define I2C_SLAVE_ADDRESS 8

int measurement = 0;

void setup() {
  Wire.begin();
  Serial.begin(57600);
  Serial.print(0);      // To freeze the lower limit
  Serial.print(" ");
  Serial.print(1024);      // To freeze the upper limit
  Serial.println(" ");
}

void loop() {
  Wire.requestFrom(I2C_SLAVE_ADDRESS, 2); // Request 1 byte

  while (Wire.available()) {
    byte high_byte = Wire.read();
    byte low_byte = Wire.read();
    measurement = low_byte + ( high_byte << 8);
    Serial.println(measurement);
    //Serial.println(output, 1);  // print float with 1 decimal
  }
  delay(1000);
}
