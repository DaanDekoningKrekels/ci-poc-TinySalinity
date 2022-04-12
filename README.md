### Salinity Sensor

[Ref1](https://me121.mme.pdx.edu/lib/exe/fetch.php?media=lecture:salinity_measurements_with_arduino_slides.pdf), [Ref2](https://www.teachengineering.org/activities/view/nyu_probe_activity1), [Ref3](https://hackaday.io/project/6444-vinduino-a-wine-growers-water-saving-project/log/26710-salinity-measurement), [Lib1](https://www.arduino.cc/reference/en/libraries/conductivitylib/)

De zoutsensor bestaat uit twee elektrodes die op een bepaalde afstand van elkaar liggen. Onder water zal, afhankelijk van de hoeveelheid zout er meer of minder stroom kunnen vloeien. Bij een constante stroom door de elektrodes zullen ze sneller verslijten dus zullen we de polariteit wisselen tussen twee digitale pinnen.

De polariteit kan gewisseld worden door een blokgolf langs de elektrode te laten variëren of door een sinus aan te leggen aan de sensor.

https://www.sparkyswidgets.com/portfolio-item/miniec-i2c-ec-interface/

https://github.com/SparkysWidgets/MinieCHW/blob/master/MinieCV1_2.pdf

We maken een brug van Wheatstone en versterken het verschilsignaal met een instrumentatieversterker. (zie videopresentatie verschilversterking - instrumentatieversterker .pdf) 

$u_{i n 1}=\frac{R_{var}}{R+R_{var}} \times U_{in}=\frac{11 k \Omega}{10 k \Omega+11 k \Omega} \times 5 V=2,62 V$

$u_{1}=u_{i n 1}-I \cdot R_{1}$
$u_{2}=u_{i n 2}+I \cdot R_{1}$
$u_{u i t}=u_{2}-u_{1}$
$u_{u i t}=u_{i n 2}+I \cdot R_{1}-\left(u_{i n 1}-I \cdot R_{1}\right)$
$u_{u i t}=u_{i n 2}-u_{i n 1}+2 I \cdot R_{1}$

$I=\frac{u_{i n 2}-u_{i n 1}}{R_{2}}$

$A_{u}=\frac{u_{u i t}}{u_{i n 2}-u_{i n 1}}=1+2 \frac{R_{1}}{R_{2}}$




 
#   c i - p o c - T i n y S a l i n i t y  
 