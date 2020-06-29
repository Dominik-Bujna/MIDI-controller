#include <button.hpp>

push_button push_buttons[MAX_PUSH_BUTTONS] = {
    {0, 100, PLAY, 1, false, 0},
    {0, 100, CUE, 1, false, 1},
};


void setup_buttons(){
    for(int i = 0; i < MAX_PUSH_BUTTONS; i++){
        pinMode(push_buttons[i].pin, INPUT_PULLUP);
    }
}
void loop_buttons(){
    for(int i=0; i < MAX_PUSH_BUTTONS; i++){
        int state = digitalRead(push_buttons[i].pin);
        if(state != push_buttons[i].last_state){
            if(!push_buttons[i].changed){
                int time = millis();
                if(time - push_buttons[i].last_pressed > push_buttons[i].cooldown){
                    push_buttons[i].last_state = state;
                    //this flag is set back after the change of the button has been sent
                    push_buttons[i].changed = true;
                    push_buttons[i].last_pressed = time;
                }
            }   
        }
    }
}