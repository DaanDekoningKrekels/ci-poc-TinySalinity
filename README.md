# Salinity Sensor

This sensor reports the relative change in salinity (conductivity) of water.
It uses a probe, a OPAMP and an ATtiny.

The salinity sensor probe exists out of two electrodes who are positioned with a certain distance between each other. With the electrodes under water there will flow a certain amount of current. When there is more salt, the resistance of the water will be lower so more current will flow though.

We will be using a Wheatstone bridge with on one side the probe and on the other side a fixed (but adjustable) resistance. The two sides of the Wheatstone bridge are two voltage dividers, on one side the voltage will change depending on the amount of salt, the other one is calibrated and will give a fixed voltage.
The two outputs of the Wheatstone bridge are connected to a differential amplifier which will output a voltage proportional to the voltage difference on the inputs. 

An ATtiny will, on request, read the output voltage of the differential amplifier and send it over I2C. 
