#ifndef INPUT_H
#define INPUT_H

#include <stdint.h>

class Input
{
public:
    Input(){};

    // Controls
    int16_t throttle;
    int16_t turning;
    int16_t vertical;
};

#endif