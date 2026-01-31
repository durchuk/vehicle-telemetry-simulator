#ifndef VEHICLE_TELEMETRY_SIMULATOR_GEARBOX_H
#define VEHICLE_TELEMETRY_SIMULATOR_GEARBOX_H
#include <vector>

class Gearbox {
private:
    static constexpr int FRICTION_SENSITIVITY = 70000;
    int currentGear = 1;
    std::vector<double> ratios;

public:
    Gearbox(const std::vector<double>& ratios);
    [[nodiscard]] double getRatio() const;
    [[nodiscard]] int getGear() const;
    void updateLogic(double currentRpm, double throttle, double frictionCoef);
};


#endif //VEHICLE_TELEMETRY_SIMULATOR_GEARBOX_H