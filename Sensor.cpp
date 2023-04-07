#include "Sensor.hpp"

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
        float fValue = analogRead(miDataPin);
        return  (fValue - miSensorMin) * (mfHighestValue - mfLowestValue) / (miSensorMax - miSensorMin) + mfLowestValue;
    #else
        return 0.0f;
    #endif
}

TestSensor::TestSensor( const float& fLastValue, const float& fMaxDifference, const float& fMinValue, const float& fMaxValue, const float& fDefaultDecay, const float &fMaxActuatorChange, const Actuator& actuator):
    mfLastValue(fLastValue),
    mfMaxDifference(fMaxDifference),
    mfMinValue(fMinValue),
    mfMaxValue(fMaxValue),
    mfDefaultDecay(fDefaultDecay),
    mfMaxActuatorChange(fMaxActuatorChange),
    mActuator(actuator)
    {}
    
float TestSensor::getValue()
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

void TestSensor::setValue(const float &fValue)
{
    mfLastValue = fValue;
}

void TestSensor::setMaxDifference(const float &fMaxDifference)
{
    mfMaxDifference = fMaxDifference;
}