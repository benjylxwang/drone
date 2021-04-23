#include <Arduino.h>

int16_t smoothing(int16_t input, int16_t previous, double alpha)
{
    return alpha * input + (1 - alpha) * previous;
}

double smoothing(double input, double previous, double alpha)
{
    return alpha * input + (1 - alpha) * previous;
}

int smoothing(int input, int previous, double alpha)
{
    return alpha * input + (1 - alpha) * previous;
}