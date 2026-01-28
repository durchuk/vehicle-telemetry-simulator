#include "Gearbox.h"
#include <vector>
#include <cassert>

Gearbox::Gearbox(const std::vector<double>& ratios) : ratios(ratios) {
    assert(ratios.size() >= 2 && "Gearbox must have at least 2 ratios (invalid ratios).");
}

double Gearbox::getRatio() const {
    return ratios.at(currentGear);
}

void Gearbox::updateLogic(double currentRpm, double frictionCoef) {
    // 1. Calculate Dynamic Shift Point
    // Calculate how much to lower the shift point based on engine friction
    double frictionPenalty = frictionCoef * FRICTION_SENSITIVITY;
    // Base shift point is 6500 reduced by the friction penalty
    double upshiftRpm = 6500 - frictionPenalty;
    // Ensure we don't shift up too early
    if (upshiftRpm < 3500.0) upshiftRpm = 3500.0;
    // Threshold for downshifting
    double downshiftRpm = 2000;

    // 2. Shift logic
    if (currentRpm > upshiftRpm && currentGear < (ratios.size() - 1)) {
        currentGear++;
    } else if (currentRpm < downshiftRpm && currentGear > 1){
        currentGear--;
    }
}
