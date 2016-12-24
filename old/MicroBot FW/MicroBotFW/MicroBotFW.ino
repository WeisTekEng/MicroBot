/*-----( INCLUDES )-----*/
#include <Wire.h>  // Comes with Arduino IDE
#include <LiquidCrystal_I2C.h>
#include <Servo.h>
//#include <MicroBot_Library.h>
//#include <EEPROM.h>
//#include <SoftwareSerial.h>
#include "IO_PINS.h"
//#include "VARIABLES.h"
//#include <SoftwareServo.h>

/*-----( Declare Constants )-----*/
int const _FULL_STOP = 0;
int const _MIN_SPEED = 10;
int const _MAX_SPEED = 170;
int const _DELAY_TIMER = 500;
const long int Timer = 15000;

/*-----( Declare objects )-----*/
// set the LCD address to 0x27 for a 20 chars 4 line display
// Set the pins on the I2C chip used for LCD connections:
//                    addr, en,rw,rs,d4,d5,d6,d7,bl,blpol
LiquidCrystal_I2C lcd(0x27, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE);  // Set the LCD I2C address
//MICROBOT BOT(_DT,_LSVO,_RSVO,_MIN, _MAX, _BS,_RB,_FS,_LFB,_RFB);    
//SoftwareSerial BT(_RXD,_TXD);
Servo PAN;
Servo TILT;
Servo LEFT;
Servo RIGHT;

/*-----( Declare Variables )-----*/
int start = 0;
unsigned long previousMillis  = 0;    //used to keep track of time.
int servoCenter = 89;
int servoLeft = 0;
int servoRight = 150;
int servoUp = 0;
int servoDown = 60;

/*-----( Declare Prototypes )-----*/
void Main();
int Initialize();               //Checks surroundings for edges.

/*-----( Matricies )-----*/
//int VISION[10][10] = {0}; // A two dimensional array to keep track of soroundings.
//int GROUND[5][5] = {0}

/*----( SETUP: RUNS ONCE )----*/
void setup()   
{
  Serial.begin(9600);      // Used to type in characters
  //BTCOM.begin(9600);       // Initialize Bluetooth comms
  lcd.begin(20,4);         // initialize the lcd for 20 chars 4 lines, turn on backlight
  PAN.attach(_PAN);
  TILT.attach(_TILT);
  LEFT.attach(_LSVO);
  RIGHT.attach(_RSVO);
 
//-------- Write characters on the display ------------------  
  lcd.setCursor(3,0);
  lcd.print("MicroBot V7A");
  delay(1000);
  lcd.setCursor(2,1);
  lcd.print("From WeisTek");
  delay(1000);  
  lcd.setCursor(0,2);
  lcd.print("");
  lcd.setCursor(0,3);
  delay(2000);   
  lcd.print("McBot Initilizing...");
  delay(5000);
  Initialize();
  delay(8000);
  // Wait and then tell user they can start the Serial Monitor and type in characters to
  // Display. (Set Serial Monitor option to "No Line Ending")
  lcd.clear();
  lcd.setCursor(0,0); //Start at character 0 on line 0
  lcd.print("Start Serial Monitor");
  lcd.setCursor(0,1);
  lcd.print("MENU");
  lcd.setCursor(0,2);
  lcd.print("");  
  
}
/*--(end setup )---*/

/*----( LOOP: RUNS CONSTANTLY )----*/
void loop()   
{
  if(start == true)                               
  {
    unsigned long currentMillis = millis();
    {
      // when characters arrive over the serial port...
      if (Serial.available()) {
        // wait a bit for the entire message to arrive
        delay(100);
        // clear the screen
        lcd.clear();
        // read all the available characters
        while (Serial.available() > 0) {
          // display each character to the LCD
          lcd.write(Serial.read());
        }
      }
      
    }
  }
}
/*
  if(BOT.init_start()==true)
  {
    Main();
  }
  else if(BOT.init_start()==false)
  {
    if(currentMillis-previousMillis>Timer)
    {
      BT.write("I'm board\n");
      BOT.boardom();
      previousMillis = currentMillis + (_DT*6.5);
    }
  }
}
void Main()
{
  BOT.run();
  if(BOT.stuck()==false)
  {BT.ping();}
  //{BOT.collision_detection();}
  return;
}
/*
void BT_Check()
{
  char recvChar;
    if(BT.available())
    {
      recvChar = BT.read();
        if(recvChar == 'h')
        {
          BT.write("I hear you\n");
        }
        else if(recvChar == 'w')
        {
          BT.write("MicroBot: Moving forward\n");
          BOT.forward();
        }
        else if(recvChar == 's')
        {
          BT.write("MicroBot: Backing up\n");
          BOT.backup();
        }
        else if(recvChar == 'a')
        {
          BT.write("MicroBot: Turning left\n");
          BOT.turn_l();
        }
        else if(recvChar == 'd')
        {
          BT.write("MicroBot: Turning right\n");
          BOT.turn_r();
        }
    }
}
//*/
/* ( THE END ) */

int Initialize()
{
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.write("Checking Servos");
  delay(1000);
  TILT.write(servoCenter);
  delay(1000);
  PAN.write(servoCenter);
  delay(1000);
  lcd.setCursor(0,1);
  lcd.write("Checking BT");
  // initialize Bluetooth here.
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.write("Init done.");
  return 1;
}

