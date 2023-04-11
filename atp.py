import ATP, sys, random, inspect
from functools import wraps

sys.setrecursionlimit(20000)

FUNCTIONAL_PID_VERSION = True
SWITCHING_TARGET_VALUE = True

def log(func):
    @wraps(func)
    def logger( *args, **kwargs):
        try:
            print("Entering: [%s] with arguments %s, and keyword arguments %s" % (func.__name__, args, kwargs))
            try:
                output = func( *args, **kwargs)
                print("Exiting: [%s] with output %s\n\n" % (func.__name__, output))
                return output
            except Exception as e:
                print('Exception in %s : %s' % (func.__name__, e))
        except:
            pass
    return logger 

def PID( value, setpoint, kp, ki, kd, iterations=0, integralValue=0, last_error=0 ):
    error = setpoint - value
    integralValue += error
    if integralValue > 1000:
        integralValue = 1000
    elif integralValue < -1000:
        integralValue = -1000
    derivative = error - last_error
    output = kp * error + ki * integralValue + kd * derivative
    return output, iterations+1, integralValue, error

def mainloop( tempSensor, phSensor, display, heater, dispensor, phPid, tempPid, max_iterations, iterations=0, temp_log = [], ph_log=[] ):
    tempValue = tempSensor.getValue()
    phValue = phSensor.getValue()

    phPidValue = phPid.update( phValue )
    tempPidValue = tempPid.update( tempValue )
    
    heater.SetPowervalue( tempPidValue )
    dispensor.SetPowervalue( phPidValue )
    
    display.WriteString( "Temperature: %s °C\nPH-value: %s" % (tempValue, phValue) )

    temp_log.append( tempValue )
    ph_log.append( phValue )

    if iterations == max_iterations:
        return temp_log, ph_log
    else:
        return mainloop( tempSensor, phSensor, display, heater, dispensor, phPid, tempPid, max_iterations, iterations+1, temp_log, ph_log )

def mainloop_functional_PID( tempSensor, phSensor, display, heater, dispensor, max_iterations, iterations=1, temp_log = [], ph_log=[], integralTemp=0, errorTemp=0, integralPh=0, errorPh=0 ):
    tempValue = tempSensor.getValue()
    phValue = phSensor.getValue()

    tempPidValue, _, integralTemp, errorTemp = PID( tempValue, 30, 8, 0.01, 0.5, iterations, integralTemp, errorTemp)
    phPidValue, _, integralPh, errorPh = PID( phValue, 8, 9, 0.1, 0.9, iterations, integralPh, errorPh)

    heater.SetPowervalue( tempPidValue )
    dispensor.SetPowervalue( phPidValue )
    
    display.WriteString( "Temperature: %s °C\nPH-value: %s" % (tempValue, phValue) )

    temp_log.append( tempValue )
    ph_log.append( phValue )

    if iterations == max_iterations:
        return temp_log, ph_log
    else:
        return mainloop_functional_PID( tempSensor, phSensor, display, heater, dispensor, max_iterations, iterations+1, temp_log, ph_log, integralTemp, errorTemp, integralPh, errorPh )

def mainloop_functional_PID_Changing_Target( tempSensor, PhSensor, display, heater, dispensor, max_iterations, targetsTemp, targetsPh, iterations=1, temp_log = [], Ph_log=[], integralTemp=0, errorTemp=0, integralPh=0, errorPh=0 ):
    tempValue = tempSensor.getValue()
    phValue = PhSensor.getValue()

    tempPidValue, _, integralTemp, errorTemp = PID( tempValue, targetsTemp[0], 8, 0.01, 0.5, iterations, integralTemp, errorTemp)
    phPidValue, _, integralPh, errorPh = PID( phValue, targetsPh[0], 8, 0.1, 0.9, iterations, integralPh, errorPh)

    heater.SetPowervalue( tempPidValue )
    dispensor.SetPowervalue( phPidValue )

    display.WriteString( "Temperature: %s °C\nPH-value: %s" % (tempValue, phValue) )
    
    temp_log.append( tempValue )
    Ph_log.append( phValue )

    if iterations == max_iterations:
        return temp_log, Ph_log
    else:
        return mainloop_functional_PID_Changing_Target( tempSensor, PhSensor, display, heater, dispensor, max_iterations, targetsTemp[1:], targetsPh[1:], iterations+1, temp_log, Ph_log, integralTemp, errorTemp, integralPh, errorPh )

if __name__ == "__main__":
    
    heater = ATP.Heater(10 , 0)
    dispensor = ATP.Dispensor(11 , 0)

    display = ATP.Display()

    tempSensor = ATP.TMP36TestSensor( 0, 0, -40, 125, 0.05, 1, heater )
    phSensor = ATP.PHSensorTestSensor( 5, 0.0, 0, 100, 0.18, 0.5, dispensor )

    if not SWITCHING_TARGET_VALUE:
        if not FUNCTIONAL_PID_VERSION:
            tempPid = ATP.PID( 30, 8, 0.01, 0.5 )
            phPid = ATP.PID( 8, 9, 0.1, 0.9 )

            temp, ph = mainloop( tempSensor, phSensor, display, heater, dispensor, phPid, tempPid, 9997 )

        else:
            temp, ph = mainloop_functional_PID( tempSensor, phSensor, display, heater, dispensor, 9997 )
    else:
        targetsTemp = 1000*[random.randint(20, 40)]+1000*[random.randint(20, 40)]+1000*[random.randint(20, 40)]+1000*[random.randint(20, 40)]+1000*[random.randint(20, 40)]+1000*[random.randint(20, 40)]+1000*[random.randint(20, 40)]+1000*[random.randint(20, 40)]+1000*[random.randint(20, 40)]+1000*[random.randint(20, 40)]
        targetsPh = 1000*[random.randint(7, 10)]+1000*[random.randint(7, 10)]+1000*[random.randint(7, 10)]+1000*[random.randint(7, 10)]+1000*[random.randint(7, 10)]+1000*[random.randint(7, 10)]+1000*[random.randint(7, 10)]+1000*[random.randint(7, 10)]+1000*[random.randint(7, 10)]+1000*[random.randint(7, 10)]
        temp, ph = mainloop_functional_PID_Changing_Target(tempSensor, phSensor, display, heater, dispensor, 9997, targetsTemp, targetsPh)

    import matplotlib.pyplot as plt
    plt.plot( temp )
    plt.plot( ph )

    if SWITCHING_TARGET_VALUE:
        plt.plot( targetsTemp )
        plt.plot( targetsPh )

    plt.show()
