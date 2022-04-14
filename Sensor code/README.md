# TinySalinity MCU

The Atmel ATTiny 85 microcontroller will read the value of the sensor and send it to the main microcontroller via I²C. The main MCU can send this data to a server for example.

## Programming the ATTiny

Firstly we will have to add the ATTiny to our Arduino IDE. 
In the Arduino IDE, go to `File` -> `Preferences` and add the following url to `Additional Boards Manager URLs` and save with `Ok`.
`https://raw.githubusercontent.com/damellis/attiny/ide-1.6.x-boards-manager/package_damellis_attiny_index.json`
To install the ATTiny board, got to `Tools` -> `Board:` and choose `Board Manager` Scroll down until you see `attiny by David A. Mellis`. Click on the `Install` button.

### The Bootloader

If the ATTiny is still new there won't be any bootloader installed. We need a bootloader to be able to put our code on the ATTiny.
Follow this guide to burn the bootloader to your ATTiny.
https://create.arduino.cc/projecthub/arjun/programming-attiny85-with-arduino-uno-afb829



### The Program

You can find the program in the `TinySalinity.ino` file. The ATTiny will send its measurements over I²C on request.

#### Parameters
In the ATtiny code is it possible to play with a few parameters. Change these to the preferred values.

```C++
// Default parameter values
#define I2C_SLAVE_ADDRESS 8

#define SAMPLE_COUNT 20
#define SAMPLE_TIME 7
```

`I2C_SLAVE_ADDRESS` can be changed to any address between 8 and 119. Every slave device connected to the same master should have a unique address.

The moving average filter uses `SAMPLE_COUNT` and `SAMPLE_TIME`.

`SAMPLE_COUNT` describes how much readings have to be done before calculating the average of those readings.
`SAMPLE_TIME` is the time in milliseconds between every reading.


## Sources

https://gammon.com.au/i2c
