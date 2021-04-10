#include <Arduino.h>

#include "constants.h"

#include "src/state.h"
#include "src/sensors/sensors.h"

#include "src/flight/flightController.h"

// Global state
State gState;

// Flight
FlightController flightControl;

// Sensors
Sensors sensors;

// Controls
#if USE_FAKE_CONTROLLER
#include "src/testing/fakeController.h"
FakeController controller;
#else
#include "src/receiver/controller.h"
Controller controller(RF_CE_PIN, RF_CSN_PIN);
#endif

void setup()
{
#if VERBOSE
    Serial.begin(SERIAL_BAUD_RATE);
    Serial.println(VERSION);
#endif
    sensors.setup();
    flightControl.setup();
    controller.setup();
}

void loop()
{
    // Read sensors first to get correct state object
    sensors.update(gState);
    gState.print();

    // Get controls
    controller.update(gState);

    // Then reflect changes in state in hardware
    flightControl.update(gState);
}
