
#include <Arduino.h>
#include <stdint.h>
#include <Wire.h>
#include "sensors.h"

#include "../../constants.h"

Sensors::Sensors()
{
}

void Sensors::setup()
{
    // Wire.setSDA(I2C_SDA);
    // Wire.setSCL(I2C_SCL);
    // Setup gyro
    Wire.begin();
    Wire.beginTransmission(gryo_addr);
    Wire.write(0x6B); // PWR_MGMT_1 register
    Wire.write(0);    // Wakes up gyro
    Wire.endTransmission(true);

    // Setup pressure senesor
    if (pressure.begin())
    {
        Serial.println("BMP180 init success");
        baseline = readPressure();
    }
    else
    {

        while (1)
            Serial.println("BMP180 init fail\n\n"); // Pause forever.
    }
}

void Sensors::update(State &state)
{
    // Get gyro values
    Wire.beginTransmission(gryo_addr);
    Wire.write(0x3B); // starting with register 0x3B (ACCEL_XOUT_H)
    Wire.endTransmission(false);
    Wire.requestFrom(gryo_addr, 14, true);      // request a total of 14 registers
    state.AcX = Wire.read() << 8 | Wire.read(); // 0x3B (ACCEL_XOUT_H) & 0x3C (ACCEL_XOUT_L)
    state.AcY = Wire.read() << 8 | Wire.read(); // 0x3D (ACCEL_YOUT_H) & 0x3E (ACCEL_YOUT_L)
    state.AcZ = Wire.read() << 8 | Wire.read(); // 0x3F (ACCEL_ZOUT_H) & 0x40 (ACCEL_ZOUT_L)
    state.Tmp = Wire.read() << 8 | Wire.read(); // 0x41 (TEMP_OUT_H) & 0x42 (TEMP_OUT_L)
    state.GyX = Wire.read() << 8 | Wire.read(); // 0x43 (GYRO_XOUT_H) & 0x44 (GYRO_XOUT_L)
    state.GyY = Wire.read() << 8 | Wire.read(); // 0x45 (GYRO_YOUT_H) & 0x46 (GYRO_YOUT_L)
    state.GyZ = Wire.read() << 8 | Wire.read(); // 0x47 (GYRO_ZOUT_H) & 0x48 (GYRO_ZOUT_L)

    // Run pressure update
    double P;
    P = readPressure();
    state.altitude = pressure.altitude(P, baseline);
}

double Sensors::readPressure()
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
            status = pressure.startPressure(3);
            if (status != 0)
            {
                delay(status);
                status = pressure.getPressure(P, T);
                if (status != 0)
                {
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