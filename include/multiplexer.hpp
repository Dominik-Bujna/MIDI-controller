#include <Arduino.h>
class Multiplexer
{

    int pin_A;
    int pin_B;
    int pin_C;
    int pin_IO;

    //updates all of the I/Os
    void update();

    void setup();
};