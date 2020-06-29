
#include <USB-MIDI.h>
#include <midimap.hpp>

void setup_midi();
void loop_midi();

void send_button_press(button_midi pressed, int velocity);
void send_button_toggle();
void send_state_change();