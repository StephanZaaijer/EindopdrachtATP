#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

class PID {
public:
    PID( const float& fTarget, const float& fKp, const float& fKi, const float& fKd );
    float update( const float& fInput );
    void setTarget(const float& fTarget);
    void setKp(const float& fKp);
    void setKi(const float& fKi);
    void setKd(const float& fKd);
    float getTarget();
    float getKp();
    float getKi();
    float getKd();
    float getLastError();
    float getIntegral();
    void resetIntegral();
    void resetLastError();
    void reset();
    
  
private:
    float mfTarget;
    float mfKp;
    float mfKi;
    float mfKd;

    float mfLastError;
    float mfIntegral;
};