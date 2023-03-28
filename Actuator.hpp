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

class Relais {
public:
    Relais(const int& iControlPin = 0, const bool& bState = false);
    void SetState(const bool& bState);
    bool GetState();

private:
    int miControlPin;
    bool mbState;
};