INC_DIR = extern/pybind11/include
TARGET = ATP
COMPILER = c++
CFLAGS_LINUX = -O3 -Wall -shared -std=c++11 -fPIC $(shell python3-config --includes) -I $(INC_DIR) -I ./
PYTHON_MODULEFILE = $(TARGET)${shell python3-config --extension-suffix}

.DEFAULT_GOAL := all
.PHONY: all run build clean

all: run build

build: $(PYTHON_MODULEFILE)

run: build
	@echo "Executing atp.py..."
	@python3 atp.py

$(PYTHON_MODULEFILE): Actuator.o Pid.o PythonModule.o Sensor.o
	@echo "Compiling $@..."
	@$(COMPILER) $(CFLAGS_LINUX) $^ -o $@

Actuator.o: Actuator.cpp Actuator.hpp
	@echo "Compiling $@..."
	@$(COMPILER) $(CFLAGS_LINUX) -c $< -o $@

Pid.o: Pid.cpp Pid.hpp
	@echo "Compiling $@..."
	@$(COMPILER) $(CFLAGS_LINUX) -c $< -o $@

PythonModule.o: PythonModule.cpp Pid.o Actuator.o Sensor.o
	@echo "Compiling $@..."
	@$(COMPILER) $(CFLAGS_LINUX) -c $< -o $@

Sensor.o: Sensor.cpp Sensor.hpp
	@echo "Compiling $@..."
	@$(COMPILER) $(CFLAGS_LINUX) -c $< -o $@

clean:
	@echo "Removing $(PYTHON_MODULEFILE)"
	@rm -f $(PYTHON_MODULEFILE)

	@echo "Removing *.o files"
	@rm -f *.o