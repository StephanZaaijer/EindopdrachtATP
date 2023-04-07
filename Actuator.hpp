#ifndef ACTUATOR_HPP
#define ACTUATOR_HPP

#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

#ifdef RPI
    #include <wiringPi.h>
#else
    #include <iostream>
#endif

class Display {
public:
    #ifdef RPI
        Display( i2cstream& displayStream );
    #else
        Display();
    #endif
    void WriteString( const std::string& sString );

private:
    #ifdef RPI
        i2cstream& mDisplayStream;
    #endif

};

class Actuator {
public:
    Actuator(const int& iControlPin, const float& fPower);
    void SetPowervalue(const float& fPower);
    float GetPowervalue() const;
protected:
    int miControlPin;
    float mfPower;
};

class Heater: public Actuator {
public:
    Heater(const int& iControlPin, const float& fPower);
};

class Dispensor: public Actuator {
public:
    Dispensor(const int& iControlPin, const float& fPower);
};



#endif // ACTUATOR_HPP