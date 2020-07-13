// #include <MIDI_controls.hpp>
#include <button.hpp>
#include <rotary_encoder.hpp>
#include <pot.hpp>

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
// ControlElement *c [6] = {new PushButton(7), new PushButton(6), new Pot(A0), new Pot(A1), new PushButton(5), new RotaryEncoder(3, 4)};
// PushButton a = PushButton(7);
int valA = 0;
int valB = 0;
int valC = 0;
PushButton button = PushButton(5);
RotaryEncoder enc = RotaryEncoder(5, 5);
void setup()
{
  pinMode(2, OUTPUT);
  pinMode(3, OUTPUT);
  pinMode(4, OUTPUT);
  // pinMode(A0, INPUT_PULLUP);
  pinMode(5, INPUT);

  Serial.begin(9600);
  // setup_midi();
  // Serial.begin(9600);
  // a.setup();
  // for(int i = 0; i < 6; i++){
  //   c[i]->setup();
  // }
}

void loop()
{
  digitalWrite(2, LOW);
  digitalWrite(3, LOW);
  digitalWrite(4, LOW);

  // valA = analogRead(A0);
  enc.read_1();
  valA = digitalRead(5);

  digitalWrite(2, LOW);
  digitalWrite(3, LOW);
  digitalWrite(4, HIGH);

  // valB = analogRead(A0);
  button.read_value();
  valB = digitalRead(5);

  digitalWrite(2, LOW);
  digitalWrite(3, HIGH);
  digitalWrite(4, LOW);

  // valC = analogRead(A0);
  enc.read_2();
  valC = digitalRead(5);

  valC = digitalRead(5);
  if(button.changed){

    Serial.println(button.get_value());
    button.changed = false;
    // delay(100);
  }
  if(enc.changed){

    Serial.println(enc.get_value());
    enc.changed = false;
  }
  // Serial.println(valA);
  // Serial.println(valB);
  // Serial.println(valC);
  // Serial.println();
  // Serial.println();

  // delay(100);

  // for(int i = 0; i < 6; i++){
  //   c[i]->read_value();
  //   if(c[i]->changed){
  //     int v = c[i]->get_value();
  //     Serial.print(i);
  //     Serial.print(" : ");
  //     Serial.println(v);
  //     c[i]->changed = false;
  //     send_button_press(60+i, v);
  //   }
  // }
  // loop_midi();
}