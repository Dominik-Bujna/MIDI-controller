// #include <MIDI_controls.hpp>
#include <button.hpp>
#include <rotary_encoder.hpp>
#include <rotary_encoder_pin.hpp>
#include <pot.hpp>
#include <multiplexer.hpp>
#include <leds.hpp>


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
// ControlElement *c [6] = {new PushButton(7), new PushButton(6), new Pot(A0), new Pot(A1), new PushButton(5), new RotaryEncoder(3, 4)};
// PushButton a = PushButton(7);
int valA = 0;
int valB = 0;
int valC = 0;
PushButton button = PushButton(5);
RotaryEncoder enc = RotaryEncoder(5, 5);
RotaryEncoderPinA enc_1 = RotaryEncoderPinA(&enc);
RotaryEncoderPinB enc_2 = RotaryEncoderPinB(&enc);
Multiplexer mult = Multiplexer(2, 3, 4, 5);
void setup()
{
  mult.setup();
  Serial.begin(9600);

  mult.assign_pin(0, &enc_1);
  mult.assign_pin(1, &button);
  mult.assign_pin(2, &enc_2);
  led_setup();
}

void loop()
{
  mult.update();
  led_loop();
  // delay(100);
  if(button.changed){
    int v = button.get_value();
    Serial.println(v);
    button.changed = false;
  }
  if(enc.changed){
    int v = enc.get_value();
    Serial.println(v);
    enc.changed = false;
  }

}