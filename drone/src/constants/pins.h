#ifndef PINS_H
#define PINS_H

// ------------- PINS ----------------
// == Sensors
#define I2C_SDA 4
#define I2C_SCL 5

// == Motors - Throttle
#define MOTOR_FRONT_LEFT_PIN 0
#define MOTOR_FRONT_RIGHT_PIN 1
#define MOTOR_BACK_LEFT_PIN 2
#define MOTOR_BACK_RIGHT_PIN 3

// == RF Receiver
#define RF_CE_PIN 49
#define RF_CSN_PIN 53

// MOSI pins for receiver (These are fixed for different arduino types: we are using an Arduino Mega2560)
#define RF_SCK_PIN 52
#define RF_MISO PIN 50
#define RF_MOSI_PIN 51


#endif