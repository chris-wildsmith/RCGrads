//**********************************************************************************************************************
//   GRADUATE RAMPAGING CHARIOTS SERIAL HELPER FUNCTIONS - SOURCE FILE
// *********************************************************************************************************************

#include "serial.h"


void debug_comment(void){debug.printf("DEBUG>> ");}
void debug_command(void){debug.printf("COMMAND>> ");}
void debug_status(void){debug.printf("STATUS>> ");}
void debug_error(void){debug.printf("ERROR>> ");}
void debug_warn(void){debug.printf("WARNING>> ");}
void debug_newline(void){debug.printf("\n\r");}

void get_line(char* result)
{
    //Create string buffer to hold iostream data
    std::stringbuf sbuf;
    
    //Create input/output stream
    std::iostream stream(&sbuf);
    
    // Without dynamic allocation (new), returned char pointer (s) will reside on the function's stack and will therefore be destroyed on exit.
    //char* s = new char[100];
    // Must delete s after used elsewhere otherwise will be memory leak
    
    while(1)
    {
        //While nothing available to read from debug port, do nothing
        while(!debug.readable());
        
        //Get char from MODSERIAL i/p buffer
        char buffer = debug.getc();
        
        //If new line delimiter received, break from loop
        if(buffer == '\n'){break;}
        //Otherwise, insert buffer char into stream
        else {stream << buffer;}
    }
    
    //Put the stream as a c-string (char array) into the array pointed to by the argument (result)
    stream.get(result,100);
    
}

int get_int(void)
{   
    //Create string buffer to hold istream data
    std::stringbuf sbuf;
    
    //Create input stream
    std::iostream stream(&sbuf);
    
    int result = 0;
    
    while(1)
    {
        //While nothing available to read from debug port, do nothing
        while(!debug.readable());
        
        //Get char from MODSERIAL i/p buffer
        char buffer = debug.getc();
        
        //Check if new line delimiter received
        if(buffer == '\r')
        {
            //stream >> result outputs stream to int result - safely converting from ASCII to int without crashing if not able to convert (unlike atoi).
            //If stream cannot be converted, returns null pointer (0).
            
            //Check for correct conversion by checking for a non-zero returned pointer.
            if(stream >> result){break;}
            
            //If not able to be converted to int, stream did not contain a valid number
            //N.B. Stream contents still in stream as did not extract, needs clearing
            else {
                debug.printf("\n\rPlease enter a valid number!\n\r");
                
                //Clear the error interal state flag of stream object to allow it to be used again
                stream.clear();
                //Add a \r delimiter to end of stream for the ignore method to work without error
                stream << '\r';
                //Extract and discard all characters in stream up to the \r delimiter (end of stream), or 256 characters reached
                stream.ignore(256, '\r');
                //Skip to next iteration
                continue;
                }
        }

        //Insert char into stream
        stream << buffer;

    }
    
    //Return the int
    return result; 
    
}

void delete_1_char(void)
{
    debug.putc(0x08);   
}


//Backspace and delete 2 characters
void delete_2_char(void)
{
    debug.putc(0x08);
    debug.putc(0x20);
    debug.putc(0x08);
    debug.putc(0x08);
}

//Backspace and delete 3 characters
void delete_3_char(void)
{
    debug.putc(0x08);
    debug.putc(0x08);
    debug.putc(0x20);
    debug.putc(0x20);
    debug.putc(0x08);
    debug.putc(0x08);
    debug.putc(0x08); 
}

