#include "controller.h"
#include <Arduino.h>
#include <SPI.h>

Controller::Controller(byte cePin_, byte csPin_)
{
    cePin = cePin_;
    csnPin = csPin_;
}

void Controller::setup()
{
    radio.init(RF_CAR_ID, cePin, csnPin);
}

void Controller::update(State &state)
{
    // Wipe previous usersignal
    if (state.signal)
        free(state.signal);

    // Prepare ack - will be sent back if radio data is received
    prepareAck(state);
    
    // If we have data, fill, otherwise, set state usersignal to null
    if (radio.hasData())
    {
        parseData(state);
    }
    else
    {
        state.signal = nullptr;
    }
}

void Controller::parseData(State &state)
{
    char data[32] = {0};
    radio.readData(&data);
    state.signal = (Signal *) calloc(1, sizeof(Signal));

    // === Process data === Change stuff here if changing protocol
    // motion data
    int16_t *motion = (int16_t *)&data[0];
    state.signal->forwardsMotion = *motion;
    motion++;
    state.signal->rightMotion = *motion;
    motion++;
    state.signal->upMotion = *motion;

#if VERBOSE
    Serial.print("Motion: (");
    Serial.print(state.signal->forwardsMotion);
    Serial.print(", ");
    Serial.print(state.signal->rightMotion);
    Serial.print(", ");
    Serial.print(state.signal->upMotion);
    Serial.print(")");
    Serial.println();
#endif
}

void Controller::prepareAck(State& state) {
    char data[32] = {0};

    // Fill data structure according to protocol
    // Position/Rotation
    float* f = (float*) &data[0];
    *f = state.speed;
    f++;
    *f = state.altitude;

    // Add new ack data to pipeline and remove any old data in the pipeline
    radio.addAckData(data, 32, true);
}