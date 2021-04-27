#ifndef MOTOR_H
#define MOTOR_H

#include <Arduino.h>
#include <Servo.h>
#include "../state.h"
#include "../../constants.h"

class Motor
{
public:
    Motor(byte frontLeftPin, byte frontRightPin, byte backLeftPin, byte backRightPin);

    void setup();
    void setMotorSpeed(byte motor, int speed);
    int getMotorSpeed(byte motor);

private:
    byte pins[MOTOR_COUNT];
    Servo escs[MOTOR_COUNT];
    int speeds[MOTOR_COUNT];
    int previousSpeeds[MOTOR_COUNT];
};

#endif