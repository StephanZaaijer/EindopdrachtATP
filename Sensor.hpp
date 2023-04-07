#ifndef SENSOR_HPP
#define SENSOR_HPP

#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

#include "Actuator.hpp"

#ifdef RPI
    #include <wiringPi.h>
#endif

class Sensor {
public:
    Sensor( const int& iDataPin = 0,
            const float& fLowestValue = 100.0f,
            const float& fHighestValue = 100.0f,
            const float& fSensorMin = 0.0f,
            const float& fSensorMax = 5.00f );
    virtual float getValue();

private:
    int miDataPin;
    float mfLowestValue;
    float mfHighestValue;
    float mfSensorMin;
    float mfSensorMax;
};

class TestSensor : public Sensor {
public:
    TestSensor( const float& fLastValue, const float& fMaxDifference, const float& fMinValue, const float& fMaxValue, const float& fDefaultDecay, const float &fMaxActuatorChange, const Actuator& actuator);
    float getValue() override;
    void setValue(const float& fValue);
    void setMaxDifference(const float& fMaxDifference);

private:
    float mfLastValue;
    float mfMaxDifference;
    float mfMinValue;
    float mfMaxValue;
    float mfDefaultDecay;
    float mfMaxActuatorChange;
    const Actuator& mActuator;
};

#endif // SENSOR_HPP