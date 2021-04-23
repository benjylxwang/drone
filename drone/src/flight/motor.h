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
    void setMotorSpeed(byte motor, int speed);
    int getMotorSpeed(byte motor);
    void adjustMotorSpeed(byte motor, int speedChange);


private:
    byte pins[MOTOR_COUNT];
    int speeds[MOTOR_COUNT];
    int previousSpeeds[MOTOR_COUNT];
};

#endif