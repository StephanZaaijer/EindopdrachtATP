#include "Pid.hpp"

PID::PID( const float& fTarget, const float& fKp, const float& fKi, const float& fKd ):
    mfTarget(fTarget),
    mfKp(fKp),
    mfKi(fKi),
    mfKd(fKd)
{
    mfLastError = 0;
    mfIntegral = 0;
}
float PID::update( const float& fInput )
{
    float fError = mfTarget - fInput;
    mfIntegral += fError;
    float fDerivative = fError - mfLastError;
    mfLastError = fError;
    return mfKp * fError + mfKi * mfIntegral + mfKd * fDerivative;
}
float PID::getKd()
{
    return mfKd;
}
float PID::getKi()
{
    return mfKi;
}
float PID::getKp()
{
    return mfKp;
}
float PID::getTarget()
{
    return mfTarget;
}
void PID::setKd(const float& fKd)
{
    mfKd = fKd;
}
void PID::setKi(const float& fKi)
{
    mfKi = fKi;
}
void PID::setKp(const float& fKp)
{
    mfKp = fKp;
}
void PID::setTarget(const float& fTarget)
{
    mfTarget = fTarget;
}
float PID::getLastError()
{
    return mfLastError;
}
float PID::getIntegral()
{
    return mfIntegral;
}
void PID::resetIntegral()
{
    mfIntegral = 0;
}
void PID::resetLastError()
{
    mfLastError = 0;
}
void PID::reset()
{
    resetIntegral();
    resetLastError();
}   
