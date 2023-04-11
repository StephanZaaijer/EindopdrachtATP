# Final exercise ATP

## Setup
To use the code in this repository you must clone this repository and it's submodule. You can than run the makefile to compile the pybind module and run the code. ( This makefile has been tested on linux, it has not been tested on Windows and MacOS yet )

## Criteria
### Implementatie
Het controlesyseem bevat 2 sensoren en 3 actuatoren
* Sensoren
    * PH-sensor
    * Temperatuursensor
* Actuator
    *  Display
    * Verwarmingselement
    * PH-beïnvloedende dispensor

Daarnaast zijn de mainloop en PID-controller functioneel geschreven

### Aspect-oriented decorator
Er is in atp.py een logging-decorator geschreven
( werkt met python-functies, zover bekend alleen niet met pybind-functies )

### Python-C++ binding
In Pythonmodule.cpp is geimplementeerd:
* Display
* (Abstracte) actuator-klasse
* Heater
* Dispensor
* PID
* (abstracte) sensor-klasse
* TMP36 (temperatuursensor)
* TMP36TestSensor
* PHSensor
* PHSensorTestSensor

### Test uitvoer en reflectie
Test rapportage is toegevoegd in Testverslag.pdf en de testen zijn beschikbaar in APT_unittest.py

### Simulator (optioneel)
De systeemtest is een volledige simulatie van het systeem en in ATP.py.
Daarbij kan er gekozen worden voor verschillende PID-controllers ( c++ / functioneel ) en met wisselend setpoint of niet dit kan met behulp van de variabelen FUNCTIONAL_PID_VERSION en SWITCHING_TARGET_VALUE. Mogelijke combinaties:
FUNCTIONAL_PID = True en SWITCHING_TARGET_VALUE = True                             functionele pid met wisselend setpoint
FUNCTIONAL_PID = True en SWITCHING_TARGET_VALUE = False                            functionele pid met fixed setpoint
FUNCTIONAL_PID = False en SWITCHING_TARGET_VALUE = *                               C++ PID met fixed setpoint
