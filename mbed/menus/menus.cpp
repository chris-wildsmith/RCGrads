//**********************************************************************************************************************
//   RAMPAGING CHARIOTS GRAD CONSOLE MENUS LIBRARY - SOURCE FILE
//   
// *********************************************************************************************************************

#include "menus.h"
#include "core_extensions.h"

extern command_prompt commandPrompt;
extern sensorBus sbus;


//**********************************************************************************************************************
//   BaseMenu Class Member Functions
// ********************************************************************************************************************* 
    
    //Constructor
    BaseMenu::BaseMenu(){MenuText = "";}
    
    //Print Menu member function
    void BaseMenu::printMenu(void)
    {
        debug.printf(MenuText.c_str());
    }

//**********************************************************************************************************************
//   MainMenu Class Member Functions
// ********************************************************************************************************************* 
   
   //Constructor
    MainMenu::MainMenu()
    {
        
        std::stringstream MenuTextStream; //Create stringstream object
        
        
        //********************************
        //*     Start of  Main Menu Text :
    
        //Enter required text into stringstream
        MenuTextStream  
                        << "===============================================================\n\r"
                        << "Main Menu:\n\r\n\r"
                        << "Please make your selection:\n\r\n\r"
                        << "1 - Start TP Control\n\r"
                        << "2 - Run Sensor Bus BIT\n\r"
                        << "3 - Get Sensor Bus readings\n\r"
                        << "4 - Manual Control\n\r"
                        << "5 - Calibration Menu\n\r"
                        << "6 - View config variables\n\r"
                        << "7 - Command Prompt\n\r\n\r"
                        << "Selection: ";
                        
        //*     End of Main Menu Text
        // ***************************** 
        
        
        //Convert string stream to string
        MenuText = MenuTextStream.str();
        
    }

    //**********************************
    //*     Start of Main Menu Actions :
    
    // Based on the choice, runs any required functions and return pointer to next required menu
    BaseMenu* MainMenu::getNextMenu(int choice, bool &IsStartSelected, bool &force_start)
    {
        BaseMenu* nextMenu = NULL; // Set up pointer making sure it's null

        switch (choice) 
        {
            
            case 1:
            {
                //Update the bool we got passed as reference to indicate start
                IsStartSelected = true;
                
                debug_command();
                debug.printf("Starting TP Control.");
                debug_newline();
            }
            break;
            
            case 2:
            {
                //nextMenu = new BITMenu;
                sbus.pbit();
            }
            break;
            
            case 3:
            {
                sbus.readings();
            }
            break;
            
            case 4:
            {
                // Manual control function
                 manual_control();   
            }
            break;
            
            case 5:
            {
                nextMenu = new CalMenu;
            }
            break;
            
            case 6:
            {
                
            }
            break;
            
            case 7:
            {
                //Initialise command prompt.  When exits, returns force_start status
                bool ForceStart = commandPrompt.start();
                
                if(ForceStart)  //If ForceStart command has been entered
                {
                    //Update the IsStartSelected bool we got passed as reference to indicate start and menu quit required.
                    IsStartSelected = true;
                    //Update the force_start bool we got passed as reference to indicate force start of interface required.
                    force_start = true;
                }
            }
            
            
            default:
            {
                // Do nothing - we won't change the menu
            }
    
        }
    
            return nextMenu; // Sending pointer to the next menu back to the main function
    }

    //*     End of Main Menu Actions
    // *******************************
    

//**********************************************************************************************************************
//   CalMenu Class Member Functions
// ********************************************************************************************************************* 
    
   
   //Constructor
    CalMenu::CalMenu()
    {
        
        std::stringstream MenuTextStream; //Create stringstream object
        
        
        
        //****************************************
        //*     Start of  Calibration Menu Text :
        
        //Enter text into stringstream
        MenuTextStream  << "\n\r\n\r===============================================================\n\r"
                        << "Calibration Menu:\n\r\n\r"
                        << "Please make your selection:\n\r\n\r"
                        << "1 - Calibrate stopping distance\n\r"
                        << "2 - Calibrate all turns\n\r"
                        << "3 - Calibrate 90 degree turn\n\r"
                        << "4 - Calibrate 45 degree turn\n\r"                 
                        << "5 - Back to main menu\n\r\n\r"                         
                        << "Selection: ";
                         
        //*     End of Calibration Menu Text
        // ***************************************
        
        //Convert string stream to string
        MenuText = MenuTextStream.str();
        
    }

    
    //*******************************************
    //*     Start of  Calibration Menu Actions :
    
    // Based on the choice, runs any required functions and return pointer to next required menu
    BaseMenu* CalMenu::getNextMenu(int choice, bool &IsStartSelected, bool &force_start)
    {
        BaseMenu *nextMenu = 0; // Set up pointer making sure it's null

        switch (choice) 
        {
            
            case 1:
            {
                //Calibrate stopping distance function - TBD
                //Do not update the nextMenu pointer so cal menu will reappear after calibration finished
            }
            break;
            
            case 2:
            {
                //Call both turn cal functions - TBD
                //Do not update the nextMenu pointer so cal menu will reappear after calibration finished
            }
            break;
            
            case 3:
            {
                //Call 90 degree turn cal function - TBD
                //Do not update the nextMenu pointer so cal menu will reappear after calibration finished
            }
        
            case 4:
            {
                //Call 45 degree turn cal function - TBD
                //Do not update the nextMenu pointer so cal menu will reappear after calibration finished
            }
            break;
            
            case 5:
            {
                nextMenu = new MainMenu;    
            }
            break;
            
            default:
            {
                // Do nothing - we won't change the menu
            }
        
        }
        
        return nextMenu; // Sending pointer to the next menu back to the main function
    }
    //*     End of Main Menu Actions
    // ************************************** 


//**********************************************************************************************************************
//   Standard Functions
// ********************************************************************************************************************* 

// Function to control menus
bool menu_init(BaseMenu* startMenu){
    
    bool IsStartSelected = false;
    bool force_start = false;
    
    BaseMenu* currentMenu = startMenu;
    
    while(!IsStartSelected)
    {
        currentMenu->printMenu();
        int choice = 0;
        
        choice = get_int();
        
        debug_newline();
        debug_newline();
        
        BaseMenu* NextMenu = currentMenu->getNextMenu(choice, IsStartSelected, force_start);
        
        //If NextMenu is not a null pointer (0), delete current menu object and create the new menu
        if(NextMenu)
        {
            //Free up memory by deleting old menu object
            delete currentMenu;
            
            //Update currentMenu pointer to point to NextMenu object
            currentMenu = NextMenu;        
        }
        
    }
    return force_start;
      
}




