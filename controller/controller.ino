#include <Arduino.h>

#include "src/sender.h"
#include "src/input.h"
#include "constants.h"
#include "src/state.h"

#include "src/inputs/JoystickAxis.h"

// RF Sender
Sender sender(RF_CE_PIN, RF_CSN_PIN);
State state;

// Movement Inputs
JoystickAxis throttle(THROTTLE_PIN);
JoystickAxis turning(TURNING_PIN);
JoystickAxis vertical(VERTICAL_PIN);

// Input to be sent to the drone
Input input;

// Specially for manual tuning
#if MANUAL_TUNING_MODE
boolean runningTest;
#endif

void setup()
{
#if VERBOSE or MANUAL_TUNING_MODE
    Serial.begin(115200);
#endif
    sender.setup();

    // Inputs
    throttle.setup();
    turning.setup();
    vertical.setup();
}

void normalOperation();
void getValueFor(float& k) {
    Serial.println("Please enter the float value here: ");
    while (!Serial.available());
    String value = Serial.readStringUntil('\n');

    k = value.toFloat();
}

void loop()
{
    #if MANUAL_TUNING_MODE
    while (true) {
        // Print current values of the PID constants
        input.printConstants();
        Serial.println("Input number of variable to change it, or 's' to start: ");
        while (!Serial.available());
        char value = Serial.read();
        switch (value)
        {
        case '1':
            getValueFor(input.pitchP);
            break;
        case '2':
            getValueFor(input.pitchI);
            break;
        case '3':
            getValueFor(input.pitchD);
            break;
        case '4':
            getValueFor(input.rollP);
            break;
        case '5':
            getValueFor(input.rollI);
            break;
        case '6':
            getValueFor(input.rollD);
            break;
        case 's':
            goto test;
            break;
        default:
            break;
        }
    }

    test:
    while (true) {
    #endif

    normalOperation();

    #if MANUAL_TUNING_MODE
        Serial.println("Enter 's' to stop test mode.");
        char value = Serial.read();
        if (value == 's') {
            // Stop
            input.throttle = 0;
            input.turning = 0;
            input.vertical = -512;
            sender.send(input, state);
            break;
        }
    }
    #endif
}

void normalOperation() {
    // Gather input data
    // input.throttle = throttle.get();
    // input.turning = turning.get();
    input.throttle = 0;
    input.turning = 0;
    input.vertical = vertical.get();

    // Send final input
    sender.send(input, state);

#if VERBOSE
    Serial.print("Speed: ");
    Serial.print(state.speed);
    Serial.print(" Pitch: ");
    Serial.print(state.pitch);
    Serial.print(" Roll: ");
    Serial.print(state.roll);
    Serial.print(" Altitude: ");
    Serial.print(state.altitude);
    Serial.print(" Throttle: ");
    Serial.print(input.throttle);
    Serial.print(" Turning: ");
    Serial.print(input.turning);
    Serial.print(" Vertical: ");
    Serial.print(input.vertical);
    Serial.println();
#endif

    delay(5);
}