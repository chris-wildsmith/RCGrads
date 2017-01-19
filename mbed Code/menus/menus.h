//**********************************************************************************************************************
//   RAMPAGING CHARIOTS GRAD CONSOLE MENUS LIBRARY - HEADER FILE
//   
// *********************************************************************************************************************

#ifndef MENU_H
#define MENU_H

#include "mbed.h"
#include "serial.h"
#include "sensorBus.h"
#include "command_prompt.h"

#include <string>
#include <sstream>


class BaseMenu{
    
    public:
    
    //Constructor
    BaseMenu();
    
    //Deconstructor - requires empty {} brackets or throws compiler error
    virtual ~BaseMenu(){};
    
    //Method to get next action e.g. next menu or call a function
    virtual BaseMenu* getNextMenu(int choice, bool &iIsStartSelected, bool &force_start)=0;
    
    virtual void printMenu(void);
    
    
    protected:
    
    std::string MenuText; // This string will be shared by all children (i.e. derived) classes
    
};
    
class MainMenu : public BaseMenu {
    
   public:
   //Default Constructor
    MainMenu();

    // Get next action method
    virtual BaseMenu* getNextMenu(int choice, bool &IsStartSelected, bool &force_start);
    
};

class CalMenu : public BaseMenu {
    
   public:
   //Constructor
    CalMenu();
    
    // Get next action method
    virtual BaseMenu* getNextMenu(int choice, bool &IsStartSelected, bool &force_start);
    
};


bool menu_init(BaseMenu* startMenu);

#endif
