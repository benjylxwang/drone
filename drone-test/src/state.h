#ifndef STATE_H
#define STATE_H

#include "signal.h"
#include <Arduino.h>

// Global state object - used for passing state of sensors and user signal to other hardware objects
class State {
public:
    State() {
    }

    // Sensor results
    float speed;
    double altitude;
    double angleX, angleY;
    
    // Pressure sensor
    double temperature, pressure;

    // Incoming signal from controller
    Signal* signal;

    void print() {
        Serial.print("(");
        Serial.print(angleX);
        Serial.print(",");
        Serial.print(angleY);
        Serial.print(") ");
        Serial.print("\t");
    
    }

};

#endif