#include <pinmap.hpp>
#include <control_element.hpp>
#include <rotary_encoder.hpp>

class RotaryEncoderPinA : public ControlElement
{
public:
    RotaryEncoderPinA(RotaryEncoder *enc);
    ~RotaryEncoderPinA();
    virtual void read_value();
    virtual int get_value();
    virtual void setup();

private:
    RotaryEncoder *encoder;
};

class RotaryEncoderPinB : public ControlElement
{
public:
    RotaryEncoderPinB(RotaryEncoder *enc);
    ~RotaryEncoderPinB();
    virtual void read_value();
    virtual int get_value();
    virtual void setup();

private:
    RotaryEncoder *encoder;
};