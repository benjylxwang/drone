#ifndef STATE_H
#define STATE_H

#include "signal.h"

// Global state object - used for passing state of sensors and user signal to other hardware objects
class State {
public:
    State() {
    }

    // Sensor results
    float speed;
    float altitude;

    // Incoming signal from controller
    Signal* signal;

};

#endif