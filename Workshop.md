---
marp: true
---

<!--
title: Internet of Things Workshop
theme: gaia
paginate: true
style: | 
  section {
    background-color: #fcf8ed;
  }
-->

# Internet of Things Workshop

## Salinity Sensor Prototype
## ESP32 & I<sup>2</sup>C

![bg](assets/bg.svg)

---

## Salinity Sensor

![bg 90% Salinity Sensor photo](assets/SalinitySensorPhoto.png)
![bg 90% Salinity Sensor photo](assets/SalinitySensorPhoto_back.png)


---

## Salinity Sensor

![bg 95% Salinity Sensor scheme](assets/Scheme-full.svg)


<img alt="Vout=(R4/R3R4)*Vin" src="https://render.githubusercontent.com/render/math?math=V_%7Bout%7D=%7B%5Cfrac%7BR_%7B4%7D%7D%7BR_%7B3%7D&plus;R_%7B4%7D%7D%7D%5Ccdot%20V_%7Bin%7D"/>



<img alt="Vout=(R10/R7)*(V2-V1)" style="float:right" src="https://render.githubusercontent.com/render/math?math=V_%7Bout%7D=%5Cfrac%7BR_10%7D%7BR_7%7D(V_2-V_1)%20"/>


---

## Wheatstone bridge

![bg right 95% Wheatstone bridge scheme](./assets/Scheme-Wheatstone-bridge.svg)

- Two voltage dividers
- <img alt="Vout=(R4/R3R4)*Vin" height="40" src="https://render.githubusercontent.com/render/math?math=V_%7Bout%7D=%7B%5Cfrac%7BR_%7B4%7D%7D%7BR_%7B3%7D&plus;R_%7B4%7D%7D%7D%5Ccdot%20V_%7Bin%7D"/>
- Only enabled when needed

---

## Amplifier

![bg right 95% Amplifier scheme](./assets/Scheme-OPAMP.svg)

- Voltage followers
  - Stable reading
- Differential amplifier
  - <img alt="Vout=(R10/R7)*(V2-V1)" height="40" src="https://render.githubusercontent.com/render/math?math=V_%7Bout%7D=%5Cfrac%7BR_10%7D%7BR_7%7D(V_2-V_1)%20"/>

---

## ATtiny

![bg right 95% ATtiny scheme](./assets/Scheme-ATtiny.svg)

- Reads Amplifier Output
- Moving Average Filter
- Sends Reading Over I<sup>2</sup>C

---

## ESP32 DOIT V1

- Microcontroller
- Arduino + WiFi & Bluetooth
- 30 pins

![bg right fit ESP32 DOIT](./assets/ESP32-DOIT.png)

---

## Setting up the Arduino IDE

1. https://www.arduino.cc/en/software
2. Open "`File` > `Preferences` > `Additional Board Manager URLs`" and add: https://dl.espressif.com/dl/package_esp32_index.json
3. Open the Boards Manager at "`Tools` > `Board` > `Boards Manager`", search for "ESP32" and press the install button for "ESP32 by Espressif Systems"


---

## Testing Arduino IDE

1. Select "`DOIT ESP32 DEVKIT V1`" at "`Tools` > `Board`"
2. Select the correct COM port under "`Tools` > `Port`"
3. Choose an example program in "`File` > `Examples` > `Examples for DOIT ESP32 DEVKIT V1` > `WiFi` > `WiFiScan`" 
4. Program the code to the ESP32 with the Upload button (&#10145;)
5. Open the Serial Monitor via "`Tools` > `Serial Monitor`" and set the Baud-rate to "115200 baud"
6. If you can see the nearby WiFi networks everything is working!


<footer>
Source: https://microcontrollerslab.com/install-esp32-arduino-ide/
</footer>

---

## Soldering the Salinity Sensor

![bg 95% Salinity Sensor photo](assets/SalinitySensorPhoto.png)
![bg 95% Salinity Sensor photo](assets/SalinitySensorPhoto_back_traced.png)


---

![bg 70% Component placement](assets/SalinitySensorComponentPlacement.png)

---


# Connecting to the Salinity Sensor

## Using I<sup>2</sup>C and an ESP32

---

## I<sup>2</sup>C

- I<sup>2</sup>C = Inter-Integrated Circuit
- Invented in 1982 by Philips 
- SDA = Serial Data Line
- SCL = Serial Clock Line
- Every target has his own address
''
![bg right fit I2C example connection](./assets/I2C_controller-target.svg)

---

![bg fit 98% Salinity Sensor connected to ESP32](./assets/SalinitySensorToESP32.png)

---

## Send to serial monitor

```C++
void setup() {
  // put your setup code here, to run once:

}

void loop() {
  // put your main code here, to run repeatedly:

}
```

---

## Send to serial monitor

```C++
void setup() {
  Serial.begin(115200); // Open the serial port at 115200 baud
}

/* Send "Salamu, Dunia!" via serial every second. */
void loop() {
  Serial.println("Salamu, Dunia!"); // Send text over the serial port
  delay(1000); // Wait 1000ms or 1s
}
```
