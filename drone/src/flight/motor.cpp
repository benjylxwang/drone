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
        #if VERBOSE
        Serial.print("Initializing ESC ");
        Serial.print(i);
        Serial.println("...");
        #endif
        escs[i].attach(pins[i], ESC_MIN_MICROSECONDS, ESC_MAX_MICROSECONDS);
    }
}

void Motor::setMotorSpeed(byte motor, int speed)
{   
    #if VERBOSE
        Serial.print("m");
        Serial.print(motor);
        Serial.print(":");
        Serial.print(speed);
        Serial.print(" ");
    #endif
    // Cap values
    if (speed > ESC_MAX_THROTTLE) speed = ESC_MAX_THROTTLE;
    else if (speed < ESC_MIN_THROTTLE) speed = ESC_MIN_THROTTLE;

    escs[motor].writeMicroseconds(speed);
    speeds[motor] = speed;
}

int Motor::getMotorSpeed(byte motor)
{
    return speeds[motor];
}