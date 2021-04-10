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
    // Gyro
    int16_t AcX,AcY,AcZ,Tmp,GyX,GyY,GyZ;

    // Incoming signal from controller
    Signal* signal;

    void print() {
        // display tab-separated accel/gyro x/y/z values
        Serial.print(altitude); Serial.print("\t");
        Serial.print(AcX); Serial.print("\t");
        Serial.print(AcY); Serial.print("\t");
        Serial.print(AcZ); Serial.print("\t");
        Serial.print(GyX); Serial.print("\t");
        Serial.print(GyY); Serial.print("\t");
        Serial.println(GyZ);
    }

};

#endif