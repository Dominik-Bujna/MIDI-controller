#if USE_MIDIUSB == 1
#include <USB-MIDI.h>
#include <FastLED.h>

#include <midimap.hpp>
#include <control_element.hpp>
#include <multiplexer.hpp>



void setup_midi();
void loop_midi();

void set_default_colors();
void set_midi(ControlElement *c);
void set_midi_mult(Multiplexer *multi);

void handleNoteOn(byte channel, byte pitch, byte velocity);
void handleNoteOff(byte channel, byte pitch, byte velocity);

void send_button_press(int note, int velocity);
void process_midi_out(ControlElement * e, int note, int value);
void send_button_toggle();
void send_state_change();

#endif