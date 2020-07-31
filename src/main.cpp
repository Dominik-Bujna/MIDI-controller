
#if USE_MIDIUSB == 1
#include <MIDI_controls.hpp>
#endif


#include <button.hpp>
#include <rotary_encoder.hpp>
#include <rotary_encoder_pin.hpp>
#include <pot.hpp>
#include <multiplexer.hpp>

/*
/dev/cu.usbmodemMIDI1
TO DO:
HW:
- reading from multiplexed inputs
* buttons with debouncing
* rotary encoder
  * adjustable scroll speed, reading as a function with return value
* potentiometer with debouncing/not jumping around
- possible LED output for each control
- 4x7 segment display driver

SW:
- SENDING MIDI MESSAGES
  - functions for different types of input (press/toggle/update)
- keeping state of loop size and jump size (displayed on display)
  - sending particular MIDI messages
*/
int mult1IO = 9;
int mult1A = 8;
int mult1B = 7;
int mult1C = 6;

int mult2IO = A5;
int mult2A = 3;
int mult2B = 4;
int mult2C = 5;

PushButton button = PushButton(mult1IO);
RotaryEncoder enc = RotaryEncoder(mult1IO, mult1IO);
RotaryEncoderPinA enc_1 = RotaryEncoderPinA(&enc);
RotaryEncoderPinB enc_2 = RotaryEncoderPinB(&enc);
PushButton b1 = PushButton(mult1IO);
PushButton b2 = PushButton(mult1IO);
PushButton b3 = PushButton(mult1IO);
PushButton b4 = PushButton(mult1IO);
PushButton b5 = PushButton(mult1IO);

Pot p1 = Pot(mult2IO);
Pot p2 = Pot(mult2IO);
Pot p3 = Pot(mult2IO);
Pot p4 = Pot(mult2IO);

Multiplexer mult1 = Multiplexer(mult1A, mult1B, mult1C, mult1IO);
Multiplexer mult2 = Multiplexer(mult2A, mult2B, mult2C, mult2IO);

void setup()
{

  #if USE_MIDIUSB == 1
  setup_midi();
  #endif

  mult1.setup();
  mult1.assign_pin(1, &enc_1);
  mult1.assign_pin(0, &button);
  mult1.assign_pin(3, &enc_2);

  mult1.assign_pin(2, &b1);
  mult1.assign_pin(4, &b2);
  mult1.assign_pin(6, &b3);
  mult1.assign_pin(7, &b4);
  mult1.assign_pin(5, &b5);

  mult2.setup();

  mult2.assign_pin(0, &p1);
  mult2.assign_pin(1, &p2);
  mult2.assign_pin(2, &p3);
  mult2.assign_pin(3, &p4);

  Serial.begin(9600);
}

void loop()
{
  mult1.update();
  // delay(100);
  for(int i = 0; i < 8; i++){
    if(mult1.pins[i] != NULL){
      if(mult1.pins[i]->changed){
        int v = mult1.pins[i]->get_value();
        Serial.println(v);
        #if USE_MIDIUSB == 1
        process_midi_out(mult1.pins[i], 60 + i, v);
        #endif
      }
    }
  }
  mult2.update();
  for(int i = 0; i < 8; i++){
    if(mult2.pins[i] != NULL){
      if(mult2.pins[i]->changed){
        int v = mult2.pins[i]->get_value();
        Serial.println(v);
        #if USE_MIDIUSB == 1
        process_midi_out(mult2.pins[i], 70 + i, v);
        #endif
      }
    }
  }

  #if USE_MIDIUSB == 1
  loop_midi();
  #endif
}