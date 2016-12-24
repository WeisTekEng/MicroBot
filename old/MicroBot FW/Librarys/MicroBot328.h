#ifndef Micro_Bot_H
#define Micro_Bot_H
#include "Arduino.h"
class MICRO_BOT
{
public:
	MICRO_BOT(int delay, int left_servo, int right_servo,
			 int count, int sw_one, int full_stop, int trigger_pin, int echo_pin);
	~MICRO_BOT();
	
	bool init_start();
	void board();
	void run();
	bool stuck();
	void ping();
	

private:
	void Servos(int _DIRECTION);
	void bt_cont();
	void forward();
	void backup();
	void turn_l();
	void turn_r();
	void stop();
	void collision_detection();
	//int _MIN;
	//int _MAX;
	int _LEFT_SERVO;
	int _RIGHT_SERVO;
	int _DELAY;
	int _COUNT;
	int _SW_ONE;
	int _FULL_STOP;
	int _LEFT_FRONT_BUMPER;
	int _RIGHT_FRONT_BUMPER;
	int _TRIGGER_PIN;
	int _ECHO_PIN;
	bool _STUCK;
	bool _BT_CONT;
	char _REC_CHAR;
	int _DIRECTION;
};
#endif
