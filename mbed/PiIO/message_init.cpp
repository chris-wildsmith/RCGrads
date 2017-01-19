//**********************************************************************************************************************
//   GRADUATE RAMPAGING CHARIOTS PI INTERFACE MESSAGE INITIALISATION - SOURCE FILE
// *********************************************************************************************************************

#include "message_init.h"
#include "message_handlers.h"

void pi_message_init(PiIO* interface)
{
    interface->add_in_message(0, "TP Ready", 0, &tp_ready);
    interface->add_in_message(2, "Motion Request", 2, &motion_request);
    interface->add_in_message(4, "Ranger Request", 0, &ranger_request);
    interface->add_in_message(6, "Emergency Stop Request", 0, &tp_stop);
    
    interface->add_out_message(1, "MBED Ready", 0);
    interface->add_out_message(3, "Motion Acknowledge", 0);
    interface->add_out_message(5, "Ranger Results", 12);
    interface->add_out_message(7, "Emergency Stop Ack.", 0);
}



