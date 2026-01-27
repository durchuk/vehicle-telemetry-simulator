#include "Engine.h"

Engine::Engine(double frictionCoef, double baseInertia, double maxTorque)
    : FRICTION_COEF(frictionCoef),
    BASE_INERTIA(baseInertia),
    currentInertia(baseInertia),
    maxTorque(maxTorque)
{}

void Engine::updateMaxTorque() {
    // Phase 1: Low speed
    // Torque is low, the engine almost stalls
    if (rpm < 1000) {
        maxTorque = 100.0 + (rpm * 0.1); // Gently increase from 100 to 200
    }
    // Phase 2: The power zone
    // This is the plateau, where torque is at its maximum and stable
    else if (rpm < 5500) {
        maxTorque = 300.0; // Constant
    }
    // Phase 3: Exhaust
    // The engine can no longer draw in enough air, causing torque to drop
    else {
        maxTorque = 300.0 - (rpm - 5500) * 0.2;

        // The torque cannot be negative
        if (maxTorque < 0) maxTorque = 0;
    }
}

void Engine::updateTorque(double throttle) {
    torque = maxTorque * throttle - rpm * FRICTION_COEF;
}

void Engine::updateRpm(double dt) {
    rpm += (torque * dt) / currentInertia;
    if (rpm < 0) rpm = 0;
}

void Engine::update(double dt, double throttle) {
    updateMaxTorque();
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

void Engine::setCurrentInertia(double inertia) {
    // Inertia can never be less than the base inertia.
    if (inertia < BASE_INERTIA) {
        currentInertia = BASE_INERTIA;
    } else {
        currentInertia = inertia;
    }
}
