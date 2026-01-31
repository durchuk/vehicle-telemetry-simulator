#include "Gearbox.h"
#include <vector>
#include <cassert>

Gearbox::Gearbox(const std::vector<double>& ratios) : ratios(ratios) {
    assert(ratios.size() >= 2 && "Gearbox must have at least 2 ratios (invalid ratios).");
}

double Gearbox::getRatio() const {
    return ratios.at(currentGear);
}

int Gearbox::getGear() const {
    return currentGear;
}

void Gearbox::updateLogic(double currentRpm, double throttle, double frictionCoef) {
    // 1. Consider driver's intention (eco / sport)
    double ecoUpshiftRpm = 2500.0;
    double sportUpshiftRpm = 6500.0;
    // Choose a value between eco and sport based on throttle
    double idealUpshiftRpm = ecoUpshiftRpm + (throttle * (sportUpshiftRpm - ecoUpshiftRpm));

    // 2. Calculate Dynamic Shift Point
    // Calculate how much to lower the shift point based on engine friction
    double frictionPenalty = frictionCoef * FRICTION_SENSITIVITY;
    // Base shift point is reduced by the friction penalty
    double upshiftRpm = idealUpshiftRpm - frictionPenalty;
    // Ensure we don't shift up too early
    if (upshiftRpm < 2000.0) upshiftRpm = 2000.0;
    // Threshold for downshifting
    double downshiftRpm = 1500.0;

    // 3. Shift logic
    if (currentRpm > upshiftRpm && currentGear < (ratios.size() - 1)) {
        currentGear++;
    } else if (currentRpm < downshiftRpm && currentGear > 1){
        currentGear--;
    }
}
