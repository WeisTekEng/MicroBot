#ifndef Micro_Bot_Software_Pwm_H
#define Micro_Bot_Software_Pwm_H
#include "Arduino.h"
class MICRO_BOT_SPWM
{
public:
	MICRO_BOT_SPWM(int left_servo, int right_servo);
	~MICRO_BOT_SPWM();
	void Servos(int _DIRECTION)
private:
	//Variables and private functions.
	int _LEFT_SERVO;
	int _RIGHT_SERVO;
	int _DIRECTION;
};
#endif