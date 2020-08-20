#pragma once
#include <pinmap.hpp>
#include <control_element.hpp>

class RotaryEncoder : public ControlElement
{
public:
    RotaryEncoder(int pin1, int pin2);
    ~RotaryEncoder();
    virtual void read_value();
    virtual int get_value();
    virtual void setup();
    virtual bool is_encoder();
    void read_1();
    void read_2();
    //pin 1 always has to preceed pin 2 when connected to multiplexer
    int pin_1;
    int pin_2;
    double scroll_multiplier;
    double step_size;
    int num_values;
    int value;

private:
    int last_state;
    int position;
};