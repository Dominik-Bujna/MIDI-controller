#if USE_MIDIUSB == 1
#include <MIDI_controls.hpp>
#include <FastLED.h>

USBMIDI_CREATE_DEFAULT_INSTANCE();

#define LED_PIN     13

#define NUM_LEDS    5
#define BRIGHTNESS  20
#define LED_TYPE    WS2812
#define COLOR_ORDER GRB
CRGB leds[NUM_LEDS];

#define UPDATES_PER_SECOND 100


void handleNoteOn(byte channel, byte pitch, byte velocity)
{
    // Do whatever you want when a note is pressed.

    if(channel == 5 && pitch == 62){
        leds[4] = CRGB::Blue;
    }
    // if(channel == 5 && pitch == 63){
    if(channel == MY_MIDI_CH && pitch == 41){
        leds[3] = CRGB::BlueViolet;
    }
    // if(channel == 5 && pitch == 64){
    if(channel == 5 && pitch == 60){
        leds[2] = CRGB::Violet;
    }
    // if(channel == 5 && pitch == 66){    
    if(channel == 5 && pitch == 61){
        leds[1] = CRGB::MediumVioletRed;
    }
    // if(channel == 5 && pitch == 67){
    if(channel == 5 && pitch == 65){
        leds[0] = CRGB::Red;
    }
    // Try to keep your callbacks short (no delays ect)
    // otherwise it would slow down the loop() and have a bad impact
    // on real-time performance.
}

void handleNoteOff(byte channel, byte pitch, byte velocity)
{
    // Do something when the note is released.
    // Note that NoteOn messages with 0 velocity are interpreted as NoteOffs.
    if(channel == MY_MIDI_CH && pitch == 62){
        leds[4] = CRGB::Black;
    }
    // if(channel == MY_MIDI_CH && pitch == 63){
    if(channel == MY_MIDI_CH && pitch == 41){
        leds[3] = CRGB::Black;
    }
    // if(channel == MY_MIDI_CH && pitch == 64){
    if(channel == MY_MIDI_CH && pitch == 60){
        leds[2] = CRGB::Black;
    }
    // if(channel == MY_MIDI_CH && pitch == 66){  
    if(channel == MY_MIDI_CH && pitch == 61){
        leds[1] = CRGB::Black;
    }
    // if(channel == MY_MIDI_CH && pitch == 67){
    if(channel == MY_MIDI_CH && pitch == 65){
        leds[0] = CRGB::Black;
    }
}




void setup_midi()
{
   MIDI.begin(MIDI_CHANNEL_OMNI);
  MIDI.setHandleNoteOn(handleNoteOn);
  MIDI.setHandleNoteOff(handleNoteOff);
    
  FastLED.addLeds<LED_TYPE, LED_PIN, COLOR_ORDER>(leds, NUM_LEDS).setCorrection( TypicalLEDStrip );
  FastLED.setBrightness(  BRIGHTNESS );
  leds[0] = CRGB::Green;
  leds[1] = CRGB::Yellow;
  leds[2] = CRGB::Red;
  leds[3] = CRGB::Yellow;
  leds[4] = CRGB::Green;
}
void loop_midi()
{
    // Read incoming messages
    MIDI.read();
    FastLED.show();
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