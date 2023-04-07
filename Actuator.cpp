#include "Actuator.hpp"

#ifdef RPI
    Display::Display( i2cstream &displayStream ):
        mDisplayStream(displayStream)
    {}
#else
    Display::Display()
    {}
#endif

void Display::WriteString( const std::string& sString )
{
    #ifdef RPI
        mDisplayStream << sString;
    #else
        std::cout << sString;
    #endif
}

Actuator::Actuator( const int& iControlPin, const float& fPower ):
    miControlPin(iControlPin),
    mfPower(fPower)
{
    #ifdef RPI
        pinMode(miControlPin, OUTPUT);
        analogWrite(miControlPin, mfPower);
    #endif
}


void Actuator::SetPowervalue(const float& fPower)
{
    mfPower = fPower;
    if (mfPower > 100)
        mfPower = 100;
    if (mfPower < 0)
        mfPower = 0;
    #ifdef RPI
        analogWrite(miControlPin, mfPower*2.55);
    #endif
}

float Actuator::GetPowervalue() const
{
    return mfPower;
}

Heater::Heater( const int& iControlPin, const float& fPower ):
    Actuator(iControlPin, fPower)
{}

Dispensor::Dispensor( const int& iControlPin, const float& fPower ):
    Actuator(iControlPin, fPower)
{}