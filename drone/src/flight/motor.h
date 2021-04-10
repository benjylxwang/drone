#ifndef MOTOR_H
#define MOTOR_H

#include <Arduino.h>
#include "../state.h"
#include "../../constants.h"

class Motor
{
public:
    Motor(byte frontLeftPin, byte frontRightPin, byte backLeftPin, byte backRightPin);

    void setup();

private:
    byte pins[MOTOR_COUNT];

    void setMotorSpeed(byte motor, int speed);
};

#endif