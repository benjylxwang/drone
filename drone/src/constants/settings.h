#ifndef SETTINGS_H
#define SETTINGS_H

// ===== Controller Settings
#define RF_CONTROLLER_ID 0
#define RF_DRONE_ID 3
#define CONTROLLER_ANALOG_MAX_VALUE 512

// ===== Motor Settings
#define MOTOR_COUNT 4
#define MOTOR_FRONT_LEFT 0
#define MOTOR_FRONT_RIGHT 1
#define MOTOR_BACK_LEFT 2
#define MOTOR_BACK_RIGHT 3
#define MOTOR_ADJUSTMENT_CONSTANT 0.2
#define MOTOR_SMOOTHING_FACTOR 0.9

// ===== ESC Settings
#define ESC_MIN_THROTTLE		        0
#define ESC_MAX_THROTTLE		        180
#define ESC_MIN_MICROSECONDS 1000
#define ESC_MAX_MICROSECONDS 2000

// ==== Pitch/Roll settings
#define FORWARD_TARGET_ANGLE 30
#define BACKWARD_TARGET_ANGLE -FORWARD_TARGET_ANGLE
#define RIGHT_TARGET_ANGLE 30
#define LEFT_TARGET_ANGLE -RIGHT_TARGET_ANGLE

// ==== Sensor Settings
#define ALTITUDE 50.0

#define ACCELEROMETER_SMOOTHING_FACTOR 0.8
#define GYRO_SMOOTHING_FACTOR 0.8
#define TEMPERATURE_SMOOTHING_FACTOR 0.9
#define PRESSURE_SMOOTHING_FACTOR 0.9

#endif