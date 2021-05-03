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

void setup()
{
#if VERBOSE
    Serial.begin(115200);
#endif

    sender.setup();

    // Inputs
    throttle.setup();
    turning.setup();
    vertical.setup();
}

void loop()
{
    Input input;
    // Gather input data
    input.throttle = throttle.get();
    input.turning = turning.get();
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
