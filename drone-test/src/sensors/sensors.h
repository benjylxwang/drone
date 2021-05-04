#ifndef SENSORS_H
#define SENSORS_H

#include "../state.h"
#include <SFE_BMP180.h>
#include <MPU6050_light.h>

class Sensors
{
public:
    Sensors();

    void setup();
    void update(State& state, unsigned long deltaTime);

    void calibrate();
private:
    // Gyro
    MPU6050 mpu;
    const int gyro_addr = 0x68;

    // Pressure
    SFE_BMP180 pressure;
    double readPressure(State& state);
    double baseline;
};

#endif