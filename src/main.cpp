#include <iostream>
#include "Gearbox.h"
#include "Engine.h"
#include "Vehicle.h"
#include <chrono>
#include <fstream>

int main() {
    std::cout << "############## Vehicle Telemetry Simulator ##############\n\n";
    // Setting the gearbox to some average values
    const std::vector<double> gears = {0.0, 3.6, 2.1, 1.45, 1.03, 0.82};
    Gearbox gearbox(gears);

    // Setting the engine to some average values
    Engine engine(180,0.007, 0.4);

    // Setting other vehicle stats to some average values
    Vehicle vehicle(0.33, 3.42, 1500, 0.00015, 0.3, 2.3, engine, gearbox);

    // Creating a csv
    std::cout << "Writing simulation data to telemetry.csv…\n";
    std::ofstream file("telemetry.csv");
    file << "Time,Speed_kmh,RPM,Gear,Fuel_L\n";

    std::cout << "Filling up the vehicle…\n";
    vehicle.fillUp(5.0);
    std::cout << "Starting the engine…\n";
    vehicle.startEngine();
    std::cout << "Pressing the gas all in!\n";
    double dt = 0.0;
    while (vehicle.getFuel() > 0) {
        double torque = 1.0;
        vehicle.accelerate(torque);

        vehicle.update(0.016); // 60 FPS
        dt += 0.016;

        file << dt << ","
            << vehicle.getSpeed() * 3.6 << ","
            << vehicle.getRpm() << ","
            << vehicle.getGear() << ","
            << vehicle.getFuel() << "\n";
    }
    file.close();
    std::cout << "Simulation finished.\n";
    return 0;
}
