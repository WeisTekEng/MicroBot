////////////////////////////////////////////////////////////////////////
//PROJECT:    Attiny84 ?C ?Bot Firmware library
//AUTHOR:     Jeremy Goss
//DATE:       4/26/2014
//SUMMERY:    Uses a custom 328 MicroC as a main board for a small
//            2 servo 1 caster robot with 3 bumper sensors. Simple
//            collision detection on front and rear of bot, reverse
//            and turn logic. as well as a board routine.
//			  (Summery needs to be updated for new board)
//
//PLANNED:	  Bluetooth control and debugging serial
//
//INCLUDED:   ChangeLog.h, MICRO_BOT_Library.cpp, MICRO_BOT_library.h
//
//UPDATED:    04/26/14
////////////////////////////////////////////////////////////////////////
//ASCII Schematic updated 04/23/14 (Needs updated to 328 schematic)
////////////////////////////////////////////////////////////////////////
#include "MicroBot328SPWM.h"

//int _DIRECTION;
int lenMicroSecondsOfPeriod = 25 * 1000; // 25 milliseconds (ms)
int lenMicroSecondsOfPulse = 1 * 1000; // 1 ms is 0 degrees
int Forward = 0.7 * 1000; //0.5ms is 0 degrees in HS-422 servo
int Reverse = 3.7 * 1000;
int increment = 0.01 * 1000;
int current = 3.7 * 1000;
////////////////////////////////////////////////////////////////////////
//Main object
////////////////////////////////////////////////////////////////////////
MICRO_BOT_SPWM:MICRO_BOT_SPWM(int left_servo, int right_servo)
{
	//Variable assignments here.
	_LEFT_SERVO = left_servo;
	_RIGHT_SERVO = right_servo;
	pinMode(_LEFT_SERVO, OUTPUT);
	pinMode(_RIGHT_SERVO, OUTPUT);
}

////////////////////////////////////////////////////////////////////////
//Main object destructor
////////////////////////////////////////////////////////////////////////
MICRO_BOT_SPWM::~MICRO_BOT_SPWM()
{
}

void MICRO_BOT_SPWM::Servos(int _DIRECTION)
{
    //Moving forward
	if(_DIRECTION == 0){
         // Servos work by sending a 25 ms pulse.  
         // 0.7 ms at the start of the pulse will turn the servo to the 0 degree position
         // 2.2 ms at the start of the pulse will turn the servo to the 90 degree position 
         // 3.7 ms at the start of the pulse will turn the servo to the 180 degree position 
         // Turn voltage high to start the period and pulse
         digitalWrite(_LEFT_SERVO, HIGH);
         // Delay for the length of the pulse
         delayMicroseconds(Forward);
         // Turn the voltage low for the remainder of the pulse
         digitalWrite(_LEFT_SERVO, LOW);
		 //Simulating multitasking both servos;
		 digitalWrite(_RIGHT_SERVO, HIGH);
		 delayMicroseconds(Reverse);
		 digitalWrite(_RIGHT_SERVO, LOW);
         // Delay this loop for the remainder of the period so we don't
         // send the next signal too soon or too late
         delayMicroseconds(lenMicroSecondsOfPeriod - current); 
         //current+=increment;
    }
	//Moving in reverse
	else if(_DIRECTION == 1)
	{
		 digitalWrite(_LEFT_SERVO, HIGH);
         // Delay for the length of the pulse
         delayMicroseconds(Reverse);
         // Turn the voltage low for the remainder of the pulse
         digitalWrite(_LEFT_SERVO, LOW);
		 //Simulating multitasking both servos;
		 digitalWrite(_RIGHT_SERVO, HIGH);
		 delayMicroseconds(Forward);
		 digitalWrite(_RIGHT_SERVO, LOW);
         // Delay this loop for the remainder of the period so we don't
         // send the next signal too soon or too late
         delayMicroseconds(lenMicroSecondsOfPeriod - current);
	}
	//Turn right
	else if(_DIRECTION == 2)
	{
		 digitalWrite(_LEFT_SERVO, HIGH);
         // Delay for the length of the pulse
         delayMicroseconds(Forward);
         // Turn the voltage low for the remainder of the pulse
         digitalWrite(_LEFT_SERVO, LOW);
		 //Simulating multitasking both servos;
		 digitalWrite(_RIGHT_SERVO, HIGH);
		 delayMicroseconds(Forward);
		 digitalWrite(_RIGHT_SERVO, LOW);
         // Delay this loop for the remainder of the period so we don't
         // send the next signal too soon or too late
         delayMicroseconds(lenMicroSecondsOfPeriod - current);
	}
	//Turn left
	else if(_DIRECTION == 3)
	{
		 digitalWrite(_LEFT_SERVO, HIGH);
         // Delay for the length of the pulse
         delayMicroseconds(Reverse);
         // Turn the voltage low for the remainder of the pulse
         digitalWrite(_LEFT_SERVO, LOW);
		 //Simulating multitasking both servos;
		 digitalWrite(_RIGHT_SERVO, HIGH);
		 delayMicroseconds(Reverse);
		 digitalWrite(_RIGHT_SERVO, LOW);
		 // Delay this loop for the remainder of the period so we don't
         // send the next signal too soon or too late
         delayMicroseconds(lenMicroSecondsOfPeriod - current);
	}
	//Full stop
	else if(_DIRECTION == 4)
	{
		 digitalWrite(_LEFT_SERVO, LOW);
		 digitalWrite(_RIGHT_SERVO, LOW);
	}
}