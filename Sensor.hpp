#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

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
    TestSensor( const float& fLastValue = 0.0f,
                const float& fMaxDifference = 1.0f,
                const float& fMinValue = -100.0f,
                const float& fMaxValue = 100.0f );
    float getValue() override;
    void setValue(const float& fValue);
    void setMaxDifference(const float& fMaxDifference);

private:
    float mfLastValue;
    float mfMaxDifference;
    float mfMinValue;
    float mfMaxValue;
};