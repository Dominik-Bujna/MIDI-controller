#include <control_element.hpp>

class Pot : public ControlElement
{
public:
    Pot(int pin_n);
    ~Pot();
    virtual void read_value();
    virtual int get_value();
    virtual void setup();
    virtual bool is_pot();

private:
    int last_updated;
    int cooldown;
    int tolerance;
    int pin;
    int last_state;
};