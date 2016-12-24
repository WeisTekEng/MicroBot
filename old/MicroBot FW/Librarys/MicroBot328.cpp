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
#include "MicroBot328.h"

int _MIN_DISTANCE = 20;
//int _DISTANCE = 0;		//cannot start out less than _MIN_DISTANCE or the robot will never move.
int _DURATION = 0;
char _REC_CHAR;
bool _BT_CONT = false;
int _DIRECTION;

int lenMicroSecondsOfPeriod = 25 * 1000; // 25 milliseconds (ms)
int lenMicroSecondsOfPulse = 1 * 1000; // 1 ms is 0 degrees
int Forward = 0.7 * 1000; //0.5ms is 0 degrees in HS-422 servo
int Reverse = 3.7 * 1000;
int increment = 0.01 * 1000;
int current = 3.7 * 1000;

////////////////////////////////////////////////////////////////////////
//Main object
////////////////////////////////////////////////////////////////////////
MICRO_BOT::MICRO_BOT(int delay, int left_servo, int right_servo,
				   int count, int sw_one, int full_stop, int trigger_pin, int echo_pin)
{
	_STUCK = false;
	_LEFT_SERVO = left_servo;
	_RIGHT_SERVO = right_servo;
	_DELAY = delay;
	_COUNT = count;
	_SW_ONE = sw_one;
	_FULL_STOP = full_stop;
	_TRIGGER_PIN = trigger_pin;
	_ECHO_PIN = echo_pin;
	pinMode(_RIGHT_SERVO, OUTPUT);
	pinMode(_LEFT_SERVO, OUTPUT);
	pinMode(_TRIGGER_PIN, OUTPUT);
	pinMode(_ECHO_PIN, INPUT);
	pinMode(_SW_ONE, INPUT);
	Serial.begin(9600);
}

////////////////////////////////////////////////////////////////////////
//Main object destructor
////////////////////////////////////////////////////////////////////////
MICRO_BOT::~MICRO_BOT()
{
}

////////////////////////////////////////////////////////////////////////
//Check to see if the start trigger has been pressed three times to 
//start robot, or a BT start command has been sent.
////////////////////////////////////////////////////////////////////////
bool MICRO_BOT::init_start()
{
	//Serial.begin(9600);
	if(_COUNT == 3)
	{
		return true;
	}
	else if(digitalRead(_SW_ONE) == LOW)
	{
		_COUNT += 1;
		delay(_DELAY);
		return false;
	}
	else
	{
			//Checking bluetooth serial for input
			//Check if we want BT control
		if(Serial.available())
		{
			_REC_CHAR = Serial.read();
			Serial.print("Awaiting commands");
			if(_REC_CHAR == '1')
			{
				_BT_CONT = true;
				return true;
			}
		}
		else
		{
			return false;
		}
	}
}

////////////////////////////////////////////////////////////////////////
//Main script called from loop within main routine of the firmware
////////////////////////////////////////////////////////////////////////
void MICRO_BOT::run()
{
	//returning control to AI
	if(Serial.available())
	{
		_REC_CHAR = Serial.read();
		if(_REC_CHAR == '0')
		{
			_BT_CONT = false;
		}
	}
	//*/
	// if not just run default routine.
	if(_BT_CONT == false)
	{
		//are we stuck and or too close to items
		//to move in any direction?
		if(digitalRead(_SW_ONE) == HIGH)
		{
			if(digitalRead(_DURATION >= _MIN_DISTANCE))
			{
					//if not all is good move freely
					_STUCK = false;
					Servos(0);
					//analogWrite(_LEFT_SERVO, _MIN);
					//analogWrite(_RIGHT_SERVO, _MAX);
			}
		}
		//are we stuck and or too close to items
		//to move in any direction?
		else if(digitalRead(_SW_ONE) == LOW)
		{
			if(digitalRead(_DURATION < _MIN_DISTANCE))
			{
					//Looks like we are stuck.
					//Don't go any ware until we are fixed.
					_STUCK = true;
					Servos(1);
					//analogWrite(_LEFT_SERVO, _FULL_STOP);
					//analogWrite(_RIGHT_SERVO, _FULL_STOP);
			}
		}
	}
	//else lets take it over.
	else if(_BT_CONT == true)
	{
		//calling bluetooth communications
		//control routine.
		bt_cont();
	}
}

////////////////////////////////////////////////////////////////////////
//returns a boolean value to the top stack if we are stuck or not.
////////////////////////////////////////////////////////////////////////
bool MICRO_BOT::stuck()
{
	return _STUCK;
}

void MICRO_BOT::Servos(int _DIRECTION)
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
////////////////////////////////////////////////////////////////////////
//Simple collision detection. needs work. called on by ping()
////////////////////////////////////////////////////////////////////////
void MICRO_BOT::collision_detection()
{
		if(digitalRead(_SW_ONE) == HIGH)
		{
			Servos(0);
		}
		else if(digitalRead(_SW_ONE) == LOW) // rear bumper has been hit
		{
			Servos(0);
		}
}

void MICRO_BOT::boarMICRO_BOT	KEYWORD1
init_start	KEYWORD2
board	KEYWORD2
run	KEYWORD2
stuck	KEYWORD2
ping	KEYWORD2
bt_cont	KEYWORD2                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                              