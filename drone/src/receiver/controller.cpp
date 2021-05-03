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
    SPI.setSCK(RF_SCK_PIN);
    SPI.setRX(RF_MISO_RX_PIN);
    SPI.setTX(RF_MOSI_TX_PIN);
    SPI.setCS(RF_CSN_PIN);
    success = radio.init(RF_DRONE_ID, cePin, csnPin);
    lastReceived = millis();
}

void Controller::update(State &state)
{
    if (success) {
        
        // If we have data, fill, otherwise, set state usersignal to null
        if (radio.hasData())
        {
            // Wipe previous usersignal
            if (state.signal)
                free(state.signal);

            // Prepare ack - will be sent back if radio data is received
            prepareAck(state);

            parseData(state);
            lastReceived = millis();
        }
        else if (millis() - lastReceived > CONTROLLER_TIMEOUT_PERIOD_MILLISECONDS)
        {
            // Thrust to zero
            state.signal->upMotion = -CONTROLLER_ANALOG_MAX_VALUE;           
            Serial.println("!!! --- Safety cutout --- !!!");
        }
    } else {
        #if VERBOSE
        Serial.println("Radio failed to setup!");
        #endif
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
    // Speed
    float* f = (float*) &data[0];
    *f = state.speed;

    // Altitude, pitch, roll
    double* d = (double*) &data[4];
    *d = state.altitude;
    d++;
    *d = state.pitch;
    d++;
    *d = state.roll;

    // Add new ack data to pipeline and remove any old data in the pipeline
    radio.addAckData(data, 32, true);
}