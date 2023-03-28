#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

#ifdef RPI
    #include <wiringPi.h>
#else
    #include <iostream>
#endif

class PID {
public:
    PID();
    void update()
    void setTarget(const float& fTarget);
    void setKp(const float& fKp);
    void setKi(const float& fKi);
    void setKd(const float& fKd);
    float getTarget();
    float getKp();
    float getKi();
    float getKd();
  
private:
    
};