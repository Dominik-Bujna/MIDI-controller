#include <button.hpp>

PushButton::PushButton(int pin_n)
{
    pin = pin_n;
    cooldown = 100;
    last_pressed = 0;
    last_state = 1;
    changed = 0;
}

PushButton::PushButton(int pin_n, int cooldown_ms)
{
    pin = pin_n;
    cooldown = cooldown_ms;
    last_pressed = 0;
    last_state = 1;
    changed = 0;
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
            if (time - last_pressed > cooldown)
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