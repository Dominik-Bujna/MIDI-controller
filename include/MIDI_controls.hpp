#if USE_MIDIUSB == 1

#include <USB-MIDI.h>
#include <midimap.hpp>
#include <control_element.hpp>

void setup_midi();
void loop_midi();

void send_button_press(int note, int velocity);
void process_midi_out(ControlElement * e, int note, int value);
void send_button_toggle();
void send_state_change();

#endif