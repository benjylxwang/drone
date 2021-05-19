
#include <Arduino.h>
#include <stdint.h>
#include <Wire.h>
#include <math.h>
#include "sensors.h"

#include "../../constants.h"
#include "../smoothing.h"

Sensors::Sensors() : mpu(Wire)
{
}

void Sensors::setup()
{
    pinMode(LED_BUILTIN, OUTPUT);

    Wire.setSDA(I2C_SDA);
    Wire.setSCL(I2C_SCL);
    Wire.begin();

    if (mpu.begin() != 0) {
        // Error
        while(1) Serial.println("MPU6050 Failed to initialize\n");
    }
    calibrate();

    // Setup pressure senesor
    // if (pressure.begin())
    // {
    //     Serial.println("BMP180 init success");
    //     State temp;
    //     baseline = readPressure(temp);
    // }
    // else
    // {

    //     while (1)
    //         Serial.println("BMP180 init fail\n\n"); // Pause forever.
    // }
}

void Sensors::update(State &state, unsigned long deltaTime)
{
    mpu.update();
    state.angleX = mpu.getAngleX();
    state.angleY = mpu.getAngleY();

    // Run pressure update
    // readPressure(state);
    // state.altitude = pressure.altitude(state.pressure, baseline);
}

void Sensors::calibrate()
{
    // mpu.calcOffsets();
}

double Sensors::readPressure(State& state)
{
    char status;
    double T, P, p0, a;
    status = pressure.startTemperature();
    if (status != 0)
    {
        delay(status);
        status = pressure.getTemperature(T);
        if (status != 0)
        {
            state.temperature = smoothing(T, state.temperature, TEMPERATURE_SMOOTHING_FACTOR);
            status = pressure.startPressure(3);
            if (status != 0)
            {
                delay(status);
                status = pressure.getPressure(P, T);
                if (status != 0)
                {
                    state.pressure = smoothing(P, state.pressure, PRESSURE_SMOOTHING_FACTOR);
                    return (P);
                }
                else
                    Serial.println("error retrieving pressure measurement\n");
            }
            else
                Serial.println("error starting pressure measurement\n");
        }
        else
            Serial.println("error retrieving temperature measurement\n");
    }
    else
        Serial.println("error starting temperature measurement\n");
}