//**********************************************************************************************************************
//   RAMPAGING CHARIOTS DEBUG SERIAL PORT - HEADER FILE
//   
// *********************************************************************************************************************

/** @file 
* @brief This header file is used for convenience to hold any declarations of serial ports used by the core repositories and also to include the MODSERIAL header file.
* Include this file in source files where you wish to use the mbed serial communications.\n\n
* <b> N.B. </b>  The serial ports are only declared here.  They must be defined elsewhere (e.g. main.cpp).
*/

#ifndef SERIAL_H
#define SERIAL_H

#include "mbed.h"
#include <string>
#include <sstream>
#include "MODSERIAL.h"
#include "serial_config.h"

extern MODSERIAL pc;
extern MODSERIAL xbee;      //Serial link to Xbee wireless debug link

void debug_comment(void);
void debug_command(void);
void debug_status(void);
void debug_error(void);
void debug_warn(void);
void debug_newline(void);

void get_line(char* result);
int get_int(void);

void delete_1_char(void);
void delete_2_char(void);
void delete_3_char(void);

#endif
