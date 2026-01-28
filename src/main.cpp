#include <iostream>
#include "Gearbox.h"

int main() {
    std::cout << "############## Vehicle Telemetry Simulator ##############\n\n";
    std::cout << "Testing the gearbox…\n";

    // Setting the gearbox to some average values
    const std::vector<double> gears = { 0.0, 3.5, 2.0, 1.4, 1.0, 0.8 };
    Gearbox gearbox(gears);
    double rpm = 0.0;
    std::cout << "Current rpm: " << rpm << std::endl;
    std::cout << "Current gear ratio: " << gearbox.getRatio() << std::endl;
    std::cout << "Accelerating…\n";
    rpm += 6500.0;
    gearbox.updateLogic(rpm, 0.007); // Average friction coefficient
    std::cout << "Current rpm: " << rpm << std::endl;
    std::cout << "Current gear ratio: " << gearbox.getRatio() << std::endl;
    return 0;
}
