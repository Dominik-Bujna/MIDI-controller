#include <MIDI_controls.hpp>
#include <button.hpp>
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
  // Serial.begin(9600);
  setup_midi();
  setup_buttons();
}
void loop(){
  loop_buttons();
  for(int i = 0; i < MAX_PUSH_BUTTONS; i++){
    if(push_buttons[i].changed){
      push_buttons[i].changed = false;
      int velocity = (push_buttons[i].last_state == LOW)?127:0;
      send_button_press(midi_buttons[push_buttons[i].midi_index], velocity);
    }
  }
  loop_midi();
}