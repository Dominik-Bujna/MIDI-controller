#include <pot.hpp>

Pot::Pot(int pin_n)
{
    pin = pin_n;
    last_state = 0;
    changed = false;
    tolerance = 4;
    cooldown = 10;
}

Pot::~Pot()
{
}

void Pot::read_value()
{
    int state = analogRead(pin);
    if (state != last_state)
    {
        if (!changed)
        {
            int time = millis();
            if (time - last_updated > cooldown)
            {
                if (abs(last_state - state) > tolerance)
                {
                    last_state = state;
                    Serial.print("pin: ");
                    Serial.print(pin);
                    Serial.print(" value: ");
                    Serial.println(last_state);
                    // delay(500);
                    //this flag is set back after the change of has been sent
                    changed = true;
                    last_updated = time;
                }
            }
        }
    }
}
int Pot::get_value()
{
    return map(last_state, 0, 1023, 0, 127);
}
void Pot::setup()
{
    pinMode(pin, INPUT);
    // analogWrite(pin, 0);
}