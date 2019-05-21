#ifndef PARALLAX_SERVO_H
#define PARALLAX_SERVO_H
#include "mbed.h"
#include <vector>

#define CENTER_BASE 1500

class parallax_servo {
    public:
        static std::vector<parallax_servo*> servo_list;

        parallax_servo(PwmOut& pin);

        void control();
        void set_speed( int value ){ goal = value; }
        void set_ramp( int value ){ ramp = value; }
        void set_factor( double value ){ factor = value; }

        void servo_control();

        //Do ramping
        int truncate( int last, int goal, int ramp );
        int operator=( int value ){ set_speed(value); return 1; }

    private:
        PwmOut *pwm;
        double factor;
        int last;
        int goal;
        int ramp;
};

#endif
