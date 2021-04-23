#ifndef SENSORS_H
#define SENSORS_H

#include "../state.h"
#include <SFE_BMP180.h>

class Sensors
{
public:
    Sensors();

    void setup();
    void update(State& state);
private:
    // Gyro
    const int gryo_addr = 0x68;
    void readGyro(State &state);

    // Pressure
    SFE_BMP180 pressure;
    double readPressure(State& state);
    double baseline;
};

#endif