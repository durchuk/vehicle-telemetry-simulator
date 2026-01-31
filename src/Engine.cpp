#include "Engine.h"
#include <numbers>

Engine::Engine(double peakTorque, double frictionCoef, double baseInertia)
    : PEAK_TORQUE(peakTorque),
    FRICTION_COEF(frictionCoef),
    BASE_INERTIA(baseInertia),
    currentInertia(baseInertia),
    maxTorqueForRpm(peakTorque)
{}

void Engine::updateMaxTorqueForRpm() {
    // Phase 1: Low speed
    // Torque is low, the engine almost stalls
    if (rpm < 1000) {
        maxTorqueForRpm = 100.0 + (rpm * 0.1); // Gently increase from 100 to 200
    }
    // Phase 2: The power zone
    // This is the plateau, where torque is at its maximum and stable
    else if (rpm < 5500) {
        maxTorqueForRpm = PEAK_TORQUE; // Constant
    }
    // Phase 3: Exhaust
    // The engine can no longer draw in enough air, causing torque to drop
    else {
        maxTorqueForRpm = PEAK_TORQUE - (rpm - 5500) * 0.2;

        // The torque cannot be negative
        if (maxTorqueForRpm < 0) maxTorqueForRpm = 0;
    }
}

void Engine::updateTorque(double throttle) {
    torque = maxTorqueForRpm * throttle - rpm * FRICTION_COEF;
}

void Engine::updateRpm(double dt) {
    double angularAcceleration = torque / currentInertia;
    // Convert Rad/s^2 to RPM/s
    double rpmAcceleration = angularAcceleration * (60.0 / (2.0 * std::numbers::pi));
    rpm += rpmAcceleration * dt;
    // If RPM drops under 900, the engine injects some fuel
    // automatically to keep the engine alive
    if (rpm < 800.0) rpm = 800.0;
    // If we accelerate too much, the engine blocks
    // the number of RPM to prevent melting
    if (rpm > 7000.0) rpm = 7000.0;
}

void Engine::update(double dt, double throttle) {
    updateMaxTorqueForRpm();
    updateTorque(throttle);
    updateRpm(dt);
}

double Engine::getBaseInertia() const {
    return BASE_INERTIA;
}

double Engine::getFrictionCoef() const {
    return FRICTION_COEF;
}

double Engine::getRpm() const {
    return rpm;
}

double Engine::getTorque() const {
    return torque;
}

void Engine::setCurrentInertia(double inertia) {
    // Inertia can never be less than the base inertia.
    if (inertia < BASE_INERTIA) {
        currentInertia = BASE_INERTIA;
    } else {
        currentInertia = inertia;
    }
}

void Engine::setRpm(double rpm) {
    this->rpm = rpm;
}
