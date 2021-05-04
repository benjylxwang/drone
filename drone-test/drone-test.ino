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

double PITCH_KP = 0.72;
double PITCH_KI = 0.006;
double PITCH_KD = 1.22;
double ROLL_KP = 0.7;
double ROLL_KI = 0.006;
double ROLL_KD = 1.2;

boolean runningTest;
unsigned long startTime;
unsigned long timer;
unsigned long TIMER_LENGTH = 10 * 1000; // 10 seconds
void setup()
{
    Serial.begin(SERIAL_BAUD_RATE);
    Serial.println(VERSION);
    sensors.setup();
    flightControl.setup();
    controller.setup();

    startTime = millis();
    runningTest = false;
}

void printSettings()
{
    Serial.print("P_p(0): ");
    Serial.print(PITCH_KP);
    Serial.print(" P_i(1): ");
    Serial.print(PITCH_KI);
    Serial.print(" P_d(2): ");
    Serial.print(PITCH_KD);
    Serial.print(" R_p(3): ");
    Serial.print(ROLL_KP);
    Serial.print(" R_i(4): ");
    Serial.print(ROLL_KI);
    Serial.print(" R_d(5): ");
    Serial.println(ROLL_KD);
}

void setValueOf(double &value)
{
    Serial.print("> Please enter a value: ");
    String val = Serial.readStringUntil('\n');

    value = val.toDouble();
}

void loop()
{
    if (runningTest)
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

        if (millis() - timer > TIMER_LENGTH) {
            gState.signal->upMotion = -CONTROLLER_ANALOG_MAX_VALUE;
            runningTest = false;
        }

        // Then reflect changes in state in hardware
        flightControl.update(gState, deltaTime, PITCH_KP, PITCH_KI, PITCH_KD, ROLL_KP, ROLL_KI, ROLL_KD);

#if VERBOSE
        Serial.print(". ");
        Serial.println(VERSION);
#endif
    }
    else
    {
        // Do test setup
        while (true)
        {
            printSettings();
            int action = Serial.read();

            switch (action)
            {
            case '0':
                setValueOf(PITCH_KP);
                break;
            case '1':
                setValueOf(PITCH_KI);
                break;
            case '2':
                setValueOf(PITCH_KD);
                break;
            case '3':
                setValueOf(ROLL_KP);
                break;
            case '4':
                setValueOf(ROLL_KI);
                break;
            case '5':
                setValueOf(ROLL_KD);
                break;
            case 's':
            case 'S':
                // Run test
                goto test;
                break;
            default:
                break;
            }
        }

    test:
        runningTest = true;
        Serial.println("Running test with the following values: ");
        printSettings();
        startTime = millis();
        timer = millis();
    }
}
