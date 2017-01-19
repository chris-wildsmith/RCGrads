//**********************************************************************************************************************
//   GRADUATE RAMPAGING CHARIOTS PI INTERFACE MESSAGE HANDLERS - SOURCE FILE
// *********************************************************************************************************************

//TO DO 10/05/16:
//1) Create a message handler base class file that is friend of PiIO class to allow the armed flag to be protected rather than public.
//2) Make classes for each handler that inherit the base class
//3) Move motion_control function to a seperate file and class (Motion Controller)

#include "message_handlers.h"
#include "PiIOConfig.h"

extern sensorBus sbus;

//static eMotion motion;

//static Ticker update_motion;

//static Timer safety_timeout;

//static bool motion_update = false;

static short speed = 0;

//Message ID 0 handler
void tp_ready(PiIO* pi, masterController* controller)
{ 
    #ifdef MESSAGE_HANDLER_DEBUG
        debug_command();
        debug.printf("PiIO: TP start command received.");
        debug_newline();
    #endif
    
    //Arm the chariot to accept motion request messages
    if(!controller->isArmed())
    {
        controller->arm();
    }
    
    //Send mbed ready message to TP
    wait(0.5);
    pi->send_message(1, NULL);
}

//Message ID 2 handler
void motion_request(PiIO* pi, masterController* controller)
{   
    //Check for valid speed byte
    if(pi->frame_buf[1] == 0 || pi->frame_buf[1] <101)
    {
        speed = pi->frame_buf[1];
    }
    else
    {
        #ifdef MESSAGE_HANDLER_DEBUG
            debug_status();
            debug.printf("PiIO: Invalid motion command speed byte value '%d' received!", pi->frame_buf[1]);
            debug_newline();
        #endif
        
        //Stop chariot and return
        controller->motionRequest(STOP, 0);
        
        return;
    }
    
    switch(pi->frame_buf[0])
    {
        case 0: //Stop
            #ifdef MESSAGE_HANDLER_DEBUG
                debug_command();
                debug.printf("PiIO: Stop called from TP...");
                debug_newline();
            #endif
            
            controller->motionRequest(STOP, 0);
            //Send motion ack
            pi->send_message(3, NULL);
        break;
        case 1: //Forwards
            #ifdef MESSAGE_HANDLER_DEBUG
                debug_command();
                debug.printf("PiIO: Forward called from TP at %d%% speed...", speed);
                debug_newline();
            #endif
            
            controller->motionRequest(FORWARDS, speed);
            //Send motion ack
            pi->send_message(3, NULL);
        break;
        case 2: //Back
            #ifdef MESSAGE_HANDLER_DEBUG
                debug_command();
                debug.printf("PiIO: Back called from TP at %d%% speed...", speed);
                debug_newline();
            #endif
            controller->motionRequest(BACKWARDS, speed);
            //Send motion ack
            pi->send_message(3, NULL);
        break;
        case 3: //Left
            #ifdef MESSAGE_HANDLER_DEBUG
                debug_command();
                debug.printf("PiIO: Left called from TP at %d%% speed...", speed);
                debug_newline();
            #endif
            controller->motionRequest(LEFT, speed);
            //Send motion ack
            pi->send_message(3, NULL);
        break;
        case 4: //Right
            #ifdef MESSAGE_HANDLER_DEBUG
                debug_command();
                debug.printf("PiIO: Right called from TP at %d%% speed...", speed);
                debug_newline();
            #endif
            controller->motionRequest(RIGHT, speed);
            //Send motion ack
            pi->send_message(3, NULL);    
        break;
        default:
            #ifdef MESSAGE_HANDLER_DEBUG
                debug_status();
                debug.printf("PiIO: Invalid motion command byte motion type value '%d' received!", pi->frame_buf[0]);
                debug_newline();
            #endif
            //Stop and do not acknowledge motion request
            controller->motionRequest(STOP, 0);
        break;
    }
}

//Message ID 4 handler
void ranger_request(PiIO* pi, masterController* controller)
{
    //12 byte payload array
    char payload[12];
    int dist = 0;
    
    debug_command();
    debug.printf("PiIO: Reading sensors...");
    debug_newline();
    
    dist = sbus.read(F);
    if(dist)
    {
        payload[0] = (char)(dist >> 8);
        payload[1] = (char)dist;
    }
    else //Invalid reading - insert reading of 601 (invalid)
    {
        payload[0] = 2;
        payload[1] = 89;
    }
    
    dist = sbus.read(FR);
    if(dist)
    {
        payload[2] = (char)(dist >> 8);
        payload[3] = (char)dist;
    }
    else //Invalid reading - insert reading of 601 (invalid)
    {
        payload[2] = 2;
        payload[3] = 89;
    }
    
    dist = sbus.read(BR);
    if(dist)
    {
        payload[4] = (char)(dist >> 8);
        payload[5] = (char)dist;
    }
    else //Invalid reading - insert reading of 601 (invalid)
    {
        payload[4] = 2;
        payload[5] = 89;
    }
    
    dist = sbus.read(B);
    if(dist)
    {
        payload[6] = (char)(dist >> 8);
        payload[7] = (char)dist;
    }
    else //Invalid reading - insert reading of 601 (invalid)
    {
        payload[6] = 2;
        payload[7] = 89;
    }
    
    dist = sbus.read(BL);
    if(dist)
    {
        payload[8] = (char)(dist >> 8);
        payload[9] = (char)dist;
    }
    else //Invalid reading - insert reading of 601 (invalid)
    {
        payload[8] = 2;
        payload[9] = 89;
    }
    
    dist = sbus.read(FL);
    if(dist)
    {
        payload[10] = (char)(dist >> 8);
        payload[11] = (char)dist;
    }
    else //Invalid reading - insert reading of 601 (invalid)
    {
        payload[10] = 2; //Appears on terminal emulator as a STX (start of text) character
        payload[11] = 89; //Appears on terminal emulator as a Y character
    }    
    
    debug_command();
    debug.printf("PiIO: Sending ranger results to TP...");
    debug_newline();
    
    pi->send_message(5, payload);
}

//Message ID 6 handler
void tp_stop(PiIO* pi, masterController* controller)
{   
    #ifdef MESSAGE_HANDLER_DEBUG
        debug_command();
        debug.printf("PiIO: TP disarm command received.");
        debug_newline();
    #endif
    
    //Send Emergency Stop Ack
    pi->send_message(7, NULL);
    
    //Disarm controller and stop interface
    pi->stop_interface();
}