#include <button.hpp>

PushButton::PushButton(int pin_n)
{
    pin = pin_n;
    cooldown = 100;
    last_pressed = 0;
    last_state = 1;
    changed = 0;
    led_pin = -1;
    midi_address = -1;
}

PushButton::PushButton(int pin_n,  int led)
{
    pin = pin_n;
    last_pressed = 0;
    last_state = 1;
    changed = 0;
    midi_address = -1;
    led_pin = led;
}
PushButton::~PushButton(){};
int PushButton::get_value()
{
    if(last_state == LOW){
        return 127;
    }else{
        return 0;
    }
}

void PushButton::read_value()
{
    int state = digitalRead(pin);
    if (state != last_state)
    {
        if (!changed)
        {
            int time = millis();
            {
                last_state = state;
                //this flag is set back after the change of the button has been sent
                changed = true;
                last_pressed = time;
            }
        }
    }
}

void PushButton::setup()
{
    pinMode(pin, INPUT_PULLUP);
    digitalWrite(pin, HIGH);
}

bool PushButton::is_button(){
    return true;
}