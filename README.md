# Salinity Sensor

![ATtiny scheme](./assets/Scheme-full.svg)

This sensor reports the relative change in salinity (conductivity) of water.

You can find the Workshop document [here](./Workshop.md).

It uses a probe, an OPAMP and an ATtiny.

The salinity sensor probe exists out of two electrodes that are positioned within a certain distance of each other. The distance is not critical because you can calibrate the sensor for a specific probe. Depending on the use case some distances might work better. With the electrodes under water there will flow a certain amount of current. When there is more salt, the resistance of the water will be lower so more current will be able to flow.

We will be using a Wheatstone bridge with on one side the probe and on the other side a fixed (but adjustable) resistance. The two sides of the Wheatstone bridge are voltage dividers, on one side the voltage will change depending on the amount of salt, the other one is calibrated and will give a fixed voltage.
The two outputs from the Wheatstone bridge are connected to a differential amplifier which will output a voltage proportional to the voltage difference on the inputs. 

An ATtiny will, on request, read the output voltage of the differential amplifier and send it over I2C. 



## Wheatstone bridge

![Wheatstone bridge scheme](./assets/Scheme-Wheatstone-bridge.svg)

A [Wheatstone bridge](http://www.ibiblio.org/kuphaldt/electricCircuits/DC/DC_8.html#xtocid96509) can be used to determine the value of an unknown resistance. In this case the unknown resistance is the resistance measured on the probe (R4). On the other side of the bridge a variable resistor (R6) is used to calibrate the Wheatstone bridge. When calibrating the bridge the value of R6 will be set to a value where the output of the sensor is in the middle of the reading window. When the conductivity of the water changes, the output of the sensor will be able to increase or decrease accordingly.
The voltage on point A and point B can be calculated with the following formula. <!-- $V_{out}={\frac{R_{4}}{R_{3}+R_{4}}}\cdot V_{in}$ --> <img style="transform: translateY(0.1em); background: white;" src="https://render.githubusercontent.com/render/math?math=V_%7Bout%7D%3D%7B%5Cfrac%7BR_%7B4%7D%7D%7BR_%7B3%7D%2BR_%7B4%7D%7D%7D%5Ccdot%20V_%7Bin%7D">

Q1 is an N-channel E-[MOSFET](https://byjus.com/physics/mosfet/) which is used to enable or disable power to the Wheatstone bridge. You can look at a MOSFET like an electric switch. When a voltage is applied to the Gate (middle pin) the switch is closed (*saturation mode*) and current can flow, when no voltage is applied the switch is open (*cutoff mode*) and no current will be able to flow. When 5V is applied to the `BRIDGE_ENABLE` pin the MOSFET will conduct and power the Wheatstone bridge, the MOSFET is in *saturation mode*. When no voltage is applied the MOSFET will be in *cutoff mode* and the Wheatstone bridge is disabled.
 

## Operational Amplifier (OPAMP)

![Amplifier scheme](./assets/Scheme-OPAMP.svg)

For reading the Wheatstone bridge, an LM324 or TL074 OPAMP is used. An [OPAMP](https://www.allaboutcircuits.com/textbook/semiconductors/chpt-8/introduction-operational-amplifiers/) is actually a voltage amplifying device. By connecting resistors in the right way we can change the way the amplification works. The two OPAMP chips mentioned above have 4 usable amplifiers in the same package. The two midpoints of the Wheatstone bridge first go through a voltage follower. A [voltage follower](http://learningaboutelectronics.com/Articles/Voltage-follower) acts as a buffer and has a very high input impedance and a very low output impedance. These characteristics are very useful to give a reliable signal to the differential amplifier. A high input impedance will result in a low current flow from the Wheatstone bridge thus almost no voltage drop (decrease of voltage because the load is to high) will appear. A low output impedance makes the voltage follower ideal to read the voltage from.
A [differential amplifier](https://www.electronics-tutorials.ws/opamp/opamp_5.html) outputs a voltage proportional to the difference in voltage from its two inputs. R3 / R1 in the following formula is the differential gain and by changing these values we can change the sensitivity of the sensor. The two inputs of the differential amplifier get subtracted from each other and then multiplied with the value of R3 / R1. Changing the multiplication value changes the sensitivity.

<!-- $V_{out}=\frac{R_10}{R_7}(V_2-V_1)$ --> <img style="transform: translateY(0.1em); background: white;" src="https://render.githubusercontent.com/render/math?math=V_%7Bout%7D%3D%5Cfrac%7BR_10%7D%7BR_7%7D(V_2-V_1)">

          
Connected to the differential amplifier we have another voltage follower to give reliable readings to the ATtiny.

## ATtiny

![ATtiny scheme](./assets/Scheme-ATtiny.svg)

An [Atmel ATtiny MCU](https://www.microchip.com/en-us/product/ATtiny85) will be used to read the output of the sensor and send it to another device, for example an ESP32 or Arduino. The ATtiny has a 10bit ADC (Analog to Digital Converter) which will be used to read the output voltage of the OPAMP. The ADC maps the input voltage to a number between 0 and 1024 where 1024 is 5V. To make the measurements more reliable a moving average filter is implemented on the ATtiny which outputs the average of a series of ADC readings. 
[I2C](https://www.circuitbasics.com/basics-of-the-i2c-communication-protocol/) is the communication protocol that will be used to communicate with the ATtiny. <br/>
See [Sensor code](./Sensor%20code/) for more details on the ATtiny and the code.

## Prototype

The current prototype of this board is made on a perfboard. This is a more stable way of testing than using a breadboard. There are three working prototype boards made by the students of KIST in our [workshop](./Workshop.md).

![Salinity Sensor prototype photo](assets/SalinitySensorPhoto.png)



