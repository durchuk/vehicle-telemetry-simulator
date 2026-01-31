#include "Vehicle.h"
#include "Engine.h"
#include "Gearbox.h"
#include <numbers>

Vehicle::Vehicle(const double wheelRadiusM,
    double differentialRatio,
    double massKg,
    double maxInjectionL,
    const Engine& engine,
    const Gearbox&  gearbox)
    : WHEEL_RADIUS(wheelRadiusM),
    DIFF_RATIO(differentialRatio),
    MASS(massKg),
    CAR_MASS_IMPACT((massKg * wheelRadiusM * wheelRadiusM) / (differentialRatio * differentialRatio)),
    MAX_INJECTION(maxInjectionL),
    engine(engine),
    gearbox(gearbox) {}

void Vehicle::accelerate(double throttlePercent) {
    throttle = throttlePercent;
}

void Vehicle::fillUp(double amountL) {
    fuel = amountL;
}

bool Vehicle::startEngine() {
    // If we have enough fuel to start
    if (fuel < 0.02) {
        return false;
    }
    // Warm up the car
    engine.setRpm(800);
    // Consume some fuel
    fuel -= 0.02;
    return true;
}

double Vehicle::getSpeed() const {
    return speed;
}

double Vehicle::getFuel() const {
    return fuel;
}

int Vehicle::getGear() const {
    return gearbox.getGear();
}

double Vehicle::getRpm() const {
    return engine.getRpm();
}

void Vehicle::manageTransmission() {
    // getting the old data
    double rpm = engine.getRpm();
    double oldGear = gearbox.getGear();
    double oldRatio = gearbox.getRatio();

    // Updating the gearbox
    gearbox.updateLogic(rpm, throttle, engine.getFrictionCoef());
    double currentGear = gearbox.getGear();
    double currentRatio = gearbox.getRatio();

    // if the gear has changed, drop the rpm
    if (oldGear != currentGear) {
        rpm = rpm * (currentRatio / oldRatio);
        engine.setRpm(rpm);
    }
}

void Vehicle::updateSpeed(double currentRatio, double rps) {
    speed = (rps * 2.0 * std::numbers::pi * WHEEL_RADIUS) / (currentRatio * DIFF_RATIO);
}

void Vehicle::updateFuel(double dt, double rps) {
    fuel -= dt * rps * MAX_INJECTION * (0.1 + (0.9 * throttle));
    if (fuel < 0) fuel = 0;
}

void Vehicle::updateCurrentInertia(double currentRatio) {
    double baseInertia = engine.getBaseInertia();
    double currentInertia = baseInertia + (CAR_MASS_IMPACT / (currentRatio * currentRatio));
    engine.setCurrentInertia(currentInertia);
}

void Vehicle::updateTransmissionTorque(double currentRatio) {
    transmissionTorque = engine.getTorque() * currentRatio;
}

void Vehicle::updateWheelTorque() {
    wheelTorque = transmissionTorque * DIFF_RATIO;
}

void Vehicle::update(double dt) {
    manageTransmission();
    double currentRatio = gearbox.getRatio();
    updateCurrentInertia(currentRatio);
    engine.update(dt, throttle);
    double rps = engine.getRpm() / 60.0;
    updateFuel(dt, rps);
    updateSpeed(currentRatio, rps);
    updateTransmissionTorque(currentRatio);
    updateWheelTorque();
}
