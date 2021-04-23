#ifndef CONSTANTS_H
#define CONSTANTS_H

#define VERBOSE 1

// ===== PINS =====
// RF Sender
#define RF_CE_PIN 9
#define RF_CSN_PIN 10

// = movement pins
#define THROTTLE_PIN A1
#define TURNING_PIN A2
#define VERTICAL_PIN A3

// MOSI pins for sender (These are fixed for different arduino types)
#define RF_SCK_PIN 13
#define RF_MISO PIN 12
#define RF_MOSI_PIN 11

// ==== RF Sender Settings
#define RF_CONTROLLER_ID 0
#define RF_DRONE_ID 3

#endif
