#include "Sensor.hpp"
#include <iostream>

Sensor::Sensor( const int &iDataPin, const float& fLowestValue, const float& fHighestValue, const float& fSensorMin, const float& fSensorMax ):
    miDataPin(iDataPin),
    mfLowestValue(fLowestValue),
    mfHighestValue(fHighestValue),
    mfSensorMin(fSensorMin),
    mfSensorMax(fSensorMax)
{
    #ifdef RPI
        pinMode(iDataPin, INPUT);
    #endif
}

float Sensor::getValue()
{  
    #ifdef RPI
        return CalculateValue( analogRead(miDataPin) );
    #else
        return 0.0f;
    #endif
}

TMP36::TMP36( const int& iDataPin )
    : Sensor(iDataPin, -40.0f, 125.0f, 2.7f, 5.5f)
{}

float TMP36::CalculateValue( const float& fValue )
{
    // # Calculate the temperature in degrees Celsius
    return ((mfHighestValue - mfLowestValue) / (mfSensorMax - mfSensorMin)) * fValue + mfLowestValue - ((mfHighestValue - mfLowestValue) / (mfSensorMax - mfSensorMin)) * mfSensorMin;
}

TMP36TestSensor::TMP36TestSensor( const float& fLastValue, const float& fMaxDifference, const float& fMinValue, const float& fMaxValue, const float& fDefaultDecay, const float &fMaxActuatorChange, const Actuator& actuator):
    TMP36(0),
    mfLastValue(fLastValue),
    mfMaxDifference(fMaxDifference),
    mfMinValue(fMinValue),
    mfMaxValue(fMaxValue),
    mfDefaultDecay(fDefaultDecay),
    mfMaxActuatorChange(fMaxActuatorChange),
    mActuator(actuator)
    {}
    
float TMP36TestSensor::getValue()
{
    mfLastValue -= mfDefaultDecay;
    mfLastValue += mfMaxActuatorChange * mActuator.GetPowervalue()/100;
    float value = mfLastValue - mfMaxDifference/100* ((rand() % 200) - 100);
    if (value < mfMinValue)
        value = mfMinValue;
    if (value > mfMaxValue)
        value = mfMaxValue;
    return value;
}

void TMP36TestSensor::setValue(const float &fValue)
{
    mfLastValue = fValue;
}

float TMP36TestSensor::CalculateValue( const float& fValue )
{
    return TMP36::CalculateValue(fValue);
}

PHSensor::PHSensor( const int& iDataPin )
    : Sensor(iDataPin, 0.0f, 14.0f, 0.0f, 5.0f)
{}

float PHSensor::CalculateValue( const float& fValue )
{
    // Source for the formula https://www.elecrow.com/wiki/index.php?title=Crowtail-_PH_Sensor
    return 7-1000*(fValue*100-365)*4.95/59.16/1023;
}

PHSensorTestSensor::PHSensorTestSensor( const float& fLastValue, const float& fMaxDifference, const float& fMinValue, const float& fMaxValue, const float& fDefaultDecay, const float &fMaxActuatorChange, const Actuator& actuator):
    PHSensor(0),
    mfLastValue(fLastValue),
    mfMaxDifference(fMaxDifference),
    mfMinValue(fMinValue),
    mfMaxValue(fMaxValue),
    mfDefaultDecay(fDefaultDecay),
    mfMaxActuatorChange(fMaxActuatorChange),
    mActuator(actuator)
    {}

float PHSensorTestSensor::getValue()
{
    mfLastValue -= mfDefaultDecay;
    mfLastValue += mfMaxActuatorChange * mActuator.GetPowervalue()/100;
    mfLastValue -= mfMaxDifference/100* ((rand() % 200) - 100);
    if (mfLastValue < mfMinValue)
        mfLastValue = mfMinValue;
    if (mfLastValue > mfMaxValue)
        mfLastValue = mfMaxValue;
    return mfLastValue;
}

void PHSensorTestSensor::setValue(const float &fValue)
{
    mfLastValue = fValue;
}

float PHSensorTestSensor::CalculateValue( const float& fValue )
{
    return PHSensor::CalculateValue(fValue);
}