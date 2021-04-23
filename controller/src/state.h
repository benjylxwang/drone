#ifndef STATE_H
#define STATE_H

#include <Arduino.h>

// Global state object - used for passing state of sensors and user signal to other hardware objects
class State {
public:
    State() {
    }

    // Sensor results
    float speed;
    double altitude;
    double pitch;
    double roll;

};

#endif