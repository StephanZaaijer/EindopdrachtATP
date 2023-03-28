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

Relais::Relais( const int& iControlPin, const bool& bState):
    miControlPin(iControlPin),
    mbState(bState)
{
    #ifdef RPI
        pinMode(miControlPin, OUTPUT);
        digitalWrite(miControlPin, bState);
    #endif
}


void Relais::SetState(const bool& bState)
{
    #ifdef RPI
        digitalWrite(miControlPin, bState);
    #endif
    mbState = bState;
}

bool Relais::GetState()
{
    return mbState;
}