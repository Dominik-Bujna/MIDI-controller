#include <MIDI_controls.hpp>

USBMIDI_CREATE_DEFAULT_INSTANCE();

void setup_midi()
{
   MIDI.begin(MIDI_CHANNEL_OMNI);
}
void loop_midi()
{
    // Read incoming messages
    MIDI.read();
}

void send_button_press(button_midi pressed, int velocity){
    int note = pressed.midi_note;
    MIDI.sendNoteOn(note, velocity, MY_MIDI_CH);
}
void send_button_toggle(){

}

void send_state_change(){

}
