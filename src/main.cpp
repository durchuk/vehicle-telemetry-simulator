#include <iostream>
#include "Engine.h"

int main() {
    std::cout << "############## Vehicle Telemetry Simulator ##############\n\n";
    std::cout << "Testing the engine…\n";

    // Setting the engine to some average values
    Engine engine(0.007, 0.4, 350);
    std::cout << "Current RPM: " << engine.getRpm() << std::endl;
    std::cout << "Pressing gas half way through for 1 second…\n";
    engine.update(1.0, 0.5);
    std::cout << "New RPM: " << engine.getRpm() << std::endl;

    std::cout << "\nReleasing the gas for 5 sec…\n";
    engine.update(5.0, 0);
    std::cout << "New RPM: " << engine.getRpm() << std::endl;
    return 0;
}
