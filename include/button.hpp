#include <pinmap.hpp>

const int MAX_PUSH_BUTTONS = 2;
struct push_button{
    int last_pressed;
    int cooldown;
    int pin;
    int last_state;
    //set true by loop that reads the inputs, reset to false by loop that processes the input
    bool changed;
    int midi_index;
};

extern push_button push_buttons[MAX_PUSH_BUTTONS];

void setup_buttons();
void loop_buttons();