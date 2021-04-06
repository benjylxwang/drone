#include "flightController.h"

FlightController::FlightController() : motor(MOTOR_FRONT_LEFT_PIN, MOTOR_FRONT_RIGHT_PIN, MOTOR_BACK_LEFT_PIN, MOTOR_BACK_RIGHT_PIN)
{

}

void FlightController::setup() {
    motor.setup();
}

void FlightController::update(State state) {

}