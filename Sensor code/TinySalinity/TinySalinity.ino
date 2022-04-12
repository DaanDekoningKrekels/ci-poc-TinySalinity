#include <twi.h>
#include <TinyWire.h>
#define I2C_SLAVE_ADDRESS 8

#define SENSOR_PIN A3 // ADC3
#define SWITCH_PIN 4

#define SAMPLE_COUNT 20 
#define SAMPLE_TIME 7 // In ms

int measurement = 0;
byte high_byte, low_byte = 0;

void setup() {
  TinyWire.begin(I2C_SLAVE_ADDRESS);
  TinyWire.onRequest(requestEvent);
  pinMode(SENSOR_PIN, INPUT);
  pinMode(SWITCH_PIN, OUTPUT);
}
void loop() {
  // Empty
}

void requestEvent() {
  digitalWrite(SWITCH_PIN, HIGH); // Measuering ON
  delay(1000);
  
  measurement = 0;
  for (byte i = 0; i < SAMPLE_COUNT; i++)
  {
    delay(SAMPLE_TIME);
    measurement += analogRead(SENSOR_PIN); // Read current voltage and add it to measurement
  }
  measurement = measurement / SAMPLE_COUNT; // Calculate the avarage
  
  high_byte = measurement >> 8;
  low_byte = measurement & 255;
  TinyWire.write(high_byte);
  TinyWire.write(low_byte);

  delay(200);
  digitalWrite(SWITCH_PIN, LOW);  // Measuring OFF
}
