#include <Arduino.h>

#include "constants.h"

#include "src/state.h"
#include "src/flight/flightController.h"
#include "src/sensors/sensors.h"


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
    #endif
    sensors.setup();
    flightControl.setup();
    controller.setup();
}

void loop()
{
    digitalWrite(LED_BUILTIN, HIGH); // turn the LED on (HIGH is the voltage level)
    #if VERBOSE
        Serial.println(VERSION);
    #endif
    // Read sensors first to get correct state object
    sensors.update(gState);
    gState.print();
    digitalWrite(LED_BUILTIN, LOW); // turn the LED off by making the voltage LOW

    // Get controls
    controller.update(gState);

    // Then reflect changes in state in hardware
    flightControl.update(gState);
}
