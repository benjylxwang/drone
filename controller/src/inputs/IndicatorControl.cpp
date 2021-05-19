#include "IndicatorControl.h"

IndicatorControl::IndicatorControl(byte leftPin_, byte rightPin_, byte mode_/* = INPUT*/, bool invert_ /*= false*/)
{
    leftPin = leftPin_;
    rightPin = rightPin_;
    invert = invert_;
    mode = mode_;
}

void IndicatorControl::setup()
{
    pinMode(leftPin, mode);
    pinMode(rightPin, mode);
}

int8_t IndicatorControl::get()
{
    int left = digitalRead(leftPin);
    int right = digitalRead(rightPin);

    if (left == HIGH && right == LOW)
    {
        if (invert) return 1;
        else return -1;
    }
    else if (left == LOW && right == HIGH)
    {
        if (invert) return -1;
        else return 1;
    }
    else
    {
        return 0;
    }
}