#include "motor.h"

#include "../../constants.h"

Motor::Motor(byte frontLeftPin, byte frontRightPin, byte backLeftPin, byte backRightPin)
{
    pins[MOTOR_FRONT_LEFT] = frontLeftPin;
    pins[MOTOR_FRONT_RIGHT] = frontRightPin;
    pins[MOTOR_BACK_LEFT] = backLeftPin;
    pins[MOTOR_BACK_RIGHT] = backRightPin;
}

void Motor::setup()
{
    for (int i = 0; i < MOTOR_COUNT; i++) {
        pinMode(pins[i], OUTPUT);
        setMotorSpeed(i, 0);
    }
}

void Motor::setMotorSpeed(byte motor, int speed)
{
    analogWrite(pins[motor], speed);
}