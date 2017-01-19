//*********************************************************************************************************************
//   COMMANDS LIBRARY FOR MBED - SOURCE FILE
//   PAUL HARRIS, FEBRUARY 2015
// *********************************************************************************************************************

#include "commands.h"

extern command_prompt commandPrompt;

void add_commands(void)
{
    commandPrompt.add_command("help", &help, "Lists available commands and their help");
    commandPrompt.add_command("ls", &list_directory, "Lists contents of mbed root directory");
    commandPrompt.add_command("ForceStart", &force_start, "Force start the TP interface as armed. Use with caution!");
}


void invalid_command(void)
{
    debug_error();
    debug.printf("Not a valid command! Type 'help' for valid commands.");
    debug_newline();
}

void list_directory(void)
{
    /* COMMENTED OUT AS DOESN'T SEEM TO WORK ANYMORE AND CRASHES MBED
    debug.printf("MBED Root Directory Contents:");
    debug_newline();
    debug_newline();
      
    DIR *d = opendir("/local"); // Opens the root directory of the local file system
    struct dirent *p;
    while((p = readdir(d)) != NULL)
    {         // Print the names of the files in the local file system
      debug.printf("\t%s\n\r", p->d_name);        
    }
    closedir(d);
    debug_newline();
    debug_command();
    */
}

void help(void)
{
    commandPrompt.list_commands();
    debug.printf("\tquit\t Return to the main menu\n\r");
    debug_newline();
}

void force_start(void)
{
    debug_status();
    debug.printf("Force starting TP interface as armed!");
    debug_newline();
    debug_newline();
    
    //Set force start flag to true to invoke force start on command prompt quit
    commandPrompt.force_start = true;
    //Quit command prompt back to main menu
    commandPrompt.quit = true;
}

