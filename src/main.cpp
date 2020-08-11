
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



int mult1IO = 13;
int mult1A = 12;
int mult1B = 11;
int mult1C = 10;

int mult2IO = A0;
int mult2A = A3;
int mult2B = A2;
int mult2C = A1;

int mult3IO = 5;
int mult3A = 2;
int mult3B = 3;
int mult3C = 4;

int mult4IO = 9;
int mult4A = 6;
int mult4B = 7;
int mult4C = 8;

Multiplexer mult1 = Multiplexer(mult1A, mult1B, mult1C, mult1IO);
Multiplexer mult2 = Multiplexer(mult2A, mult2B, mult2C, mult2IO);
Multiplexer mult3 = Multiplexer(mult3A, mult3B, mult3C, mult3IO);
Multiplexer mult4 = Multiplexer(mult4A, mult4B, mult4C, mult4IO);

//mult1
PushButton bh = PushButton(mult1IO);
PushButton bl = PushButton(mult1IO);
RotaryEncoder enc = RotaryEncoder(mult1IO, mult1IO);
RotaryEncoderPinA enc_1 = RotaryEncoderPinA(&enc);
RotaryEncoderPinB enc_2 = RotaryEncoderPinB(&enc);
PushButton benc_1 = PushButton(mult1IO);
PushButton sw1 = PushButton(mult1IO);
PushButton sw2 = PushButton(mult1IO);
PushButton sw3 = PushButton(mult1IO);
//mult2
Pot p1 = Pot(mult2IO);
Pot p2 = Pot(mult2IO);
Pot p3 = Pot(mult2IO);
//mult3

PushButton ba = PushButton(mult3IO);
PushButton bb = PushButton(mult3IO);
PushButton bc = PushButton(mult3IO);
PushButton bd = PushButton(mult3IO);
RotaryEncoder enc2 = RotaryEncoder(mult3IO, mult3IO);
RotaryEncoderPinA enc2_1 = RotaryEncoderPinA(&enc2);
RotaryEncoderPinB enc2_2 = RotaryEncoderPinB(&enc2);
PushButton benc_2 = PushButton(mult3IO);

//mult4
PushButton b1 = PushButton(mult4IO);
PushButton b2 = PushButton(mult4IO);
PushButton b3 = PushButton(mult4IO);
PushButton b4 = PushButton(mult4IO);
PushButton b5 = PushButton(mult4IO);
PushButton b6 = PushButton(mult4IO);
PushButton b7 = PushButton(mult4IO);
PushButton b8 = PushButton(mult4IO);

void update_multiplex(Multiplexer *mult){
  mult->update();
  for(int i = 0; i < 8; i++){
    if(mult->pins[i] != NULL){
      if(mult->pins[i]->changed){
        int v = mult->pins[i]->get_value();
        Serial.print(mult->pin_IO);
        if(mult->pins[i]->is_button()){
          Serial.print("b");
        }
        if(mult->pins[i]->is_encoder()){
          Serial.print("e");
        }        
        if(mult->pins[i]->is_pot()){
          Serial.print("p");
        }

        Serial.print(i);
        Serial.print(" : ");
        Serial.println(v);
        #if USE_MIDIUSB == 1
        process_midi_out(mult->pins[i], 40 + i, v);
        #endif
      }
    }
  }
}


void setup()
{

  #if USE_MIDIUSB == 1
  setup_midi();
  #endif

  mult1.setup_pullup();

  mult1.assign_pin(0, &bh);
  mult1.assign_pin(1, &enc_1);
  mult1.assign_pin(2, &enc_2);
  mult1.assign_pin(3, &bl);
  mult1.assign_pin(4, &benc_1);
  mult1.assign_pin(5, &sw1);
  mult1.assign_pin(6, &sw2);
  mult1.assign_pin(7, &sw3);


  mult2.setup();

  mult2.assign_pin(0, &p1);
  mult2.assign_pin(1, &p2);
  mult2.assign_pin(2, &p3);


  mult3.setup_pullup();

  mult3.assign_pin(0, &ba);
  mult3.assign_pin(1, &bb);
  mult3.assign_pin(2, &bc);
  mult3.assign_pin(3, &bd);
  mult3.assign_pin(4, &benc_2);
  mult3.assign_pin(6, &enc2_1);
  mult3.assign_pin(7, &enc2_2);


  mult4.setup_pullup();

  mult4.assign_pin(0, &b1);
  mult4.assign_pin(1, &b2);
  mult4.assign_pin(2, &b3);
  mult4.assign_pin(3, &b4);
  mult4.assign_pin(4, &b5);
  mult4.assign_pin(5, &b6);
  mult4.assign_pin(6, &b7);
  mult4.assign_pin(7, &b8);

  Serial.begin(9600);
}

void loop()
{
  // update_multiplex(&mult1);
  update_multiplex(&mult2);
  update_multiplex(&mult3);
  update_multiplex(&mult4);
  #if USE_MIDIUSB == 1
  loop_midi();
  #endif
}