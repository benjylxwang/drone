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
    // Set target pitch and roll based on left/right/front/back commands
    targetPitch = map(current.signal->forwardsMotion, -512, 511, BACKWARD_TARGET_ANGLE, FORWARD_TARGET_ANGLE);
    targetRoll = map(current.signal->rightMotion, -512, 511, LEFT_TARGET_ANGLE, RIGHT_TARGET_ANGLE);

    // Up down adjustment
    int thrust = map(current.signal->upMotion, -512, 511, ESC_MIN_THROTTLE, ESC_MAX_THROTTLE);

    // Adjust motors based on current state to be closer to target pitch and roll
    int frontBackAdjust = 0;
    int leftRightAdjust = 0;
    if (thrust > ESC_MIN_THROTTLE) {
        frontBackAdjust = calculateAdjustment(current.pitch, targetPitch);
        leftRightAdjust = calculateAdjustment(current.roll, targetRoll);
    }

    // Apply calculated changes to motors
    motor.setMotorSpeed(MOTOR_FRONT_LEFT, frontBackAdjust + leftRightAdjust + thrust);
    motor.setMotorSpeed(MOTOR_FRONT_RIGHT, frontBackAdjust - leftRightAdjust + thrust);
    motor.setMotorSpeed(MOTOR_BACK_LEFT, -frontBackAdjust + leftRightAdjust + thrust);
    motor.setMotorSpeed(MOTOR_BACK_RIGHT, -frontBackAdjust - leftRightAdjust + thrust);
}

int FlightController::calculateAdjustment(double current, double target)
{
    double diff = target - current;

    // Adjust relative speeds of motors - magic sauce
    return diff * MOTOR_ADJUSTMENT_CONSTANT;
}