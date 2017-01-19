//**********************************************************************************************************************
//   GRADUATE RAMPAGING CHARIOTS CORE LIBRARY EXTENSIONS - HEADER FILE
// *********************************************************************************************************************

#ifndef CORE_EXT_H
#define CORE_EXT_H

#include "core.h"

extern CORE chariot;

void splash_screen(const char* version, const char* date, char* mac_addr);
void booting(void);

int atoi(char* ascii, int len);
char itoa(int num);

void manual_control(void);

#endif


