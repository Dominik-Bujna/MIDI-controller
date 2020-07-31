#if USE_MIDIUSB == 1
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

void send_button_press(int note, int velocity){
    MIDI.sendNoteOn(note, velocity, MY_MIDI_CH);
}
void send_button_toggle(){

}

void send_state_change(){

}
void process_midi_out(ControlElement * e, int note, int value){
    if(e->is_button()){
        MIDI.sendNoteOn(note, e->get_value(), MY_MIDI_CH);
        e->changed = false;
    }
    if(e->is_encoder() || e->is_pot()){
        MIDI.sendControlChange(note, e->get_value(), MY_MIDI_CH);
        e->changed = false;
    }
}
#endif