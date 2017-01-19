//**********************************************************************************************************************
//   GRADUATE RAMPAGING CHARIOTS PI INTERFACE MESSAGE HANDLERS - HEADER FILE
// *********************************************************************************************************************

#ifndef HANDLERS_H
#define HANDLERS_H

#include "MODSERIAL.h"
#include "core.h"
#include "sensorBus.h"
#include "enums.h"
#include "masterController.h"
#include "PiIOConfig.h"
#include "PiIO.h"


extern CORE chariot;

//Forward declare PiIO
class PiIO;

//Message ID 0 handler
void tp_ready(PiIO* pi, masterController* controller);

//Message ID 2 handler
void motion_request(PiIO* pi, masterController* controller);

//Message ID 4 handler
void ranger_request(PiIO* pi, masterController* controller);

//Message ID 6 handler
void tp_stop(PiIO* pi, masterController* controller);

void motion_control(void);


#endif




