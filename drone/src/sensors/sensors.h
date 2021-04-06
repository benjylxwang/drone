#ifndef SENSORS_H
#define SENSORS_H

#include "../state.h"

class Sensors
{
public:
    Sensors();

    void setup();
    void update(State& state);
private:
};

#endif