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
    double pitch;
    double roll;
    // Gyro
    int16_t AcX,AcY,AcZ,Tmp,GyX,GyY,GyZ;
    // Pressure sensor
    double temperature, pressure;

    // Incoming signal from controller
    Signal* signal;

    void print() {
        // display tab-separated accel/gyro x/y/z values
        Serial.print(altitude); Serial.print("\t");
        Serial.print(pitch); Serial.print("\t");
        Serial.println(roll);
    }

};

#endif