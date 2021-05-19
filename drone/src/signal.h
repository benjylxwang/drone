#ifndef SIGNAL_H
#define SIGNAL_H

#include <stdint.h>
#include "../constants.h"

class Signal
{
public:
    // Steering controls + throttle
    int16_t forwardsMotion;
    int16_t rightMotion;
    int16_t upMotion;

    #if CONTROLLER_TEST_MODE
    // PID constants
    float pitchP, pitchI, pitchD;
    float rollP, rollI, rollD;
    #endif
};

#endif