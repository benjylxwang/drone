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
    void update(State current);
private:
    Motor motor;

    double targetRoll;
    double targetPitch;

    int calculateAdjustment(double current, double target);
};

#endif