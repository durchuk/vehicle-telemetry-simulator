
#ifndef VEHICLE_TELEMETRY_SIMULATOR_ENGINE_H
#define VEHICLE_TELEMETRY_SIMULATOR_ENGINE_H


class Engine {
private:
    const double PEAK_TORQUE;
    const double FRICTION_COEF;
    const double BASE_INERTIA;
    double currentInertia;
    double maxTorqueForRpm;
    double torque = 0.0;
    double rpm = 0.0;

    void updateMaxTorqueForRpm();
    void updateTorque(double throttle, double loadTorque);
    void updateRpm(double dt);

public:
    Engine(double peakTorque, double frictionCoef, double baseInertia);
    // nodiscard will send a warning if the method's output is not used
    [[nodiscard]] double getBaseInertia() const;
    [[nodiscard]] double getFrictionCoef() const;
    [[nodiscard]] double getRpm() const;
    [[nodiscard]] double getTorque() const;
    void setCurrentInertia(double inertia);
    void setRpm(double rpm);
    void update(double dt, double throttle, double loadTorque);
};


#endif //VEHICLE_TELEMETRY_SIMULATOR_ENGINE_H