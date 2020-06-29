#include <pinmap.hpp>
#include <MIDI_controls.hpp>
/*
TO DO:
HW:
- reading from multiplexed inputs
- buttons with debouncing
- rotary encoder
  -adjustable scroll speed, reading as a function with return value
- potentiometer with debouncing/not jumping around
- possible LED output for each control
- 4x7 segment display driver

SW:
- SENDING MIDI MESSAGES
  - functions for different types of input (press/toggle/update)
- keeping state of loop size and jump size (displayed on display)
  - sending particular MIDI messages
*/

void setup(){
  setup_midi();
}
void loop(){
  loop_midi();
}