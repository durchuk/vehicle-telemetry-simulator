cmake_minimum_required(VERSION 4.1)
project(Vehicle_Telemetry_Simulator)

set(CMAKE_CXX_STANDARD 20)

# Look for the .h files in the include directory if asked for
include_directories(${CMAKE_SOURCE_DIR}/include)

add_executable(Vehicle_Telemetry_Simulator
        src/main.cpp
        src/Engine.cpp
        src/Gearbox.cpp
        src/Vehicle.cpp)

# Find the right Python environment
find_package(Python3 COMPONENTS Interpreter REQUIRED)

# Set up virtual environment path
set(VENV_DIR "${CMAKE_BINARY_DIR}/venv")

# Determine the Python executable in the venv
if(WIN32)
    set(VENV_PYTHON "${VENV_DIR}/Scripts/python.exe")
    set(VENV_PIP "${VENV_DIR}/Scripts/pip.exe")
else()
    set(VENV_PYTHON "${VENV_DIR}/bin/python")
    set(VENV_PIP "${VENV_DIR}/bin/pip")
endif()

# Create virtual environment
add_custom_command(
        OUTPUT "${VENV_PYTHON}"
        COMMAND ${Python3_EXECUTABLE} -m venv ${VENV_DIR}
        COMMENT "Creating Python virtual environment"
)

# Install requirements
add_custom_command(
        OUTPUT "${VENV_DIR}/.requirements_installed"
        COMMAND ${VENV_PIP} install -r "${CMAKE_SOURCE_DIR}/requirements.txt"
        COMMAND ${CMAKE_COMMAND} -E touch "${VENV_DIR}/.requirements_installed"
        DEPENDS "${VENV_PYTHON}" "${CMAKE_SOURCE_DIR}/requirements.txt"
        COMMENT "Installing Python requirements"
)

# Create a target for the Python environment
add_custom_target(python_env ALL
        DEPENDS "${VENV_DIR}/.requirements_installed"
)

# Make sure python_env is built before the executable
add_dependencies(Vehicle_Telemetry_Simulator python_env)

# Pass the venv Python path to C++
target_compile_definitions(Vehicle_Telemetry_Simulator PRIVATE
        PYTHON_EXECUTABLE=\"${VENV_PYTHON}\"
)

# Copy the python file to the build folder
file(COPY src/plot_telemetry.py DESTINATION ${CMAKE_CURRENT_BINARY_DIR})