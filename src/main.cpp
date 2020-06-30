#include <MIDI_controls.hpp>
#include <button.hpp>
#include <rotary_encoder.hpp>
#include <pot.hpp>

/*
/dev/cu.usbmodemMIDI1
TO DO:
HW:
- reading from multiplexed inputs
* buttons with debouncing
* rotary encoder
  * adjustable scroll speed, reading as a function with return value
* potentiometer with debouncing/not jumping around
- possible LED output for each control
- 4x7 segment display driver

SW:
- SENDING MIDI MESSAGES
  - functions for different types of input (press/toggle/update)
- keeping state of loop size and jump size (displayed on display)
  - sending particular MIDI messages
*/

const int buttons_size = 3;
const int buttons[buttons_size] = {5, 6, 7};
const int encoders_size = 1;
const int pots_size = 2;
const int pots[pots_size] = {A0, A1};
const int controls_size = buttons_size + encoders_size + pots_size;
ControlElement *controls[controls_size];

void setup()
{
  Serial.begin(9600);
  PushButton a = PushButton(buttons[0]);
  a.setup();
  controls[0] = &a;
  PushButton b = PushButton(buttons[1]);
  b.setup();
  controls[1] = &b;
  PushButton c = PushButton(buttons[2]);
  c.setup();
  controls[2] = &c;
  // for(int i = 0; i < buttons_size; i++){
  //   PushButton b = PushButton(buttons[i]);
  //   b.setup();
  //   controls[i] = &b;
  // }
  RotaryEncoder e = RotaryEncoder(3, 4);
  e.setup();
  controls[buttons_size] = &e;
  Pot p = Pot(pots[0]);
  p.setup();
  controls[buttons_size + encoders_size] = &p;
  Pot r = Pot(pots[1]);
  r.setup();
  controls[buttons_size + encoders_size + 1] = &r;
}

void loop()
{
  for (int i = 0; i < controls_size; i++)
  {
    controls[i]->read_value();
  }
  for (int i = 0; i < controls_size; i++)
  {
    if (controls[i]->changed)
    {
      int v = controls[i]->get_value();
      Serial.println(v);
      controls[i]->changed = false;
    }
    else
    {
      // Serial.println("no change");
      // delay(500);
    }
  }
  // loop_midi();
}