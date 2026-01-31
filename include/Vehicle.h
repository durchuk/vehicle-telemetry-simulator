#ifndef VEHICLE_TELEMETRY_SIMULATOR_VEHICLE_H
#define VEHICLE_TELEMETRY_SIMULATOR_VEHICLE_H
#include "Engine.h"
#include "Gearbox.h"

class Vehicle {
private:
    const double WHEEL_RADIUS;
    const double DIFF_RATIO;
    const double MASS;
    const double CAR_MASS_IMPACT;
    const double MAX_INJECTION;
    double speed = 0.0;
    double fuel = 0.0;
    double throttle = 0.0;
    double transmissionTorque = 0.0;
    double wheelTorque = 0.0;
    Engine engine;
    Gearbox gearbox;

    void manageTransmission();
    void updateSpeed(double currentRatio, double rps);
    void updateFuel(double dt, double rps);
    void updateCurrentInertia(double currentRatio);
    void updateTransmissionTorque(double currentRatio);
    void updateWheelTorque();

public:
    Vehicle(double wheelRadiusM,
        double differentialRatio,
        double massKg,
        double maxInjectionL,
        const Engine& engine,
        const Gearbox& gearbox);
    void accelerate(double throttlePercent); // a throttle setter
    void fillUp(double amountL); // a fuel setter
    bool startEngine();
    [[nodiscard]] double getSpeed() const;
    [[nodiscard]] double getFuel() const;
    [[nodiscard]] int getGear() const;
    [[nodiscard]] double getRpm() const;
    void update(double dt);
};


#endif //VEHICLE_TELEMETRY_SIMULATOR_VEHICLE_H