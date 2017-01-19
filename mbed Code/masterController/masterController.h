//**********************************************************************************************************************
//   GRADUATE RAMPAGING CHARIOTS MASTER BOARD CONTROLLER  - HEADER FILE
// *********************************************************************************************************************

#ifndef CHARIOT_CONTROLLER_H
#define CHARIOT_CONTROLLER_H

#include "mbed.h"
#include "serial.h"
#include "core.h"
#include "controller_enums.h"

class masterController
{
    public:
        //Constructor
        masterController(CORE* chariot, short safety_timeout=2);    
    
        //Public Member Functions
        bool isArmed(void);
        void arm(void);
        void disarm(void);
        
        void motionRequest(eMotion motion, short speed);
        
    private:
        //Private member variables
        eMotion _motion;
        static const char* eMotionStrings[];
        short _speed;
        short _safety_timeout;
        Ticker comms_ticker;
        Timer safety_timeout;
        bool motion_update;
        bool _armed;
        CORE* _chariot;
        
        //Private Member Functions
        void motionController(void);
};
 
#endif