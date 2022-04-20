#include <twi.h>                            // Importing the necessary libraries for I²C communication.
#include <TinyWire.h>                       // #include imports the library code.

#define I2C_SLAVE_ADDRESS 8                 // Setting the Slave/Client address for I²C identification.
                                            // #define replaces the name given with the value given when compiling. On the contrary to using a variable, a #define doesn't use any memory.
#define SENSOR_PIN A3 // ADC3               // Specifing the PIN number to analog read the voltage output value from the sensor.
#define SWITCH_PIN 4                        // Specifing the PIN number to switch on/off the power to the sensor cable to save power.

#define SAMPLE_COUNT 20                     // Amount of sample readings to be done to calculate the average value.
#define SAMPLE_TIME 7                       // Delay time in ms between sample readings.

int measurement = 0;                        // Variable for the final measurment with range 0-1023 or 16 bits.
byte high_byte, low_byte = 0;               // Bytes variables to seperate the measurement. In I²C we can only send one byte or 8 bits at a time, so we have to seperate the measurment into its highbyte and lowbyte.
bool isReadyToSend = false;
bool isRequest = true;

void setup() {                              // setup() is only executed once.
  TinyWire.begin(I2C_SLAVE_ADDRESS);        // Here we tell I²C the slave/client address of this device, so a master/host device can specify this device by address. Works comparable to an IP address on a WiFi network.
  TinyWire.onRequest(requestEvent);         // Here we set a callback function that will be axecuted when a request from a master/host device is received.
  pinMode(SENSOR_PIN, INPUT);               // The sensor data needs to be read, so this is an INPUT.
  pinMode(SWITCH_PIN, OUTPUT);              // The switch has to be set HIGH or LOW to turn on/off the probe, so this is an OUPUT.
  digitalWrite(SWITCH_PIN, HIGH);           // 
}
void loop() {                               // loop() will be executed continuasly, like a while(true) loop.
  if(isRequest){
    //digitalWrite(SWITCH_PIN, HIGH);       
    //delay(500);
    isReadyToSend = false;
    measurement = 0;                          // measurment to 0 to make sure the value is reset.
    for (byte i = 0; i < SAMPLE_COUNT; i++)   // Start sample loop
    {
      delay(SAMPLE_TIME);
      measurement += analogRead(SENSOR_PIN); // Read current voltage and add it to measurement
    }
    //digitalWrite(SWITCH_PIN, LOW);
    measurement = measurement / SAMPLE_COUNT; // Calculate the avarage value from all samples.
    isReadyToSend = true;                     // Measurement is ready to be send.
    isRequest = false;                        // Request flag is reset.
  }
}

void requestEvent() {
  isRequest = true;                           // Every time a request is received a new measurement will be made by setting the request flag.
  
  if(isReadyToSend){                          // If the measurement in the loop is completed the measurement can be send.
    high_byte = measurement >> 8;             // The 8 bits at the high end are shifted down to be saved as a byte, eg 1111 1111 0000 0000 >> 8 == 0000 0000 1111 1111, so the 1's are saved to the byte instead of the 0's.
    low_byte = measurement & 255;             // 255 decimal = 1111 1111 binary. The &-symbol indicates to read these bits from the measuremnt, so only the lowest 8 bits, or low byte, are read. 255 decimal can also be written in code as 0b11111111.
    TinyWire.write(high_byte);                // Sending the high byte of the measurement.
    TinyWire.write(low_byte);                 // Sending the low byte of the measurement.
  }
}
