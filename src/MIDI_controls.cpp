#if USE_MIDIUSB == 1
#include <MIDI_controls.hpp>

USBMIDI_CREATE_DEFAULT_INSTANCE();
#define LED_PIN 13

#define NUM_LEDS 5
#define BRIGHTNESS 20
#define LED_TYPE WS2812
#define COLOR_ORDER GRB
CRGB leds[NUM_LEDS];

#define UPDATES_PER_SECOND 30

int n_midi = 0;
int leds_midi[NUM_LEDS];
CRGB led_colors[NUM_LEDS];

void set_default_colors()
{
    for (int i = 0; i < NUM_LEDS; i++)
    {
        led_colors[i] = CRGB::DeepPink;
    }
}
void set_midi(ControlElement *c)
{
    if (!c->isModifier)
    {
        c->midi_address = n_midi++;
        if (c->led_pin != -1)
        {
            leds_midi[c->led_pin] = c->midi_address;
            Serial.print("MIDI ADDRESS SET: ");
            Serial.print(c->midi_address);
            Serial.print("To led_pin");
            Serial.print(c->led_pin);
            Serial.print("\t");
            Serial.println(leds_midi[c->led_pin]);
            // NoteToLed[multi->pins[i]->midi_address] = multi->pins[i]->led_pin;
        }
    }
}

void set_midi_mult(Multiplexer *multi)
{
    for (int i = 0; i < 8; i++)
    {
        if (multi->pins[i] != NULL)
        {
            ControlElement *c = multi->pins[i];
            set_midi(c);
        }
    }
}

void handleNoteOn(byte channel, byte pitch, byte velocity)
{
    for(int i = 0; i < NUM_LEDS; i++){
    Serial.print(leds_midi[i]);
    Serial.print('\t');
    }
    Serial.println();
    // delay(500);
    // Do whatever you want when a note is pressed.
    Serial.print("MIDI IN ON ");
    Serial.print(pitch);
    Serial.print(" : ");
    Serial.println(velocity);

    for (int i = 0; i < NUM_LEDS; i++)
    {
        if (leds_midi[i] == pitch)
        {
            leds[i] = led_colors[i];
        }
    }
}

void handleNoteOff(byte channel, byte pitch, byte velocity)
{
    Serial.print("MIDI IN OFF ");
    Serial.print(pitch);
    Serial.print(" : ");
    Serial.println(velocity);
    // Do something when the note is released.
    // Note that NoteOn messages with 0 velocity are interpreted as NoteOffs.
    for (int i = 0; i < NUM_LEDS; i++)
    {
        if (leds_midi[i] == pitch)
        {
            leds[i] = CRGB::Black;
        }
    }
}

void setup_midi()
{
    MIDI.begin(MIDI_CHANNEL_OMNI);
    MIDI.setHandleNoteOn(handleNoteOn);
    MIDI.setHandleNoteOff(handleNoteOff);
    set_default_colors();
    FastLED.addLeds<LED_TYPE, LED_PIN, COLOR_ORDER>(leds, NUM_LEDS).setCorrection(TypicalLEDStrip);
    FastLED.setBrightness(BRIGHTNESS);
      leds[0] = CRGB::Green;
      leds[1] = CRGB::Yellow;
      leds[2] = CRGB::Red;
      leds[3] = CRGB::Yellow;
      leds[4] = CRGB::Green;
}
void loop_midi()
{
    // Read incoming messages

    // leds_midi[0]=6;
    MIDI.read();
    FastLED.show();
}

void send_button_press(int note, int velocity)
{
    MIDI.sendNoteOn(note, velocity, MY_MIDI_CH);
}
void send_button_toggle()
{
}

void send_state_change()
{
}
void process_midi_out(ControlElement *e, int note, int value)
{
    if (e->is_button())
    {
        MIDI.sendNoteOn(note, e->get_value(), MY_MIDI_CH);
        e->changed = false;
    }
    if (e->is_encoder() || e->is_pot())
    {
        MIDI.sendControlChange(note, e->get_value(), MY_MIDI_CH);
        e->changed = false;
    }
}
#endif