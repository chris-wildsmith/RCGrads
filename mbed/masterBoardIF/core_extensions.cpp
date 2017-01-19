//**********************************************************************************************************************
//   GRADUATE RAMPAGING CHARIOTS CORE LIBRARY EXTENSIONS - SOURCE FILE
// *********************************************************************************************************************

#include "core_extensions.h"

void splash_screen(const char* version, const char* date, char* mac_addr){
    debug.printf("===============================================================\n\r");
    debug.printf("TEAM GR@DICAL RAMPAGING CHARIOT PROGRAM\n\r");
    debug.printf("Version: %s\n\r", version);
    debug.printf("Date: %s\n\r", date);
    debug.printf("MAC Address: %02x:%02x:%02x:%02x:%02x:%02x\n\r", mac_addr[0], mac_addr[1], mac_addr[2], mac_addr[3], mac_addr[4], mac_addr[5]);
    debug.printf("===============================================================\n\r\n\r");
}

void booting(void){
    char boot[] = "Booting.......... Please Wait...........";
    
    debug_newline();
    short i;
    for(i=0; i<41; i++)
    {
     debug.putc(boot[i]);
     wait_ms(80);   
    }
    
    debug_newline();
    debug_newline();
}


int atoi(char* ascii, int len){
    int i =0;
    int int_number=0;
    char number=0;
    
    for(i =0; i<len; i++){
        number= ascii[i] - '0'; // subtracts ASCII value for '0' off incoming byte ASCII value - implictly converts ascii[i] to int.
        int_number = int_number + number*pow(10,(double)(len-i-1));  //Cast (len-i-1)(int) to a double type required by pow.
    }
    return int_number;
}

//Converts a single digit int (0-9) to its single ASCII character equivalent
char itoa(int num){
    if(num<=9 && num >=0){
    return num + '0';
    }
    else {return '0';}
}


void manual_control(void){
    
    debug_newline();
    debug_newline();
    debug.printf("===============================================================\n\r");
    debug_command();
    debug.printf("Start Manual Control...");
    debug.printf("\n\r===============================================================\n\r");
    debug_newline();
    debug_newline();
    
    debug_status();
    debug.printf("Use w/a/s/d keys to control chariot.\n\r\t\t Press space bar to quit at any time!");
    
    //Buffer to store read character
    char buf = NULL;
    
    //Speed for manual control
    short power = 50;
    
    while(1){
        
        while(!debug.readable());
        
        buf = debug.getc();
        
        //Forwards
        if(buf == 'w')
        {
            chariot.straight_burst(FORWARD, power);
            debug_newline();
            debug_status();
            debug.printf("Forwards");
        }
        
        //Backwards
        else if(buf == 's')
        {
            chariot.straight_burst(BACKWARD, power);
            debug_newline();
            debug_status();
            debug.printf("Backwards");
        }
        
        //Left
        else if(buf == 'a')
        {
            chariot.turn_burst(CCW, power);
            debug_newline();
            debug_status();
            debug.printf("Left");
        }
        
        //Right
        else if(buf == 'd')
        {
            chariot.turn_burst(CW, power);
            debug_newline();
            debug_status();
            debug.printf("Right");
        }
        //Quit back to main menu
        else if(buf == ' ')
        {
            break;
        }
        //Else invalid character
        else
        {
         debug_newline();
         debug_error();
         debug.printf("Invalid key pressed!");
        }
    
    }
    
}
