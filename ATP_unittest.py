import ATP, unittest, atp, sys, random
import matplotlib.pyplot as plt

class ATPTestCase(unittest.TestCase):
    def TempSensorValue(self):
        # Check if the analog value to degrees celcius conversion is working correctly
        tempSensor = ATP.TMP36TestSensor( 0, 2, -40, 125, 0.05, 1, ATP.Heater(10 , 0) )
        self.assertAlmostEqual(tempSensor.CalculateValue(2.7), -40, 1)
        self.assertAlmostEqual(tempSensor.CalculateValue(3.5), 7.1, 1)
        self.assertAlmostEqual(tempSensor.CalculateValue(4.0), 36.6, 1)
        self.assertAlmostEqual(tempSensor.CalculateValue(5.0), 95.5, 1)
        self.assertAlmostEqual(tempSensor.CalculateValue(5.5), 125, 1)
        
    def PHSensorValue(self):        
        PHSensor = ATP.PHSensorTestSensor( 5, 0.0, 0, 100, 0.18, 0.5, ATP.Dispensor(11 , 0) )

        # Check if the analog value to PH-value conversion is working correctly
        self.assertAlmostEqual(PHSensor.CalculateValue(3.7), 6.6, 1)
        self.assertAlmostEqual(PHSensor.CalculateValue(3.8), 5.8, 1)
        self.assertAlmostEqual(PHSensor.CalculateValue(3.9), 5.0, 1)
        self.assertAlmostEqual(PHSensor.CalculateValue(4.0), 4.1, 1)
        self.assertAlmostEqual(PHSensor.CalculateValue(4.1), 3.3, 1)
        self.assertAlmostEqual(PHSensor.CalculateValue(4.2), 2.5, 1)
        self.assertAlmostEqual(PHSensor.CalculateValue(4.3), 1.7, 1)
        self.assertAlmostEqual(PHSensor.CalculateValue(4.4), 0.9, 1)

    def IntegratieTest(self):
        # Check if the PID controller is working correctly

        #check 1: if the setpoint is 30 and the current value is 27, the output should be positive
        PIDoutput = atp.PID( 27, 30, 8, 0.01, 0.5, 1, 0, 0)
        self.assertAlmostEqual(PIDoutput[0], 25.53, 1)
        
        #check 2: if the setpoint is 30 and the current value is 30, the output should be 0
        PIDoutput = atp.PID( 30, 30, 8, 0.01, 0.5, 1, 0, 0)
        self.assertAlmostEqual(PIDoutput[0], 0, 1)
        
        #check 3: if the setpoint is 30 and the current value is 33, the output should be negative
        PIDoutput = atp.PID( 33, 30, 8, 0.01, 0.5, 1, 0, 0)
        self.assertAlmostEqual(PIDoutput[0], -25.53, 1)
    
    def SysteemTest(self):
        heater = ATP.Heater(10 , 0)
        dispensor = ATP.Dispensor(11 , 0)

        display = ATP.Display()

        tempSensor = ATP.TMP36TestSensor( 0, 2, -40, 125, 0.05, 1, heater )
        phSensor = ATP.PHSensorTestSensor( 5, 0.0, 0, 100, 0.18, 0.5, dispensor )

        targetsTemp = 1000*[random.randint(20, 40)]+1000*[random.randint(20, 40)]+1000*[random.randint(20, 40)]+1000*[random.randint(20, 40)]+1000*[random.randint(20, 40)]+1000*[random.randint(20, 40)]+1000*[random.randint(20, 40)]+1000*[random.randint(20, 40)]+1000*[random.randint(20, 40)]+1000*[random.randint(20, 40)]
        targetsPh = 1000*[random.randint(7, 10)]+1000*[random.randint(7, 10)]+1000*[random.randint(7, 10)]+1000*[random.randint(7, 10)]+1000*[random.randint(7, 10)]+1000*[random.randint(7, 10)]+1000*[random.randint(7, 10)]+1000*[random.randint(7, 10)]+1000*[random.randint(7, 10)]+1000*[random.randint(7, 10)]
        temp, ph = atp.mainloop_functional_PID_Changing_Target(tempSensor, phSensor, display, heater, dispensor, 9997, targetsTemp, targetsPh)

        plt.plot( temp )
        plt.plot( ph )
        plt.plot( targetsTemp )
        plt.plot( targetsPh )
        plt.show()

def suite():
    suite = unittest.TestSuite()
    suite.addTest(ATPTestCase('TempSensorValue'))
    suite.addTest(ATPTestCase('PHSensorValue'))
    suite.addTest(ATPTestCase('IntegratieTest'))
    suite.addTest(ATPTestCase('SysteemTest'))
    return suite

if __name__ == '__main__':
    runner = unittest.TextTestRunner()
    runner.run(suite())
