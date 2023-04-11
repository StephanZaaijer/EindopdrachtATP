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
            const float& fLowestValue = -100.0f,
            const float& fHighestValue = 100.0f,
            const float& fSensorMin = 0.0f,
            const float& fSensorMax = 5.00f );
    virtual float getValue();

protected:
    virtual float CalculateValue( const float& fValue ) = 0;
    int miDataPin;
    float mfLowestValue;
    float mfHighestValue;
    float mfSensorMin;
    float mfSensorMax;
};

class TMP36 : public Sensor {
public:
    TMP36( const int& iDataPin = 0 );

protected:
    float CalculateValue( const float& fValue ) override;
    
};

class TMP36TestSensor : public TMP36 {
public:
    TMP36TestSensor( const float& fLastValue, const float& fMaxDifference, const float& fMinValue, const float& fMaxValue, const float& fDefaultDecay, const float &fMaxActuatorChange, const Actuator& actuator);
    float getValue() override;
    void setValue(const float& fValue);

    float CalculateValue( const float& fValue ) override;

private:
    float mfLastValue;
    float mfMaxDifference;
    float mfMinValue;
    float mfMaxValue;
    float mfDefaultDecay;
    float mfMaxActuatorChange;
    const Actuator& mActuator;
};

class PHSensor : public Sensor {
public:
    PHSensor( const int& iDataPin = 0 );

protected:
    float CalculateValue( const float& fValue ) override;
};

class PHSensorTestSensor : public PHSensor {
public:
    PHSensorTestSensor( const float& fLastValue, const float& fMaxDifference, const float& fMinValue, const float& fMaxValue, const float& fDefaultDecay, const float &fMaxActuatorChange, const Actuator& actuator);
    float getValue() override;
    void setValue(const float& fValue);

    float CalculateValue( const float& fValue ) override;

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