#include <multiplexer.hpp>


Multiplexer::Multiplexer(){
    // for(int i = 0; i < pins_length; i++){
    //     pin_addresses[i] = -1;
    // }
}
Multiplexer::Multiplexer(int pinA, int pinB, int pinC, int pinIO){
    pin_A = pinA;
    pin_B = pinB;
    pin_C = pinC;
    pin_IO = pinIO;
}

//updates all of the I/Os
void Multiplexer::update()
{   
    for (int i = 0b000; i <= 0b111; i++)
    {
        digitalWrite(pin_A, (i & 1 << 0));
        digitalWrite(pin_B, (i & 1 << 1));
        digitalWrite(pin_C, (i & 1 << 2));
        (*read[i])();
        Serial.println(i);
    }
}
void Multiplexer::setup()
{
    pinMode(pin_A, OUTPUT);
    pinMode(pin_B, OUTPUT);
    pinMode(pin_C, OUTPUT);
    pinMode(pin_IO, INPUT);
}

void Multiplexer::assign_pin(int pin_n, void (*read_func)()){
    read[pin_n] = read_func;
}