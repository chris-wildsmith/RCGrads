//**********************************************************************************************************************
//   GRADUATE RAMPAGING CHARIOTS MASTER BOARD CONTROLLER - SOURCE FILE
// *********************************************************************************************************************

#include "masterController.h"

//Constructor
masterController::masterController(CORE* chariot, short safety_timeout)
{
    _chariot = chariot;
    _safety_timeout = safety_timeout;
    _armed = false;
    _motion = STOP;    
    _speed = 0;
    motion_update = false;
}

//Assign values to eMotionStrings char array (can't do this in constructor)
const char* masterController::eMotionStrings[] = {"Forwards", "Backwards", "Left", "Right", "Stop"};

//Public Member Functions
bool masterController::isArmed(void){return _armed;}

void masterController::motionRequest(eMotion motion, short speed)
{
    if(_armed)
    {
        //Update motionController state variables
        _motion = motion;
        _speed = speed;
        
        debug_command();
        debug.printf("Master Controller: %s request at %d%% speed.", eMotionStrings[_motion], _speed);
        debug_newline();
        
        //Set motion_update flag so safety timeout is reset in motionController
        motion_update = true;
    }
    else
    {
        debug_warn();
        debug.printf("Master Controller: Motion request ignored as chariot not armed...");
        debug_newline();
    }

}

//Private Member Functions
void masterController::arm(void)
{
    if(!isArmed())
    {
        //Attach motionController function to be called every 10ms
        //to control master board
        comms_ticker.attach_us(this, &masterController::motionController, 10000);
        _armed = true;
    }
    
    debug_warn();
    debug.printf("Master Controller: Chariot is ARMED!");
    debug_newline();
}

void masterController::disarm(void)
{
    if(isArmed())
    {
        //Stop motors
        _motion = STOP;
        //Set ticker timer to 30mins as interupt does not get stopped in h/w when handler detached - still runs.
        comms_ticker.attach(NULL,0);
        //Detach motionController function from ticker
        comms_ticker.detach();
        
        //Stop and reset safety timer
        safety_timeout.stop();
        safety_timeout.reset();
        
        _armed = false;
        
        debug_status();
        debug.printf("Master Controller: Chariot is disarmed and SAFE to approach.");
        debug_newline();
    }
}

//Motion control loop called periodically by comms ticker
void masterController::motionController(void)
{
    //If motion has been updated (motion request received), stop, reset and start the timer
    if(motion_update)
    {
        //Stop and reset and start timer
        safety_timeout.stop();
        safety_timeout.reset();
        
        if(_motion != STOP)
        {
            safety_timeout.start();
        }
        
        //Reset motion_update flag
        motion_update = false;
    }
    
    //If safety timeout exceeded, stop chariot
    if(safety_timeout.read() >= _safety_timeout)
    {
        //Set motion state variable to motionS to stop chariot
        _motion = STOP;
        
        //Stop and reset timer
        safety_timeout.stop();
        safety_timeout.reset();
        
        debug_warn();
        debug.printf("Master Controller: Motion request safety timeout exceeded. Stopped.");
        debug_newline();
    }
    
    switch(_motion)
    {
        case FORWARDS:
        _chariot->straight_burst(FORWARD, _speed);
        break;
        case BACKWARDS:
        _chariot->straight_burst(BACKWARD, _speed);
        break;
        case LEFT:
        _chariot->turn_burst(CCW, _speed);
        break;
        case RIGHT:
        _chariot->turn_burst(CW, _speed);
        break;
        case STOP:
        _chariot->stop();
        break;
    }
    
}
