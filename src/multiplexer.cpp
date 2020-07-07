#include <multiplexer.hpp>

//updates all of the I/Os
void Multiplexer::update()
{   
    int j = 0;
    for (int i = 0b000; i <= 0b111; i++)
    {
        digitalWrite(pin_A, (i & 1 << 0));
        digitalWrite(pin_B, (i & 1 << 1));
        digitalWrite(pin_C, (i & 1 << 2));
        pins[j]->read_value();
    }
}
void Multiplexer::setup()
{
    pinMode(pin_A, OUTPUT);
    pinMode(pin_B, OUTPUT);
    pinMode(pin_C, OUTPUT);
    pinMode(pin_IO, INPUT);
}
