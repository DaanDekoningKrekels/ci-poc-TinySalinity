#include <Wire.h>                               // Importing the I²C library needed.

#define I2C_SLAVE_ADDRESS 8                     // Setting the slave/client address of the sensor. This needs to match the address set in the sesnor code. Sensors modules you buy often have a fixed address.

#define LED_TEST 2                              // Using the onboard LED on D2/GPIO2 for test feedback.
#define BTN_SEND 23                             // Using a button on D23/GPIO23 to send the measurement over LoRaWAN on button press.

#define REQUEST_DELAY 5000                     // Setting the time between measurements in milliseconds, or ms.

int measurement = 0;                            // Variable to keep the measurement value.

void blinkTest(int duration = 100){
  digitalWrite(LED_TEST, HIGH);
  delay(duration);
  digitalWrite(LED_TEST, LOW);
}

void setup() {
  pinMode(LED_TEST, OUTPUT);                    // Setting the LED pin to OUTPUT.
  pinMode(BTN_SEND, INPUT);                     // Setting the BUTTON pin to INPUT.

  Wire.begin();                                 // Starting the I²C connection. On ESP32 the default is GPIO 22 as SCL line and GPIO 21 as SDA line. You can also configure other pins, but be aware other libraries can overwrite this method, eg. #define I2C_SDA 23 ... #define I2C_SCL 4 ... Wire.begin(I2C_SDA, I2C_SCL);
  Serial.begin(115200);                         // Setting the buadrate speed of the serial connection through the USB-port.
                                                // To visualize the readings from the sensor more clearly we can use the Serial Plotter under Tools in the Arduino IDE. To make the plotter start with values between 0 and 6 V the following lines are recommended.
  Serial.print(0);                              // To freeze the lower limit.
  Serial.print(" ");
  Serial.print(6);                              // To freeze the upper limit.
  Serial.println(" ");
  blinkTest(1000);
}
void loop() {
  blinkTest(); delay(100);                      // 1 blink to indicate the start of the loop.
  
  // Measuering
  Wire.requestFrom(I2C_SLAVE_ADDRESS, 2);       // Request 2 bytes from the slave/client device, in this case the sensor.
  
  while (Wire.available()) {                    // Check if there are bytes available to read in the I²C buffer.
    byte high_byte = Wire.read();               // The first byte that is send is the high byte. (Check sensor code for explenation.)
    byte low_byte = Wire.read();                // Second byte available is the low byte.
    measurement = low_byte + ( high_byte << 8); // To get the measurement the high and low byte have to be recombined into the original 16 bit value, eg. high_byte = 1111 1111, low_byte = 1010 1010, hig_byte << 8 = 1111 1111 0000 0000, low_byte + ( high_byte << 8) = 1010 1010 + 1111 1111 0000 0000 = 1111 1111 1010 1010.
    float output = measurement * (5.0f / 1023); // Turn the 0-1023 measurement value into a float from 0.0-5.0 V.
    Serial.print(measurement); Serial.print(" = "); Serial.print(output, 1); Serial.println(" V");  // Print values to serial.
    blinkTest(); delay(100); blinkTest();       // 2 blinks to indicate a read.
  }

  // LoRaWAN Sending
  // ...
  
  delay(REQUEST_DELAY);                         // Delay before starting a new loop and starting a new request to make a measurement.
}
