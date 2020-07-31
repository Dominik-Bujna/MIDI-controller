#pragma once
#include <Arduino.h>
class ControlElement
{
public:
    ControlElement(){};
    virtual ~ControlElement(){};
    virtual void read_value() = 0;
    virtual int get_value();
    virtual void setup();
    virtual bool is_button(){return false;};
    virtual bool is_encoder(){return false;};
    virtual bool is_pot(){return false;};
    int index; // assigns this control to array used in translation to midi
    bool changed;
};