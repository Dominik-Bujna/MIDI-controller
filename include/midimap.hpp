#include <pinmap.hpp>

#define MY_MIDI_CH 1
const int MAX_MIDI_BUTTONS = 2;

struct button_midi{
    int pin;
    int midi_note;
};

constexpr static button_midi midi_buttons[MAX_MIDI_BUTTONS] = {
    {PLAY, 42},
    {CUE, 41}
};