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
    void read_1();
    void read_2();
    //pin 1 always has to preceed pin 2 when connected to multiplexer
    int pin_1;
    int pin_2;

private:
    int last_state;
    int position;
    int scroll_multiplier;
};