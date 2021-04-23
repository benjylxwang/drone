#include "sender.h"
#include "../constants.h"

#include <SPI.h>
#include <NRFLite.h>

Sender::Sender(byte cePin_, byte csPin_)
{
    cePin = cePin_;
    csnPin = csPin_;
}

void Sender::setup()
{
    radio.init(RF_CONTROLLER_ID, cePin, csnPin);
}

void Sender::send(Input& input, State& state)
{
    // Format input object as protocol payload and send
    char data[32] = {0};

    // Throttle turning vertical(int16_t)
    int16_t* i16 = (int16_t*) &data[0];
    *i16 = input.throttle;
    i16++;
    *i16 = input.turning;
    i16++;
    *i16 = input.vertical;   

    // Send payload
    radio.send(RF_DRONE_ID, &data, sizeof(data));

    // Check for sensor data in ack
    if (radio.hasAckData()) {
        char ackData[32] = {0};
        // Get sensor data from ack
        radio.readData(&ackData);

        // Parse data into sensor state object
        // Speed
        float* f = (float*) &ackData[0];
        state.speed = *f++;
        
        // Altitude, Pitch, Roll
        double* d = (double*) &ackData[4];
        state.altitude = *d++;
        state.pitch = *d++;
        state.roll = *d++;
    }
}