
#include <USB-MIDI.h>

#define MY_MIDI_CH 1

void setup_midi();
void loop_midi();

void send_button_press();
void send_button_toggle();
void send_state_change();