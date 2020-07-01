#include <rotary_encoder.hpp>

RotaryEncoder::RotaryEncoder(int pin1, int pin2)
{
  pin_1 = pin1;
  pin_2 = pin2;
  last_state = 0;
  position = 0;
  scroll_multiplier = 1;
}
RotaryEncoder::~RotaryEncoder() {}

void RotaryEncoder::read_value()
{
  // int state_1 = digitalRead(pin_1);
  // if (state_1 != last_state) {
  //   if (digitalRead(pin_2) != state_1) {
  //     position--;
  //   } else {
  //     position++;
  //   }
  // }
  // last_state = state_1;
  read_1();
  read_2();
}
int RotaryEncoder::get_value()
{
  return position%127;
}

void RotaryEncoder::setup()
{
  pinMode(pin_1, INPUT);
  pinMode(pin_2, INPUT);
}

void RotaryEncoder::read_1()
{
  int state_1 = digitalRead(pin_1);
  if (state_1 != last_state)
  {
    changed = true;
  }
  last_state = state_1;
}

void RotaryEncoder::read_2()
{
  if (changed)
  {
    if (digitalRead(pin_2) != last_state)
    {
      position--;
    }
    else
    {
      position++;
    }
  }
}