#ifndef Micro_Bot_SPWM_H
#define Micro_Bot_SPWM_H
#include "Arduino.h"
class MICRO_BOT_SPWM
{
public:
	MICRO_BOT_SPWM(int left_servo, int right_servo);
	~MICRO_BOT_SPWM();
	int servos(int direction);
private:
	int _LEFT_SERVO;
	int _RIGHT_SERVO;
	int _DIRECTION;
};
#endif