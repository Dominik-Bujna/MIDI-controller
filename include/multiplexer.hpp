#include <Arduino.h>
#include <control_element.hpp>
class Multiplexer
{
public:
    Multiplexer();
    Multiplexer(int pinA, int pinB, int pinC, int pinIO);
    int pin_A;
    int pin_B;
    int pin_C;
    int pin_IO;
    static const int pins_length = 8;
    ControlElement * pins[pins_length];
    int pin_addresses[pins_length];
    
    //updates all of the I/Os
    void update();
    void setup();
    void setup_pullup();
    void setup_output();
    void cycle();
    void assign_pin(int pin_n, ControlElement * pin);
};