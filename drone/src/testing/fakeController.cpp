#include <Arduino.h>

#include "fakeController.h"
#include "../signal.h"

#include "../../constants.h"

FakeController::FakeController(){};

void FakeController::setup() {
    #if !VERBOSE
    // Begin serial if haven't already
    Serial.begin(SERIAL_BAUD_RATE);
    #endif
}

void FakeController::update(State& state) {
    byte instruction = Serial.read();

    if (state.signal == NULL) state.signal = (Signal*) calloc(1, sizeof(Signal));

    switch (instruction)
    {
    case 's': // Put a fake speed value in
        state.speed = 75.23;
        break;
    case 'S': // 'Stop' vehicle
        state.speed = 0;
        break;
    default:
        break;
    }
}