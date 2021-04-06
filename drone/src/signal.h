#ifndef SIGNAL_H
#define SIGNAL_H

#include <stdint.h>

class Signal
{
public:
    // Steering controls + throttle
    int16_t forwardsMotion;
    int16_t rightMotion;
    int16_t upMotion;
};

#endif