#ifndef FLIGHTCONTROLLER_H
#define FLIGHTCONTROLLER_H

#include "motor.h"
#include "../state.h"
#include "../../constants.h"

class FlightController
{
public:
    FlightController();

    void setup();
    void update(State current, unsigned long deltaTime, double PITCH_KP, double PITCH_KI, double PITCH_KD, double ROLL_KP, double ROLL_KI, double ROLL_KD);
private:
    Motor motor;

    double targetRoll;
    double targetPitch;

    double pitchI, rollI, pitchError, rollError;

    double calculateAdjustment(double current, double target, double kp, double ki, double kd, double& previousI, double& prevError, unsigned long deltaTime);
};

#endif