#include <rotary_encoder_pin.hpp>

RotaryEncoderPinA::RotaryEncoderPinA(RotaryEncoder *enc)
{
    encoder = enc;
}

RotaryEncoderPinA::~RotaryEncoderPinA()
{
}

void RotaryEncoderPinA::read_value()
{
    encoder->read_1();
}

int RotaryEncoderPinA::get_value(){
    
}
void RotaryEncoderPinA::setup(){

}
RotaryEncoderPinB::RotaryEncoderPinB(RotaryEncoder *enc)
{
    encoder = enc;
}

RotaryEncoderPinB::~RotaryEncoderPinB()
{
}

void RotaryEncoderPinB::read_value()
{
    encoder->read_2();
}

int RotaryEncoderPinB::get_value(){

}
void RotaryEncoderPinB::setup(){

}