#ifndef FAKE_CONTROLLER_H
#define FAKE_CONTROLLER_H

#include "../state.h"

class FakeController
{
public:
    FakeController();

    void setup();
    void update(State& state);
};

#endif