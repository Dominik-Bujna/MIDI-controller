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
    changed = encoder->changed;
}

int RotaryEncoderPinA::get_value(){
    encoder->get_value();
    encoder->changed = false;
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