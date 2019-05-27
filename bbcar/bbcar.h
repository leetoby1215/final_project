#ifndef BBCAR_H
#define BBCAR_H
#include "parallax_servo.h"
#include "parallax_encoder.h"
#include "parallax_ping.h"

class BBCar{
	public:
		BBCar( PwmOut &pin_servo0, PwmOut &pin_servo1, Ticker &servo_ticker );

		parallax_servo servo0;
		parallax_servo servo1;

		void controlWheel();
		void stop();
		void goStraight( int speed );

		// turn left/right with a factor of speed
		void turn( int speed, double factor );

		// limit the value by max and min
		float clamp( float value, float max, float min );
		int turn2speed( float turn );
};

#endif
