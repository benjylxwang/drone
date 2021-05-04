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
    pitchError = 0;
    rollError = 0;
    pitchI = 0;
    rollI = 0;
}

void FlightController::update(State current, unsigned long deltaTime, double PITCH_KP, double PITCH_KI, double PITCH_KD, double ROLL_KP, double ROLL_KI, double ROLL_KD)
{
    // Set target pitch and roll based on left/right/front/back commands
    targetPitch = map(current.signal->forwardsMotion, -512.0, 511.0, BACKWARD_TARGET_ANGLE, FORWARD_TARGET_ANGLE);
    targetRoll = map(current.signal->rightMotion, -512.0, 511.0, LEFT_TARGET_ANGLE, RIGHT_TARGET_ANGLE);

    // Up down adjustment
    int thrust = map(current.signal->upMotion, -512.0, 511.0, ESC_MIN_THROTTLE, ESC_MAX_THROTTLE);

    #if VERBOSE
        Serial.print("Tp: ");
        Serial.print(targetPitch);
        Serial.print(" Tr: ");
        Serial.print(targetRoll);
        Serial.print(" T: ");
        Serial.print(thrust);
        Serial.print(" ");
    #endif

    // Adjust motors based on current state to be closer to target pitch and roll
    double rollPID = 0;
    double pitchPID = 0;
    if (thrust > ESC_MIN_THROTTLE) {
        pitchPID = calculateAdjustment(current.angleX, targetPitch, PITCH_KP, PITCH_KI, PITCH_KD, pitchI, pitchError, deltaTime);
        rollPID = calculateAdjustment(current.angleY, targetRoll, ROLL_KP, ROLL_KI, ROLL_KD, rollI, rollError, deltaTime);

        #if VERBOSE
            Serial.print("pI: ");
            Serial.print(pitchI);
            Serial.print(" pE: ");
            Serial.print(pitchError);
            Serial.print(" rI: ");
            Serial.print(rollI);
            Serial.print(" rE: ");
            Serial.print(rollError);
            Serial.print(" ");
        #endif
    }

    // Apply calculated changes to motors
    motor.setMotorSpeed(MOTOR_FRONT_LEFT, thrust + rollPID - pitchPID);
    motor.setMotorSpeed(MOTOR_FRONT_RIGHT, thrust - rollPID - pitchPID);
    motor.setMotorSpeed(MOTOR_BACK_LEFT, thrust + rollPID + pitchPID);
    motor.setMotorSpeed(MOTOR_BACK_RIGHT, thrust - rollPID + pitchPID);
}

double FlightController::calculateAdjustment(double current, double target, double kp, double ki, double kd, double& previousI, double& prevError, unsigned long deltaTime)
{
    // PID loop - proportional integral derivative
    double error = target - current;
    
    double p = kp * error;

    double i = previousI;
    if (-3 < error < 3) {
        i = i + (ki * error);
        previousI = i;
    }

    double d = kd * (error - prevError) / deltaTime / 1000; 

    // Store previous error
    prevError = error;
    return p + i + d;
}