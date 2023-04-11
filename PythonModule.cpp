#include "Actuator.hpp"
#include "Pid.hpp"
#include "Sensor.hpp"


PYBIND11_MODULE(ATP, m) {
    m.doc() = "ATP c++ implemented sensors";

    pybind11::class_<Display>(m, "Display")
        .def(pybind11::init<>())
        .def("WriteString", &Display::WriteString, "Write string to the display");

    pybind11::class_<Actuator>(m, "Actuator")
        .def(pybind11::init<const int&, const float&>())
        .def("SetPowervalue", &Actuator::SetPowervalue, "Set the powervalue of the actuator", pybind11::arg("fPower"))
        .def("GetPowervalue", &Actuator::GetPowervalue, "Get the powervalue of the actuator");

    pybind11::class_<Heater, Actuator>(m, "Heater")
        .def(pybind11::init<const int&, const float&>())
        .def("SetPowervalue", &Heater::SetPowervalue, "Set the powervalue of the Heater", pybind11::arg("fPower"))
        .def("GetPowervalue", &Heater::GetPowervalue, "Get the powervalue of the Heater");

    pybind11::class_<Dispensor, Actuator>(m, "Dispensor")
        .def(pybind11::init<const int&, const float&>())
        .def("SetPowervalue", &Dispensor::SetPowervalue, "Set the powervalue of the Dispensor", pybind11::arg("fPower"))
        .def("GetPowervalue", &Dispensor::GetPowervalue, "Get the powervalue of the Dispensor");


    pybind11::class_<PID>(m, "PID")
        .def(pybind11::init<const float&, const float&,const float&,const float&>())
        .def("update", &PID::update, "Get new value of PID", pybind11::arg("fInput"))
        .def("setTarget", &PID::setTarget, "Set targetvalue")
        .def("setKp", &PID::setKp, "Set Kp")
        .def("setKi", &PID::setKi, "Set Ki")
        .def("setKd", &PID::setKd, "Set Kd")
        .def("getTarget", &PID::getTarget, "Get targetvalue")
        .def("getKp", &PID::getKp, "Get Kp")
        .def("getKi", &PID::getKi, "Get Ki")
        .def("getKd", &PID::getKd, "Get Kd")
        .def("getLastError", &PID::getLastError, "Get last error")
        .def("getIntegral", &PID::getIntegral, "Get integral")
        .def("resetIntegral", &PID::resetIntegral, "Reset integral")
        .def("resetLastError", &PID::resetLastError, "Reset last error")
        .def("reset", &PID::reset, "Reset PID");

    pybind11::class_<Sensor>(m, "Sensor")
        .def("getValue", &Sensor::getValue, "Get the value of the sensor");

    pybind11::class_<TMP36, Sensor>(m, "TMP36")
        .def(pybind11::init<const int&>())
        .def("getValue", &Sensor::getValue, "Get the value of the sensor");

    pybind11::class_<TMP36TestSensor, TMP36, Sensor>(m, "TMP36TestSensor")
        .def(pybind11::init<const float &, const float, const float &, const float &, const float &, const float &, const Actuator&>())
        .def("getValue", &TMP36TestSensor::getValue, "Get the value of the sensor")
        .def("setValue", &TMP36TestSensor::setValue, "Set the value of the sensor", pybind11::arg("fValue"))
        .def("CalculateValue", &TMP36TestSensor::CalculateValue, "Calculate the value of the sensor", pybind11::arg("fValue"));

    pybind11::class_<PHSensor, Sensor>(m, "PHSensor")
        .def(pybind11::init<const int&>())
        .def("getValue", &Sensor::getValue, "Get the value of the sensor");
    
    pybind11::class_<PHSensorTestSensor, PHSensor, Sensor>(m, "PHSensorTestSensor")
        .def(pybind11::init<const float &, const float, const float &, const float &, const float &, const float &, const Actuator&>())
        .def("getValue", &PHSensorTestSensor::getValue, "Get the value of the sensor")
        .def("setValue", &PHSensorTestSensor::setValue, "Set the value of the sensor", pybind11::arg("fValue"))
        .def("CalculateValue", &PHSensorTestSensor::CalculateValue, "Calculate the value of the sensor", pybind11::arg("fValue"));

}
