//*********************************************************************************************************************
//   COMMAND PROMPT LIBRARY FOR MBED - HEADER FILE
//   PAUL HARRIS, FEBRUARY 2015
// *********************************************************************************************************************

#ifndef COMMAND_PROMPT_H
#define COMMAND_PROMPT_H

#include "mbed.h"
#include <vector>
#include <string>
#include "serial.h"

//Config defines
#define MAX_COMMANDS 32
#define MAX_LENGTH_COMMAND 30

class command_prompt{
    
    public:
    
        //Constructor
        command_prompt(void (*default_handler)(void));
        
        //Public methods
    
        //Start command prompt
        bool start(void);
        
        //Add a command to the command list
        void add_command(const char* command, void (*function)(void), const char* help);
        
        //Return the current number of loaded commands
        int get_num_commands(void);
        
        //Get the next argument following the command text
        char* get_next_arg(void);

        //Set the default handler when command is not recognised.
        void set_default_handler(void (*function)(void));
        
        //List loaded commands and their help
        void list_commands(void);
        
        //Public variables
        bool quit; //Quits command prompt loop and returns
        bool force_start; //Bool to indicate if ForceStart command invoked for interface
        
    private:
    
        //Private types/variables
        
        //Number of commands currently loaded.
        int num_commands;
        //Buffer to hold command input
        char command_buf[MAX_LENGTH_COMMAND];
        //Next free position within command_buf
        int buf_pos;
        
        //Line terminator
        char term;
        //Command, argument delimiter
        char* delim;
        
        //Structure to hold command, function pointer pairs
        struct command_struct{
        
            const char* command;
            void (*function)(void);
            const char* help;    
        };
        
        //Type def of command structure
        typedef struct command_struct command_t;
        
        //Vector container to hold vector of command structures (command/function lookup list)
        std::vector<command_t> commands_list;
        
        //Pointer to default function to call if entered command does not match command list 
        void (*default_handler)(void);
        
        //Private methods
        
        //Clear the command_buf
        void clearBuffer(void);
    
};
 
#endif



