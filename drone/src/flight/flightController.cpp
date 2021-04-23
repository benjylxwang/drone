#include "flightController.h"

FlightController::FlightController() : motor(MOTOR_FRONT_LEFT_PIN, MOTOR_FRONT_RIGHT_PIN, MOTOR_BACK_LEFT_PIN, MOTOR_BACK_RIGHT_PIN)
{
}

void FlightController::setup()
{
    motor.setup();

    // Initial target values
    targetPitch = 0;
    targetRoll = 0;
}

void FlightController::update(State current)
{
    // Adjust motors based on current state to be closer to target pitch and roll
    int frontBackAdjust = calculateAdjustment(current.pitch, targetPitch);
    int leftRightAdjust = calculateAdjustment(current.roll, targetRoll);

    // Apply calculated changes to motors
    motor.adjustMotorSpeed(MOTOR_FRONT_LEFT, frontBackAdjust + leftRightAdjust);
    motor.adjustMotorSpeed(MOTOR_FRONT_RIGHT, frontBackAdjust - leftRightAdjust);
    motor.adjustMotorSpeed(MOTOR_BACK_LEFT, -frontBackAdjust + leftRightAdjust);
    motor.adjustMotorSpeed(MOTOR_BACK_RIGHT, -frontBackAdjust - leftRightAdjust);
}

int FlightController::calculateAdjustment(double current, double target)
{
    double diff = target - current;

    // Adjust relative speeds of motors
    return diff * MOTOR_ADJUSTMENT_CONSTANT;
}