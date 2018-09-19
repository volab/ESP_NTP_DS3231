/**********************************************************************

SerialCommand.cpp
COPYRIGHT (c) 2013-2015 Gregg E. Berman

Part of DCC++ BASE STATION for the Arduino

**********************************************************************/

// DCC++ BASE STATION COMMUNICATES VIA THE SERIAL PORT USING SINGLE-CHARACTER TEXT COMMANDS
// WITH OPTIONAL PARAMTERS, AND BRACKETED BY < AND > SYMBOLS.  SPACES BETWEEN PARAMETERS
// ARE REQUIRED.  SPACES ANYWHERE ELSE ARE IGNORED.  A SPACE BETWEEN THE SINGLE-CHARACTER
// COMMAND AND THE FIRST PARAMETER IS ALSO NOT REQUIRED.

// See SerialCommand::parse() below for defined text commands.

#include "SerialCommand.h"
/*
#include "DCCpp_Uno.h"
#include "Accessories.h"
#include "Sensor.h"
#include "Outputs.h"
#include "EEStore.h"
#include "Comm.h"
*/

extern RTC_DS3231 rtc;
extern DateTime NTPTime;
extern int __heap_start, *__brkval;

///////////////////////////////////////////////////////////////////////////////

char SerialCommand::commandString[MAX_COMMAND_LENGTH+1];
// volatile RegisterList *SerialCommand::mRegs;
// volatile RegisterList *SerialCommand::pRegs;
// CurrentMonitor *SerialCommand::mMonitor;

///////////////////////////////////////////////////////////////////////////////

// void SerialCommand::init(volatile RegisterList *_mRegs, volatile RegisterList *_pRegs, CurrentMonitor *_mMonitor){
void SerialCommand::init(){
  // mRegs=_mRegs;
  // pRegs=_pRegs;
  // mMonitor=_mMonitor;
  sprintf(commandString,"");
} // SerialCommand:SerialCommand

///////////////////////////////////////////////////////////////////////////////

// void SerialCommand::process(){
char SerialCommand::process(){
  char c;
    
    while(INTERFACE.available()>0){    // while there is data on the serial line
     c=INTERFACE.read();
     if(c=='<')                    // start of new command
       sprintf(commandString,"");
     else if(c=='>')               // end of new command
       // parse(commandString); 
        return commandString[0];
     else if(strlen(commandString)<MAX_COMMAND_LENGTH)    // if comandString still has space, append character just read from serial line
       sprintf(commandString,"%s%c",commandString,c);     // otherwise, character is ignored (but continue to look for '<' or '>')
    } // while
  
} // SerialCommand:process
   
///////////////////////////////////////////////////////////////////////////////

// void SerialCommand::parse(char *com){
    // char buf[255];
    // switch(com[0]){

// /***** SET ENGINE THROTTLES USING 128-STEP SPEED CONTROL ****/    

    // case 'S':       // <S> set DS3231 time
      // INTERFACE.println(F("\n<VOLAB> commande S a traiter"));
      // mRegs->setThrottle(com+1);
      // break;

        

    // case 'D':     // <D> for display

      // INTERFACE.println(F("\n<VOLAB> commande D a traiter"));
      // INTERFACE.println("");
      // break;

    // case 'N':     // <N> for display NTP time
        // sprintf(buf, "<VoLAB> NTP full date (RTCLib.h)  : %d/%d/%d %d:%d:%d", 
        // NTPTime.day(), NTPTime.month(), NTPTime.year(),
        // NTPTime.hour(), NTPTime.minute(), NTPTime.second()); 
        // INTERFACE.println( buf); 
    // break;      

      
  // } // switch
// }; // SerialCommand::parse

///////////////////////////////////////////////////////////////////////////////


