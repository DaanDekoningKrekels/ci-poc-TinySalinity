#include <Wire.h>                               // Importing the I²C library needed.

#define I2C_SLAVE_ADDRESS 8                     // Setting the slave/client address of the sensor. This needs to match the address set in the sesnor code. Sensors modules you buy often have a fixed address.

#define REQUEST_DELAY 1000                      // Setting the time between measurements in milliseconds, or ms.

int measurement = 0;                            // Variable to keep the measurement value.

void setup() {
  Wire.begin();                                 // Starting the I²C connection. On ESP32 the default is GPIO 22 as SCL line and GPIO 21 as SDA line. You can also configure other pins, but be aware other libraries can overwrite this method, eg. #define I2C_SDA 23 ... #define I2C_SCL 4 ... Wire.begin(I2C_SDA, I2C_SCL);
  Serial.begin(115200);                         // Setting the buadrate speed of the serial connection through the USB-port.
                                                // To visualize the readings from the sensor more clearly we can use the Serial Plotter under Tools in the Arduino IDE. To make the plotter start with values between 0 and 6 V the following lines are recommended.
  Serial.print(0);                              // To freeze the lower limit.
  Serial.print(" ");
  Serial.print(6);                              // To freeze the upper limit.
  Serial.println(" ");
}
void loop() {
  Wire.requestFrom(I2C_SLAVE_ADDRESS, 2);       // Request 2 bytes from the slave/client device, in this case the sensor.

  while (Wire.available()) {                    // Check if there are bytes available to read in the I²C buffer.
    byte high_byte = Wire.read();               // The first byte that is send is the high byte. (Check sensor code for explenation.)
    byte low_byte = Wire.read();                // Second byte available is the low byte.
    measurement = low_byte + ( high_byte << 8); // To get the measurement the high and low byte have to be recombined into the original 16 bit value, eg. high_byte = 1111 1111, low_byte = 1010 1010, hig_byte << 8 = 1111 1111 0000 0000, low_byte + ( high_byte << 8) = 1010 1010 + 1111 1111 0000 0000 = 1111 1111 1010 1010.
    float output = measurement * (5.0f / 1023); // Turn the 0-1023 measurement value into a float from 0.0-5.0 V.
    Serial.println(output, 1);                  // Print float to serial with 1 decimal.
  }
  delay(REQUEST_DELAY);                         // Delay before starting a new loop and starting a new request to make a measurement.
}
