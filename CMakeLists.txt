cmake_minimum_required(VERSION 4.1)
project(Vehicle_Telemetry_Simulator)

set(CMAKE_CXX_STANDARD 20)

# Look for the .h files in the include directory if asked for
include_directories(include)

add_executable(Vehicle_Telemetry_Simulator
        src/main.cpp
        src/Engine.cpp
        src/Gearbox.cpp
        src/Vehicle.cpp)
