#include "Sensor.hpp"
#include "Actuator.hpp"


PYBIND11_MODULE(atp, m) {
    m.doc() = "ATP c++ implemented sensors";

    pybind11::class_<Sensor>(m, "Sensor")
        .def(pybind11::init<>())
        .def("getValue", &Sensor::getValue, "Get the value of the sensor");

    pybind11::class_<TestSensor, Sensor> TestSensor(m, "TestSensor");
    TestSensor.def(pybind11::init<>());
    TestSensor.def(pybind11::init<const float &>());
    TestSensor.def(pybind11::init<const float &, const float>());
    TestSensor.def(pybind11::init<const float &, const float, const float &>());
    TestSensor.def(pybind11::init<const float &, const float, const float &, const float &>());
    TestSensor.def("getValue", &TestSensor::getValue, "Get the value of the sensor");
    TestSensor.def("setValue", &TestSensor::setValue, "Set the value of the sensor", pybind11::arg("fValue"));
    TestSensor.def("setMaxDifference", &TestSensor::setMaxDifference, "Set the max difference of the sensor", pybind11::arg("dMaxDifference"));


    pybind11::class_<Display>(m, "Display")
        .def(pybind11::init<>())
        .def("WriteString", &Display::WriteString, "Write string to the display");

    pybind11::class_<Relais>(m, "Relais")
        .def(pybind11::init<const int&>())
        .def(pybind11::init<const int&, const bool&>())
        .def("SetState", &Relais::SetState, "Set the state of the relais", pybind11::arg("bState"))
        .def("GetState", &Relais::GetState, "Get the state of the relais");
}