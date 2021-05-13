VICS AFR for 2000 NB miata

Wideband AFR sensor conversion to narrowband. 
Motivation:
1.6L to 1.8L conversion with WB AFR Bosch sensor to regulate closed loop operation and VICS butterfly operation without an expensive RPM switch or aftermarket ECU.

VICS operation:
VICS, Variable Inertia Charging System/Solenoid, the details of the acrynym are limited at best. Torque curves provided by mazda describe butterfly valves opening at ~5000 rpm to a resonence chamber that counteracts torque loss at high RPM.


AFR conversion:
Fairly simple process, take a .5v-4.5v signal from the Bosch WB and convert it to a 0-1v signal to be used by the original ECU. 
Arduino Uno was used as a cheap easy to use platform to sense the voltage and output an inverted 0-1v signal wired into the ECU. 

