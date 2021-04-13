
#include <Arduino.h>
#include <stdint.h>
#include <Wire.h>
#include <math.h>
#include "sensors.h"

#include "../../constants.h"

Sensors::Sensors()
{
}

void Sensors::setup()
{
    pinMode(LED_BUILTIN, OUTPUT);

    Wire.setSDA(I2C_SDA);
    Wire.setSCL(I2C_SCL);
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
        State temp;
        baseline = readPressure(temp);
    }
    else
    {

        while (1)
            Serial.println("BMP180 init fail\n\n"); // Pause forever.
    }
}

void Sensors::update(State &state)
{
    digitalWrite(LED_BUILTIN, HIGH); // turn the LED on (HIGH is the voltage level)
    readGyro(state);

    // Run pressure update
    readPressure(state);
    state.altitude = pressure.altitude(state.pressure, baseline);
    delay(50);
    digitalWrite(LED_BUILTIN, LOW); // turn the LED off by making the voltage LOW
    delay(50);
}

void Sensors::readGyro(State &state)
{
    // Get gyro values
    Wire.beginTransmission(gryo_addr);
    Wire.write(0x3B); // starting with register 0x3B (ACCEL_XOUT_H)
    Wire.endTransmission(false);
    Wire.requestFrom(gryo_addr, 14, true); // request a total of 14 registers

    // Apply smoothing to values
    state.AcX = smoothing(Wire.read() << 8 | Wire.read(), state.AcX, ACCELEROMETER_SMOOTHING_FACTOR); // 0x3B (ACCEL_XOUT_H) & 0x3C (ACCEL_XOUT_L)
    state.AcY = smoothing(Wire.read() << 8 | Wire.read(), state.AcY, ACCELEROMETER_SMOOTHING_FACTOR); // 0x3D (ACCEL_YOUT_H) & 0x3E (ACCEL_YOUT_L)
    state.AcZ = smoothing(Wire.read() << 8 | Wire.read(), state.AcZ, ACCELEROMETER_SMOOTHING_FACTOR); // 0x3F (ACCEL_ZOUT_H) & 0x40 (ACCEL_ZOUT_L)
    state.Tmp = Wire.read() << 8 | Wire.read(); // 0x41 (TEMP_OUT_H) & 0x42 (TEMP_OUT_L)
    state.GyX = smoothing(Wire.read() << 8 | Wire.read(), state.GyX, GYRO_SMOOTHING_FACTOR); // 0x43 (GYRO_XOUT_H) & 0x44 (GYRO_XOUT_L)
    state.GyY = smoothing(Wire.read() << 8 | Wire.read(), state.GyY, GYRO_SMOOTHING_FACTOR); // 0x45 (GYRO_YOUT_H) & 0x46 (GYRO_YOUT_L)
    state.GyZ = smoothing(Wire.read() << 8 | Wire.read(), state.GyZ, GYRO_SMOOTHING_FACTOR); // 0x47 (GYRO_ZOUT_H) & 0x48 (GYRO_ZOUT_L)

    // Calculate pitch/roll values
    state.pitch = 180 * atan(state.AcX / sqrt(state.AcY * state.AcY + state.AcZ * state.AcZ)) / M_PI;
    state.roll = 180 * atan(state.AcY / sqrt(state.AcX * state.AcX + state.AcZ * state.AcZ)) / M_PI;
}

int16_t Sensors::smoothing(int16_t input, int16_t previous, double alpha)
{
    return alpha * input + (1 - alpha) * previous;
}

double Sensors::smoothing(double input, double previous, double alpha)
{
    return alpha * input + (1 - alpha) * previous;
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