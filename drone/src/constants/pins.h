#ifndef PINS_H
#define PINS_H

// ------------- PINS ----------------
// == Sensors
#define I2C_SDA 12
#define I2C_SCL 13

// == Motors - Throttle
#define MOTOR_FRONT_LEFT_PIN 18
#define MOTOR_FRONT_RIGHT_PIN 20
#define MOTOR_BACK_LEFT_PIN 19
#define MOTOR_BACK_RIGHT_PIN 21

// == RF Receiver - SPI Pins
#define RF_CE_PIN 1
#define RF_SCK_PIN 2
#define RF_MOSI_TX_PIN 3
#define RF_MISO_RX_PIN 4
#define RF_CSN_PIN 5

// == Fake controller
#define POTENTIOMETER_READ_PIN A1


#endif