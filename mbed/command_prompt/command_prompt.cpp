//*********************************************************************************************************************
//   COMMAND PROMPT LIBRARY FOR MBED - SOURCE FILE
//   PAUL HARRIS, FEBRUARY 2015
// *********************************************************************************************************************

#include "command_prompt.h"
#include "commands.h"

//Uncomment line below if you want command debug info.
//#define COMMAND_DEBUG

//Constructor
command_prompt::command_prompt(void (*default_handler)(void))
{
    set_default_handler(default_handler);
    delim = " ";
    term = '\r';
    num_commands =0;
    
    add_commands();
};


//Public methods

    //Read in and process command, return force start status
    bool command_prompt::start(void)
    {
        char temp = 0;
        
        int i = 0;
        bool match = false;
        quit = false;
        force_start = false;
        bool startNewCommand = true;
        
        while(!quit)
        {   
            if(startNewCommand)
            {
                //Display command prompt
                debug_newline();
                debug_command();
                startNewCommand = false;
            }
            
            while(!debug.readable());
            temp = debug.getc();
            
            if(temp == term) //If line terminator received, parse command
            {
                debug_newline();
                debug_newline();
                
                char* parsed_command = strtok(command_buf, delim);
                
                if(parsed_command != NULL)
                {
                    
                    //First check if command is quit
                    if(strncmp(parsed_command, "quit", MAX_LENGTH_COMMAND) == 0) //If command is "quit", break from command prompt loop
                    {
                        #ifdef COMMAND_DEBUG
                        debug_status();
                        debug.printf("Quit command received. Clearing command buffer and returning to menu.");
                        debug_newline();
                        #endif
                        
                        clearBuffer(); //Clear command buffer
                        break; //Break out of command prompt loop
                    }
                    
                    //Command is not quit, continue processing

                    match = false;
                    for(i=0; i < num_commands; i++ ) //Loop through command list looking for match
                    {
                        #ifdef COMMAND_DEBUG
                        debug_status();
                        debug.printf("Matching %s with %s.", parsed_command, commands_list[i].command);
                        debug_newline();
                        #endif
                        
                        
                        if(strncmp(parsed_command, commands_list[i].command, MAX_LENGTH_COMMAND) == 0)
                        {
                            #ifdef COMMAND_DEBUG
                            debug_status();
                            debug.printf("Match found!  Invoking command...");
                            debug_newline();
                            #endif
    
                            (*commands_list[i].function)();
                            match = true;
                            break;
                        }
                        
                    }
                    
                    if(!match && (default_handler != NULL))
                    {
                        #ifdef COMMAND_DEBUG
                        debug_status();
                        debug.printf("No match found!  Invoking default command handler...");
                        debug_newline();
                        #endif
                        
                        (*default_handler)();  
                    }
                    
                    clearBuffer();
                    startNewCommand = true;
                }
                
                else // Command empty
                {
                    clearBuffer();
                    
                    debug_newline();
                    debug_error();
                    debug.printf("No command entered! Type 'help' for valid commands.");
                    
                    startNewCommand = true;
                }
                
            }
            
            
            else if(temp == 127 || temp == 8) //If backspace or delete received
            {
                if(buf_pos > 0) //If at least 1 character in buffer
                {
                    command_buf[--buf_pos] = '\0'; //Delete last character in buffer
                }
                
                debug.putc(0x20); //Blank the character
                delete_1_char(); //Backspace
            }
            
            
            else //Character not delimiter or backspace/delete
            {
                if(buf_pos < MAX_LENGTH_COMMAND) //If max command length not exceeded
                {
                    
                    command_buf[buf_pos] = temp;
                    command_buf[++buf_pos] = '\0'; //Null terminate next character
                }
                
                else                            //If max command length exceeded
                {
                    debug_newline();
                    debug_error();
                    debug.printf("Command too long! - Rejected.");
                    
                    clearBuffer();
                    
                    debug_newline();
                    debug_command();
                }

            }
        }
        return force_start;
    };
    
    //Add a command to the command list
    void command_prompt::add_command(const char* command, void (*function)(void), const char* help)
    {
        if(num_commands < MAX_COMMANDS)
        {
            
            commands_list.push_back(command_t());
            
            commands_list[num_commands].command = command;
            commands_list[num_commands].function = function;
            commands_list[num_commands++].help = help;

        }
        
        else
        {
            #ifdef COMMAND_DEBUG
            debug_error();
            debug.printf("Failed to add command %s!  Max number of supported commands reached!", command);
            debug_newline();
            #endif   
        }
    };
    
    //Return the current number of loaded commands
    int command_prompt::get_num_commands(void)
    {
        return num_commands;
    };

    //Get the next argument following the command text
    char* command_prompt::get_next_arg(void)
    {
        return strtok(NULL, delim);
    };
    
    //Set the default handler when command is not recognised.
    void command_prompt::set_default_handler(void (*function)(void))
    {
        default_handler = function;   
    };
    
    //List loaded commands and their help
    void command_prompt::list_commands(void)
    {
        int i = 0;
        
        debug.printf("Available commands:");
        debug_newline();
        debug_newline();
       
        for(i = 0; i < get_num_commands(); i++)
        {
            debug.printf("\t%s \t %s", commands_list[i].command, commands_list[i].help);
            debug_newline();
        }
        
    }
    
//Private methods
    
    //Clear the command_buf
    void command_prompt::clearBuffer(void)
    {
        command_buf[0] = '\0'; //Set first position of buffer to null terminator.
        buf_pos = 0;
        
        #ifdef COMMAND_DEBUG
        debug_status();
        debug.printf("Command buffer cleared");
        debug_newline();
        #endif
    };




