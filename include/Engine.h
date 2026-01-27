
#ifndef VEHICLE_TELEMETRY_SIMULATOR_ENGINE_H
#define VEHICLE_TELEMETRY_SIMULATOR_ENGINE_H


class Engine {
private:
    const double FRICTION_COEF;
    const double BASE_INERTIA;
    double currentInertia;
    double maxTorque;
    double torque = 0.0;
    double rpm = 0.0;

    void updateMaxTorque();
    void updateTorque(double throttle);
    void updateRpm(double dt);

public:
    Engine(double frictionCoef, double baseInertia, double maxTorque);
    // nodiscard will send a warning if the method's output is not used
    [[nodiscard]] double getBaseInertia() const;
    [[nodiscard]] double getFrictionCoef() const;
    [[nodiscard]] double getRpm() const;
    void setCurrentInertia(double inertia);
    void update(double dt, double throttle);
};


#endif //VEHICLE_TELEMETRY_SIMULATOR_ENGINE_H