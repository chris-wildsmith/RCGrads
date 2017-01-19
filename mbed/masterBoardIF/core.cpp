//**********************************************************************************************************************
//   RAMPAGING CHARIOTS CORE LIBRARY - SOURCE FILE
//   
// *********************************************************************************************************************

#include "core.h"

//**********************************************************************************************************************
//   GLOBAL VARIABLES
// *********************************************************************************************************************

    char neutral = 127;
    
    
//**********************************************************************************************************************
//   CORE CLASS METHODS
// *********************************************************************************************************************

//CORE constructor
CORE::CORE(PinName tx_pin, PinName rx_pin, int buffer_size) : master(tx_pin, rx_pin, buffer_size){
    master.baud(50000);
}

void CORE::straight(eDirection dir, int time_ms, short power)
{
    char direction_byte;
    Timer straight_timer;
     
    debug_command();
    
     
    if(dir == FORWARD)
    {
        direction_byte = neutral - ((float)power/100)*80;
    }
    else
    {
        direction_byte = neutral + ((float)power/100)*80; 
    }
   

    
    // Start
    straight_timer.start();

    while(straight_timer.read_ms()<time_ms)
    {       
        //Commands must be sent out repeatedly faster than once every 100ms otherwise robot comms will timeout and stop 
        master.putc(direction_byte); //Send longitudinal byte as forwards byte
        master.putc(neutral);  //Send lateral turn byte as neutral
        
        wait_ms(10);
    }
    
    //Stop
    stop();
    
 }

void CORE::turn(eRotation rot, int time_ms, short power)
{
    Timer turn_timer;
    
    //Start turn
    turn_timer.start(); //Start turn timer
    while(turn_timer.read_ms()<time_ms){ //Commands must be repeatedly sent out faster than once every 100ms otherwise robot comms will timeout and stop 
        
        turn_burst(rot, power);
        wait_ms(10);
    }
    
    //Stop turn
    stop();
}

// Forwards (fowards burst, no stop, no timer)
void CORE::straight_burst(eDirection dir, short power){
    
    char direction_byte;
    
    if(dir == FORWARD)
    {
        direction_byte = neutral - ((float)power/100)*80;
    }
    else
    {
       direction_byte = neutral + ((float)power/100)*80; // dir = BACKWARDS
    }
    
    master.putc(direction_byte);
    master.putc(neutral);
}

// Turn burst (no timer)
void CORE::turn_burst(eRotation rot, short power){
    
    char turn_byte;
    
    if(rot == CW)
    {
       turn_byte = neutral + ((float)power/100)*80;
    }
    else
    {
        turn_byte = neutral - ((float)power/100)*80;
    }

    
    master.putc(neutral);
    master.putc(turn_byte);
}

//Forwards whilst turning left (no stop, no timer)
//Use as part of loop
void CORE::forwards_left(short power_forward, short power_left){
    
    char forwards_byte = neutral - ((float)power_forward/100)*80;
    char left_turn_byte = neutral - ((float)power_left/100)*80;
    
    master.putc(forwards_byte);
    master.putc(left_turn_byte);
    
}

//Forwards whilst turning right (no stop, no timer)
//Use as part of loop
void CORE::forwards_right(short power_forward, short power_right){
    
    char forwards_byte = neutral - ((float)power_forward/100)*80;
    char right_turn_byte = neutral + ((float)power_right/100)*80;
    
    master.putc(forwards_byte);
    master.putc(right_turn_byte);
    
}


//Cuts power to motors causing chariot to come to a stop naturally (slower than emergency stop)
void CORE::stop(void){
    
    master.putc(neutral);//Send longitudinal byte as neutral
    master.putc(neutral);//Send lateral turn byte as neutral
}

//Emergency stop - shorts motor terminals inside driver chip to bring chariot to quicker stop than normal stop()
void CORE::emergency_stop(void){
    
    master.putc(0x00);
    master.putc(0x00);
}
  
//   END OF CORE CLASS METHODS
// *********************************************************************************************************************
