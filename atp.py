import ATP, sys, random
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

@log
def PID( value, setpoint, kp, ki, kd, iterations=0, integralValue=0, last_error=0 ):
    error = setpoint - value
    integralValue += error
    derivative = error - last_error
    output = kp * error + ki * integralValue + kd * derivative
    return output, iterations+1, integralValue, error

def mainloop( tempSensor, chloorSensor, chloorPid, tempPid, max_iterations, iterations=0, temp_log = [], chloor_log=[] ):
    tempValue = tempSensor.getValue()
    chloorValue = chloorSensor.getValue()

    chloorPidValue = chloorPid.update( chloorValue )
    tempPidValue = tempPid.update( tempValue )
    
    heater.SetPowervalue( tempPidValue )
    dispensor.SetPowervalue( chloorPidValue )
    
    temp_log.append( tempValue )
    chloor_log.append( chloorValue )

    if iterations == max_iterations:
        return temp_log, chloor_log
    else:
        return mainloop( tempSensor, chloorSensor, chloorPid, tempPid, max_iterations, iterations+1, temp_log, chloor_log )

def mainloop_functional_PID( tempSensor, chloorSensor, max_iterations, iterations=1, temp_log = [], chloor_log=[], integralTemp=0, errorTemp=0, integralChloor=0, errorChloor=0 ):
    tempValue = tempSensor.getValue()
    chloorValue = chloorSensor.getValue()

    tempPidValue, _, integralTemp, errorTemp = PID( tempValue, 30, 8, 0.01, 0.5, iterations, integralTemp, errorTemp)
    chloorPidValue, _, integralChloor, errorChloor = PID( chloorValue, 8, 9, 0.1, 0.9, iterations, integralChloor, errorChloor)

    heater.SetPowervalue( tempPidValue )
    dispensor.SetPowervalue( chloorPidValue )
    
    temp_log.append( tempValue )
    chloor_log.append( chloorValue )

    if iterations == max_iterations:
        return temp_log, chloor_log
    else:
        return mainloop_functional_PID( tempSensor, chloorSensor, max_iterations, iterations+1, temp_log, chloor_log, integralTemp, errorTemp, integralChloor, errorChloor )

def mainloop_functional_PID_Changing_Target( tempSensor, PhSensor, max_iterations, targetsTemp, targetsPh, iterations=1, temp_log = [], Ph_log=[], integralTemp=0, errorTemp=0, integralPh=0, errorPh=0 ):
    tempValue = tempSensor.getValue()
    PhValue = PhSensor.getValue()

    tempPidValue, _, integralTemp, errorTemp = PID( tempValue, targetsTemp[0], 8, 0.01, 0.5, iterations, integralTemp, errorTemp)
    phPidValue, _, integralPh, errorPh = PID( PhValue, targetsPh[0], 8, 0.1, 0.9, iterations, integralPh, errorPh)

    heater.SetPowervalue( tempPidValue )
    dispensor.SetPowervalue( phPidValue )
    
    temp_log.append( tempValue )
    Ph_log.append( PhValue )

    if iterations == max_iterations:
        return temp_log, Ph_log
    else:
        return mainloop_functional_PID_Changing_Target( tempSensor, PhSensor, max_iterations, targetsTemp[1:], targetsPh[1:], iterations+1, temp_log, Ph_log, integralTemp, errorTemp, integralPh, errorPh )

if __name__ == "__main__":
    heater = ATP.Heater(10 , 0)
    dispensor = ATP.Dispensor(11 , 0)

    tempSensor = ATP.TMP36TestSensor( 0, 2, -40, 125, 0.05, 1, heater )
    chloorSensor = ATP.PHSensorTestSensor( 5, 0.0, 0, 100, 0.18, 0.5, dispensor )

    if not SWITCHING_TARGET_VALUE:
        if FUNCTIONAL_PID_VERSION:
            tempPid = ATP.PID( 30, 8, 0.01, 0.5 )
            chloorPid = ATP.PID( 8, 9, 0.1, 0.9 )

            temp, chloor = mainloop( tempSensor, chloorSensor, chloorPid, tempPid, 9997 )

        else:
            temp, chloor = mainloop_functional_PID( tempSensor, chloorSensor, 9997 )
    else:
        # create list of 10000 random values between 30 and 40
        targetsTemp = 1000*[random.randint(20, 40)]+1000*[random.randint(20, 40)]+1000*[random.randint(20, 40)]+1000*[random.randint(20, 40)]+1000*[random.randint(20, 40)]+1000*[random.randint(20, 40)]+1000*[random.randint(20, 40)]+1000*[random.randint(20, 40)]+1000*[random.randint(20, 40)]+1000*[random.randint(20, 40)]
        targetsPh = 1000*[random.randint(7, 10)]+1000*[random.randint(7, 10)]+1000*[random.randint(7, 10)]+1000*[random.randint(7, 10)]+1000*[random.randint(7, 10)]+1000*[random.randint(7, 10)]+1000*[random.randint(7, 10)]+1000*[random.randint(7, 10)]+1000*[random.randint(7, 10)]+1000*[random.randint(7, 10)]
        temp, chloor = mainloop_functional_PID_Changing_Target(tempSensor, chloorSensor, 9997, targetsTemp, targetsPh)

    # plot temps
    import matplotlib.pyplot as plt
    plt.plot( temp )
    plt.plot( chloor )

    if SWITCHING_TARGET_VALUE:
        plt.plot( targetsTemp )
        plt.plot( targetsPh )

    plt.show()
