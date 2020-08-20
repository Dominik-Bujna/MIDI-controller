
#if USE_MIDIUSB == 1
#include <MIDI_controls.hpp>
#endif

#include <button.hpp>
#include <rotary_encoder.hpp>
#include <rotary_encoder_pin.hpp>
#include <pot.hpp>
#include <multiplexer.hpp>

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
int modifier = 0;
int mult1IO = 12;
int mult1A = 9;
int mult1B = 10;
int mult1C = 11;

int mult2IO = 8;
int mult2A = 5;
int mult2B = 6;
int mult2C = 7;

Pot p1 = Pot(A0);
Pot p2 = Pot(A3);
Pot p3 = Pot(A4);

Multiplexer mult1 = Multiplexer(mult1A, mult1B, mult1C, mult1IO);
Multiplexer mult2 = Multiplexer(mult2A, mult2B, mult2C, mult2IO);

//mult1
PushButton b1 = PushButton(mult1IO);
PushButton b2 = PushButton(mult1IO);
PushButton b3 = PushButton(mult1IO);
PushButton b4 = PushButton(mult1IO, 3);
PushButton b5 = PushButton(mult1IO, 2);
PushButton b6 = PushButton(mult1IO);
PushButton b7 = PushButton(mult1IO, 1);
PushButton b8 = PushButton(mult1IO, 0);

//mult2
RotaryEncoder enc = RotaryEncoder(mult2IO, mult2IO);
RotaryEncoderPinA enc_1 = RotaryEncoderPinA(&enc);
RotaryEncoderPinB enc_2 = RotaryEncoderPinB(&enc);
PushButton benc_1 = PushButton(mult2IO);

RotaryEncoder enc2 = RotaryEncoder(mult2IO, mult2IO);
RotaryEncoderPinA enc2_1 = RotaryEncoderPinA(&enc2);
RotaryEncoderPinB enc2_2 = RotaryEncoderPinB(&enc2);
PushButton benc_2 = PushButton(mult2IO);

void update_modifier(ControlElement *p)
{

  int v = p->get_value();
  if (v > 0)
  {
    Serial.println("mod on");
    modifier = 1;
  }
  else
  {
    Serial.print("mod off");
    modifier = 0;
  }
  p->changed = false;
}

void update_element(ControlElement *p)
{
  if (p->changed)
  {
    if (p->is_button())
    {
      Serial.print("b");
    }
    if (p->is_encoder())
    {
      Serial.print("e");
    }
    if (p->is_pot())
    {
      Serial.print("p");
    }

    if (p->isModifier)
    {
      update_modifier(p);
    }
    else
    {

#if USE_MIDIUSB == 1
      Serial.print(" : ");
      int v = p->get_value();
      Serial.println(v);
      if (modifier == 1)
      {

        Serial.print(p->midi_address + 40);
        process_midi_out(p, p->midi_address + 40, v);
      }
      else
      {
        Serial.print(p->midi_address);
        process_midi_out(p, p->midi_address, v);
      }
#endif
    }
  }
}

//used for elements connected directly into the arduino
void update_single_element(ControlElement *p){
  p->read_value();
  update_element(p);
}
void update_multiplex(Multiplexer *mult)
{
  mult->update();
  for (int i = 0; i < 8; i++)
  {
    if (mult->pins[i] != NULL)
    {
      update_element(mult->pins[i]);
    }
  }
}

void setup()
{
  delay(3000);
  digitalWrite(mult1IO, HIGH);
  digitalWrite(mult2IO, HIGH);
  mult1.setup_pullup();
  // enc.scroll_multiplier = 9.0;
  // b7.led_pin = 0;
  // b2.led_pin = 1;
  // b5.led_pin = 2;
  // b6.led_pin = 3;
  benc_1.led_pin = 4;
  b3.set_is_modifier(true);

  // enc2.scroll_multiplier = 1.0;
  mult1.assign_pin(0, &b1);
  mult1.assign_pin(1, &b2);
  mult1.assign_pin(2, &b3);
  mult1.assign_pin(3, &b4);
  mult1.assign_pin(4, &b5);
  mult1.assign_pin(5, &b6);
  mult1.assign_pin(6, &b7);
  mult1.assign_pin(7, &b8);

  mult2.setup();

  mult2.assign_pin(5, &enc_1);
  mult2.assign_pin(7, &enc_2);
  mult2.assign_pin(6, &benc_1);

  mult2.assign_pin(0, &enc2_1);
  mult2.assign_pin(3, &enc2_2);
  mult2.assign_pin(1, &benc_2);

  p1.setup();
  p2.setup();
  p3.setup();


#if USE_MIDIUSB == 1
  set_midi_mult(&mult1);
  set_midi_mult(&mult2);
  set_midi(&p1);
  set_midi(&p2);
  set_midi(&p3);
#endif
#if USE_MIDIUSB == 1
  setup_midi();
#endif

  Serial.begin(9600);
}

void loop()
{
  update_multiplex(&mult1);
  update_multiplex(&mult2);
  update_single_element(&p1);
  update_single_element(&p2);
  update_single_element(&p3);
#if USE_MIDIUSB == 1
  loop_midi();
#endif
}