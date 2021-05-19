#ifndef INPUT_H
#define INPUT_H

#include <stdint.h>
#include <Arduino.h>
#include "../constants.h"

class Input
{
public:
    Input(){};

    // Controls
    int16_t throttle;
    int16_t turning;
    int16_t vertical;

    #if MANUAL_TUNING_MODE
    // PID constants
    float pitchP, pitchI, pitchD;
    float rollP, rollI, rollD;

    void printConstants() {
        Serial.print("Pp(1): ");
        Serial.print(pitchP);
        Serial.print(" Pi(2): ");
        Serial.print(pitchI);
        Serial.print(" Pd(3): ");
        Serial.print(pitchD);
        Serial.print(" Rp(4): ");
        Serial.print(rollP);
        Serial.print(" Ri(5): ");
        Serial.print(rollI);
        Serial.print(" Rd(6): ");
        Serial.print(rollD);
        Serial.println();
    }
    #endif
};

#endif