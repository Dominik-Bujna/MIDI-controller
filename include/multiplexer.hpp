#include <Arduino.h>
#include <control_element.hpp>
class Multiplexer
{
public:
    const int pin_A;
    const int pin_B;
    const int pin_C;
    const int pin_IO;
    ControlElement * pins[];
    //updates all of the I/Os
    void update();

    void setup();
};