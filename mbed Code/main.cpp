//**********************************************************************************************************************
//   GRADUATE RAMPAGING CHARIOTS SOFTWARE - SOURCE FILE
// *********************************************************************************************************************
#include "mbed.h"
#include "core.h"
#include "core_extensions.h"
#include "menus.h"
#include "command_prompt.h"
#include "commands.h"
#include "sensorBus.h"
#include "masterController.h"
#include "PiIO.h"
#include "IPv4.h"

//*******************************
//   BUILD INFO
// ******************************

static const char* version = "2.1";
static const char* date = "11/06/2016";

//*******************************
//   MODSERIAL SERIAL PORTS SETUP
// ******************************

//****Debug ports - wired (pc) or wireless (xbee) - which one is active is defined in serial_config.h****
MODSERIAL pc(USBTX, USBRX);      //Serial link to PC serial monitor (wired)                                                    
MODSERIAL xbee(p9,p10);      //Serial link to Xbee wireless debug link

//******************************
//   sensorBus CLASS CONSTRUCTOR
// *****************************
I2C i2c_bus(p28,p27); // I2C port, p28 = sda, p27 = scl
sensorBus sbus(&i2c_bus);

//***********************************
//   COMMAND PROMPT CLASS CONSTRUCTOR
// **********************************
//Create command_prompt object
command_prompt commandPrompt(&invalid_command);

//*************************
//   CORE CLASS CONSTRUCTOR
// ************************
  
//Create a CORE object to control chariot
CORE chariot(p13, p14, 512); //p13 = tx to master board , p14 = rx from master board, 512 byte tx/rx buffer

//***********************************
//   CHARIOT CONTROLLER CLASS CONSTRUCTOR
// **********************************
//Instantiate chariot controller object
//and pass in master serial port dependancy
masterController controller(&chariot);

//******************************************************
//   ETHERNET PORT SETUP
// *****************************************************
//Create ETHERNET object (ethernet PHY) for comms to TP.
Ethernet eth;
//Create ethernet link actvity led digital outputs
DigitalOut eth_rx_led(LED1);
DigitalOut eth_tx_led(LED2);

//**********************************
//   PI INTERFACE CLASS CONSTRUCTOR
// *********************************

//Create Pi Interface Object and 
//pass in pointer to Ethernet object, required mbed static IP address,
//pointer to chariotController object and pointers to ethernet link activity leds
PiIO pi(&eth, "192.168.0.128", &controller, &eth_rx_led, &eth_tx_led);

//**********************************
//   SETUP
// *********************************
void setup()
{
    //Initiate serial ports

    debug.baud(9600);
    
    splash_screen(version, date, pi.getMACAddress());
    
    //Enable/disable sensor bus sensors
    //            F     FR     BR     B     BL     FL
    sbus.enable(false, false, false, false, false, false);
    
}

//**********************************************************************************************************************
//   MAIN CODE
// *********************************************************************************************************************

int main()
{
    setup();

    //IPv4 Packet generation testing
    /*
    IPv4Hdr hdr;
    hdr.setSourceAddr(192,168,0,128);
    hdr.setDestAddr(192,168,0,1);
    hdr.setProtocol(0x19);
    hdr.setPayloadLength(10);
    hdr.genCRC();

    hdr.print();
    */

    BaseMenu* startMenu = new MainMenu;
    
    while(1)
    {
        //Load main menu. Returns whether force_start command selected from command prompt
        bool force_start = menu_init(startMenu);

        //Start pi TP interface with force start set appropriately
        pi.start_interface(force_start);
        debug_newline();
    }
    
}












