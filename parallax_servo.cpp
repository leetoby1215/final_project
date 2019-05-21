#include "parallax_servo.h"

std::vector<parallax_servo*> parallax_servo::servo_list;

parallax_servo::parallax_servo (PwmOut& pin) {
    pin.period(.02);
    pwm = &pin;
    factor = 1;
    last = 0;
    ramp = 1500;
    goal = 1500;
    servo_list.push_back(this);
}

void parallax_servo::control(){
    int speed = truncate(last,goal,ramp);
    if (factor*speed > 200) speed = 200;
    else if (factor*speed < -200) speed = -200;
    else speed = factor*speed;
    pwm->write((CENTER_BASE + speed) / 20000.0f);
    last = speed;
}

void parallax_servo::servo_control(){
    for( int i=0; i<servo_list.size(); i++ ){
        (servo_list[i])->control();
    }
}

int parallax_servo::truncate( int last, int goal, int ramp ) {
    if (abs(last - goal) < ramp) return goal;
    else return (last > goal) ? (last - ramp) : (last + ramp);
}
