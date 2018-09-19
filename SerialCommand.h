/**********************************************************************

SerialCommand.h
COPYRIGHT (c) 2013-2015 Gregg E. Berman

Part of DCC++ BASE STATION for the Arduino

**********************************************************************/

#ifndef SerialCommand_h
#define SerialCommand_h

// #include "PacketRegister.h"
// #include "CurrentMonitor.h"
#include "ESP_NTP_DS3231.h"

#define  MAX_COMMAND_LENGTH         30

struct SerialCommand{
  static char commandString[MAX_COMMAND_LENGTH+1];
  // static volatile RegisterList *mRegs, *pRegs;
  // static CurrentMonitor *mMonitor;
  // static void init(volatile RegisterList *, volatile RegisterList *, CurrentMonitor *);
  static void init();
  // static void parse(char *);
  // static void process();
  static char process();
}; // SerialCommand
  
#endif




