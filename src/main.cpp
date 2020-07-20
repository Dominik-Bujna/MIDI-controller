
#if USE_MIDIUSB == 1
#include <MIDI_controls.hpp>
#endif


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
ControlElement *c [6] = {new PushButton(7), new PushButton(6), new Pot(A0), new Pot(A1), new PushButton(5), new RotaryEncoder(3, 4)};
PushButton a = PushButton(7);
void setup()
{

  #if USE_MIDIUSB == 1
  setup_midi();
  #endif

  Serial.begin(9600);
  a.setup();
  for(int i = 0; i < 6; i++){
    c[i]->setup();
  }
}

void loop()
{
  for(int i = 0; i < 6; i++){
    c[i]->read_value();
    if(c[i]->changed){
      int v = c[i]->get_value();
      Serial.print(i);
      Serial.print(" : ");
      Serial.println(v);
      c[i]->changed = false;
      #if USE_MIDIUSB == 1
      send_button_press(60+i, v);
      #endif
    }
  }

  #if USE_MIDIUSB == 1
  loop_midi();
  #endif
}