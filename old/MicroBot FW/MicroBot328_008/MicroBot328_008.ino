////////////////////////////////////////////////////////////////////////
//Comments included in Main library.
//////////////////////////////////////////////////////////////////////////
//PROJECT:    MicroBot development board Firmware
//AUTHOR:     Jeremy Goss
//DATE:       4/26/2014
//SUMMERY:    Uses a custom 328 development board as the brains and 
//            main communication platform for a small robot. with
//            object avoidance/collision detection, bluetooth 
//            serial comms, ping sensor support, 4 servo support
//            4 switches, plus 5 additional I/O pins for additional
//            hardware. As well as a board routine, and direct access
//            controll of the bot over bluetooth.
//
//INCLUDED:   ChangeLog.h, MICRO_BOT328.cpp, MICRO_BOT328.h
//
//UPDATED:    04/26/14, 05/05/14
///////////////////////////////////////////////////////////////////////
//Includes
#include "PINS.h"
#include <Servo.h>
#include <EEPROM.h>
#include <MicroBot328.h>

//variables not named in the library
int const _FS = 0;
int const _MIN = 10;
int const _MAX = 170;
int _BS = 0;
int _DT = 500;
const long int Timer = 15000;
unsigned long previousMillis = 0;

//MicroBot object
MICRO_BOT BOT(_DT,_DCS0,_DCS1,_MIN,_MAX,
_BS,_SW1,_FS,_TRIG,_ECHO);

//Function prototype
void Main();

void setup()
{
  Serial.begin(9600);                          //Setting serial baud rate to 9800
  pinMode(_SW1, INPUT);                        //Setting rear bumper pin as input
  if(Serial.available())                       //Is the bluetooth responding?
  {
    Serial.write("MicroBot BT Connected!\n");  //We have bluetooth connection
  }
}

void loop()
{
  unsigned long currentMillis = millis();       //Setting up the current time
  
  if(BOT.init_start()==true)                    //Have we been initiated?
  {
    Main();                                     //If so run Main()
  }
  else if(BOT.init_start()==false)              //We have not been initiaed
  {
    if(currentMillis-previousMillis>Timer)      //Have enough millis passed to be board
    {
      Serial.write("I'm board\n");              
      BOT.board();                              //We are board Dance!
      previousMillis = currentMillis+(_DT*6.5); //Adding current time to previous time
    }
  }
}

void Main()
{
  BOT.run();                                    //Running main routine
  if(BOT.stuck()==false)                        //Are we stuck?
  {BOT.ping();}                                 //Run object avoidance and collision detection routine
  return;                                       //done start all over.
}
