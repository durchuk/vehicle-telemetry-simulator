#include <iostream>
#include "Gearbox.h"
#include "Engine.h"
#include "Vehicle.h"
#include <fstream>
#include <cstdlib>

int main() {
    std::cout << "############## Vehicle Telemetry Simulator ##############\n";
    std::cout << "Scenario: 0 to top speed test (aerodynamic limit)\n\n";

    // Setting the gearbox to some average values
    const std::vector<double> gears = {0.0, 3.6, 2.1, 1.45, 1.03, 0.82};
    Gearbox gearbox(gears);
    // Setting the engine to some average values
    Engine engine(180,0.007, 0.4);
    // Setting other vehicle stats to some average values
    Vehicle vehicle(0.33, 3.42, 1500, 0.00015, 0.3, 2.3, engine, gearbox);

    // Initialising a csv
    std::ofstream file("telemetry.csv");
    file << "Time,Speed_kmh,RPM,Gear,Fuel_L\n";

    std::cout << "Filling up the vehicle…\n";
    vehicle.fillUp(20.0);
    std::cout << "Starting the engine…\n";
    vehicle.startEngine();

    double simTime = 0.0;
    double dt = 0.016; // 60 FPS
    double maxDuration = 120.0;
    std::cout << "Pedal to the metal!\n";
    while (simTime < maxDuration) {
        double torque = 1.0;
        vehicle.accelerate(torque);

        vehicle.update(dt);
        simTime += dt;

        file << simTime << ","
            << vehicle.getSpeed() * 3.6 << ","
            << vehicle.getRpm() << ","
            << vehicle.getGear() << ","
            << vehicle.getFuel() << "\n";
    }

    file.close();
    std::cout << "Simulation finished. Top speed reached: " << vehicle.getSpeed() * 3.6 << "\n";
    std::cout << "Data saved to telemetry.csv…\n";
    std::cout << "Generating graphs with Python…\n";

    // Running the python script
    // Getting the correct environment from CMake
    std::string command = "\"" + std::string(PYTHON_EXECUTABLE) + "\"" + " plot_telemetry.py";
    int result = std::system(command.c_str());
    if (result == 0) {
        std::cout << "Visualization saved to 'simulation_results.png'.\n";
    } else {
        std::cout << "Error: Python script execution failed.\n";
    }
    return 0;
}
