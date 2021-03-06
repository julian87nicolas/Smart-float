# Smart float

Control for the PH level of a pool and alert if there is a problem.

That repo contains:
* All the necessary code
* STL files for the 3D model print
* PCB diagram for the electronic circuit.

# Introduction

It is an intelligent float, which through WiFi connection provides data from its sensors to a database Crate, which manages alerts and historical values. In addition, by obtaining the local time using a NTP server performs daily the addition of the chlorine measurement corresponding to the volume of the pool.


The creation of the entities, sensors and their registration to QuantumLeap is done automatically through of the microcontroller used, once the WiFi connection is made. The latter is done by using
of the "WiFiManager.h" library which allows a connection through any WiFi device to the microcontroller to provide SSID and Password of the desired WiFi network.

As an additional item to highlight, in the realization of the microcontroller code to perform all these functions, it was aided by the recently released “GitHub Copilot” tool, which saved a lot of time in the development of the project.

# Component list
* ESP8266 – NodeMCU v1.0
* UV radiation sensor – GUVA-S12SD
* Submersible temperature sensor – DS18B20
* Mini servo motor – SG90
* Solar panel – 5v 220 mAh
* Powerbank – 2500mAh
* Generic pool buoy
* Crate database

# Funcionalities
* Water temperature measurement
* UV radiation measurement
* Tracking and mobile alerts via Telegram
* Water care through chlorine powder
* Rechargeable battery by Solar Panel

# Images 3D parts of the project
<div style="display:flex; justify-content:center;">
    <img src="photos/base-stl.png">
    <img src="photos/servo-hel.png">
    <img src="photos/cover-float.png">
</div>

# Electronic board
It was developed using PCBWizard, placing each component and making each route manually:
<div style="display:flex; justify-content:center;">
    <img src="photos/pcb.png">
</div>
It integrates the connection of the microcontroller, battery, servo and sensors.
Its dimensions are 60x70 mm, a size that fits perfectly inside the buoy used.
Soldered to the board are only female pins, to facilitate the placement and removal of components and the
microcontroller, if necessary.

# Real images of the project
<div style="display:flex; justify-content:center;">
    <img src="photos/servo-real.png">
    <img src="photos/float-real.png">
</div>
# Data handling in Crate using Grafana
To use the sensor data sent by the microcontroller, the Grafana tool was used.
Through this tool, graphics and controls were made through alerts that reach the user through
notifications in the Telegram messaging application through a Bot.

Alerts notify user if pool water temperature and UV radiation index exceed certain limits. The temperature of the water is simply a control by preferences of the user in question. On the other hand the UV radiation index serves as prevention to help avoid possible harmful damage to health. these alerts they also notify the moment in which the sensors indicate acceptable values again, that is, within the specified range.

The graphs made help to quickly observe the most current values of the sensors and at the same time
provide historical data.

The generated graphs are the following:
<div style="display:flex; justify-content:center;">
    <img src="photos/graphana.png">
</div>
Examples of Bot alerts on Telegram:
<div style="display:flex; justify-content:center;">
    <img src="photos/bot-message.png">
</div>