#include <pinmap.hpp>
#include <control_element.hpp>

class PushButton : public ControlElement
{

public:
    PushButton(int pin_n);
    PushButton(int pin_n, int cooldown_ms);
    ~PushButton();
    virtual void read_value();
    virtual int get_value();
    virtual void setup();
    virtual bool is_button();

private:
    int last_pressed;
    int cooldown;
    int last_state;
    int pin;
};