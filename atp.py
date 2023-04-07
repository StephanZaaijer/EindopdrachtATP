import ATP, sys

sys.setrecursionlimit(10000)

FUNCTIONAL_PID_VERSION = True

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

def mainloop_functional_PIDv2( tempSensor, chloorSensor, chloorPid, tempPid, tempTarget, chloorTarget, max_iterations, iterations=1, temp_log = [], chloor_log=[] ):
    tempValue = tempSensor.getValue()
    chloorValue = chloorSensor.getValue()

    tempPidValue = tempPid( tempTarget, tempValue )
    chloorPidValue = chloorPid( chloorTarget, chloorValue )

    heater.SetPowervalue( tempPidValue )
    dispensor.SetPowervalue( chloorPidValue )
    
    temp_log.append( tempValue )
    chloor_log.append( chloorValue )

    if iterations == max_iterations:
        return temp_log, chloor_log
    else:
        return mainloop_functional_PIDv2( tempSensor, chloorSensor, chloorPid, tempPid, tempTarget, chloorTarget, max_iterations, iterations+1, temp_log, chloor_log )

if __name__ == "__main__":

    heater = ATP.Heater(10 , 0)
    dispensor = ATP.Dispensor(11 , 0)

    tempSensor = ATP.TestSensor( 0, 0, -100, 100, 0.05, 1, heater )
    chloorSensor = ATP.TestSensor( 5, 0.0, 0, 100, 0.18, 0.5, dispensor )

    if FUNCTIONAL_PID_VERSION:
        tempPid = ATP.PID( 30, 8, 0.01, 0.5 )
        chloorPid = ATP.PID( 8, 9, 0.1, 0.9 )

        temp, chloor = mainloop( tempSensor, chloorSensor, chloorPid, tempPid, 9997 )

    else:
        temp, chloor = mainloop_functional_PID( tempSensor, chloorSensor, 9997 )
        
    # plot temps
    import matplotlib.pyplot as plt
    plt.plot( temp )
    plt.plot( chloor )
    plt.show()
