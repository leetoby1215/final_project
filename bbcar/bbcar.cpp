#include "bbcar.h"

BBCar::BBCar( PwmOut &pin_servo0, PwmOut &pin_servo1, Ticker &servo_ticker ):servo0(pin_servo0), servo1(pin_servo1){
    servo0.set_speed(0);
    servo1.set_speed(0);
    servo_ticker.attach(callback(this, &BBCar::controlWheel), 0.5);
}

void BBCar::controlWheel(){
    servo0.control();
    servo1.control();
}

void BBCar::stop(){
    servo0.set_speed(0);
    servo1.set_speed(0);
    servo0.set_factor(1);
    servo1.set_factor(1);
}

void BBCar::goStraight( double speed ){
    servo0.set_speed(speed);
    servo1.set_speed(-speed);
}

/*	speed : speed value of servo
    factor: control the speed value with 0~1
            control left/right turn with +/-
*/
void BBCar::turn( double speed, double factor ){
    servo0.set_speed(speed);
    servo1.set_speed(-speed);
    if(factor>0){
        servo0.set_factor(factor);
        servo1.set_factor(1);
    }
    else if(factor<0){
        servo0.set_factor(1);
        servo1.set_factor(-factor);
    }
}

float BBCar::clamp( float value, float max, float min ){
    if (value > max) return max;
    else if (value < min) return min;
    else return value;
}

int BBCar::turn2speed( float turn ){
    return 25+abs(25*turn);
}


