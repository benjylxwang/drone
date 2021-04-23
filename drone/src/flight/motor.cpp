#include "motor.h"

#include "../smoothing.h"
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
    for (int i = 0; i < MOTOR_COUNT; i++)
    {
        pinMode(pins[i], OUTPUT);
        setMotorSpeed(i, 0);
    }
}

void Motor::setMotorSpeed(byte motor, int speed)
{
    int smoothedSpeed = smoothing(speed, previousSpeeds[motor], MOTOR_SMOOTHING_FACTOR);
    analogWrite(pins[motor], smoothedSpeed);
    previousSpeeds[motor] = speeds[motor];
    speeds[motor] = smoothedSpeed;
}

int Motor::getMotorSpeed(byte motor)
{
    return speeds[motor];
}

void Motor::adjustMotorSpeed(byte motor, int speedChange)
{
    int current = speeds[motor];
    setMotorSpeed(motor, current + speedChange);
}