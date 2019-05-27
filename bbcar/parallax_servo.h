#ifndef PARALLAX_SERVO_H
#define PARALLAX_SERVO_H
#include "mbed.h"

#define CENTER_BASE 1500

class parallax_servo {
    public:
        parallax_servo(PwmOut& pin);

        void set_speed( double value );
        void set_factor( double value );
        void set_speed_by_cm( double value );
        void control();

    private:

        PwmOut *pwm;
        double factor;
        double pwm_value;

        // the calibration table
        double *pwm_table;
        double *speed_table;
};

#endif
