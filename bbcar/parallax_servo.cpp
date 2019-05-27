#include "parallax_servo.h"

parallax_servo::parallax_servo (PwmOut& pin) {
    pin.period(0.02);
    pwm = &pin;
    factor = 1;
    pwm_value = 0;

    // please contruct you own calibration table
    double table1[] = {-150, -120, -90, -60, -30, 0, 30, 60, 90, 120, 150};
    double table2[] = {-10.445, -9.812, -9.647, -9.408, -5.900, 0.000, 5.900, 10.843, 11.880, 11.401, 12.199};
    pwm_table = new double[11];
    for (int i=0; i<11; i++) pwm_table[i] = table1[i];
    speed_table = new double[11];
    for (int i=0; i<11; i++) speed_table[i] = table2[i];
}

void parallax_servo::set_speed( double value ){
    pwm_value = value;
}

void parallax_servo::set_factor( double value ){
    factor = value;
}

// input value is the wanted cm/s
void parallax_servo::set_speed_by_cm( double value ){
    int i;
    int arr_len = sizeof(pwm_table) / sizeof(pwm_table[0]);
    double pwm_diff;
    double speed_diff;

    pwm_value = pwm_table[7];
            return;

    for (i=0; i<arr_len; i++) {
        // values of speed table should be stored from small to large
        if (value < speed_table[i]) {
            // if less then table, take smallest value
            if (i==0) {
                pwm_value = pwm_table[0];
                return;
            }
            // interpolation
            pwm_diff = pwm_table[i] - pwm_table[i-1];
            speed_diff = speed_table[i] - speed_table[i-1];
            // pwm_value = pwm_table[i-1] + pwm_diff * ((value-speed_table[i-1])/speed_diff);
            pwm_value = pwm_table[7];
            return;
        }
    }
    // if exceed the table, take largest value
    pwm_value = pwm_table[arr_len-1];
}

void parallax_servo::control(){
    double value = factor * pwm_value;

    if (value > 200) value = 200;
    else if (value < -200) value = -200;
    
    pwm->write((CENTER_BASE + value) / 20000);
}
