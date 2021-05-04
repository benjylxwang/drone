#ifndef SMOOTHING_H
#define SMOOTHING_H

#include <Arduino.h>

int16_t smoothing(int16_t input, int16_t previous, double alpha);
int smoothing(int input, int previous, double alpha);
double smoothing(double input, double previous, double alpha);

#endif