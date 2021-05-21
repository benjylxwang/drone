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

unsigned long startTime;

void setup()
{
    #if VERBOSE
        Serial.begin(SERIAL_BAUD_RATE);
        Serial.println(VERSION);
    #endif
    sensors.setup();
    flightControl.setup();
    controller.setup();

    startTime = millis();
}

void loop()
{   
    unsigned long deltaTime = millis() - startTime;
    startTime = millis();

    digitalWrite(LED_BUILTIN, HIGH); // turn the LED on (HIGH is the voltage level)
    // Read sensors first to get correct state object
    sensors.update(gState, deltaTime);
    digitalWrite(LED_BUILTIN, LOW); // turn the LED off by making the voltage LOW
    gState.print();

    // Get controls
    controller.update(gState);

    // Then reflect changes in state in hardware
    flightControl.update(gState, deltaTime);

    #if VERBOSE
        Serial.print(". ");
        Serial.println(VERSION);
    #endif
}
