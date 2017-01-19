//**********************************************************************************************************************
//   RAMPAGING CHARIOTS CORE LIBRARY - HEADER FILE
//   
// *********************************************************************************************************************

/** @file
 *
 * @brief This documentation describes the core s/w repository provided for the Grad and Apprentice Rampaging Chariot Teams 2014-15.
 *
 * @image html http://homepage.ntlworld.com/beehive77/core_logo.png
 * 
 * <b> Purpose of Repository </b>
 *
 * The purpose of the core repository is to provide both teams with a tried and tested basic s/w platform to:
 * - Control the basic motion of a chariot via the master board (AUTO v1.0 PIC) (Core library)
 * - Provide debug serial port to PC to print debug text (Core library)
 * - Interface with HC-SRF04 ultrasonic ranger sensors (hc_srf04 library)
 *
 * Each team may then write their own, more complex code to control the chariot, building on top of the core functions.
 *
 * <b> Repository Libraries </b>
 *
 * The core s/w repository consists of a number of s/w libraries:
 *
 * - Core library
 * - hc_srf04 library
 *
 * <b>N.B.</b> It is recommended that the libraries are left <b>unaltered</b> and any additional code/functionality required is written in <b>seperate</b> libraries.\n
 * This will allow any updates we may make to the core libraries to be pulled in without disrupting any additional code you may choose to write.\n\n
 *
 * <b> Core library </b>
 *
 * - This class-based library contains a number of basic public methods to issue motion commands via an mbed serial port to the Rampaging Chariot Master board (AUTO v1.0 PIC installed).
 * - It removes the need of the user to directly control the serial port communications between the mbed and the master board - this is all handled by the core s/w.
 * - Instead, all the user need do is to call the basic public methods provided by the core s/w.
 * - <b> IMPORTANT NOTE: </b>
 * - When using the straight_burst, turn_burst, forwards_left and forwards_right member functions, DO NOT have two consecutive requests from one speed direction to the other (e.g. FORWARDS to BACKWARDS or CW to CCW).
 * - Instead, insert a stop() call between the two requests.
 * - Failure to do so will cause the master board to shutdown to prevent damage to the motors.
 * - A reboot of the master board will be required to resume operation.
 *
 * <b> hc_srf04 library </b>
 *
 * - This library supports a class-based interface between the mbed and HC-SRF04 ultrasonic ranger sensors to allow distance sensing in cm.
 * - The number of sensors supported is limited by number of free GPIO pins on the mbed.
 *
 * <b> Required H/W </b>
 *
 * - This Core library is written for an mbed LPC1768 interfacing to an Rampaging Chariot Master board with the <b>AUTO V1.0 PIC installed</b>.
 * - It will not work if a V3 or V4 (non-AUTO) PIC is installed on the Master board.
 * - The s/w is designed to be used on an mbed installed into the core mbed H/W PCBs provided to each team.
 * - It can be customised to be used with an mbed on a breadboard, although this is not recommended.
 * - The slave board should have a V3 or V4 (non-AUTO) PIC installed.
 *
 * <b> Master Board Interface Using Core H/W: </b>
 *
 * - The mbed serial port Tx/Rx pins for connecting to the master board are user-defined when calling the CORE constructor (see constructor documentation).
 * - When using the core H/W board, the Tx pin <b>MUST BE</b> set to p13 and the Rx pin to p14.
 * - N.B. The Rx pin is currently not supported in the core s/w and so is effectively unused.
 * - The image below defines the connections that must be made between the mbed and the master board.  It is recommended that 3-wire servo wire and connectors are used for this purpose:
 *
 *
 * @image html http://homepage.ntlworld.com/beehive77/master_mbed_connections.png
 *
 *
 * <b>  N.B. </b> It is essential that the master ground pin is connected to the mbed ground for the serial port to work.
 *
 * \n<b> AUTO/MANUAL MODE </b>
 *
 * - The master board can work in AUTO mode (under control of serial port commands from mbed), or MANUAL mode (under control from radio-control receiver).
 * - The two pins shown in the diagram above (AUTO/MANUAL mode), control which mode the master board is set to on power up.
 * - To select AUTO mode, short (jumper) the two pins together
 * - To select MANUAL mode, leave pins disconnected from each other.
 * - For ease of use, it is recommended that a SPDT switch be installed to perform this function rather than a jumper.

*/

//**********************************************************************************************************************
//   GRADUATE RAMPAGING CHARIOTS MASTER MOTOR CONTROLLER BOARD LIBRARY - HEADER FILE
//   
// *********************************************************************************************************************

#ifndef CORE_CLASS_H
#define CORE_CLASS_H

#include "mbed.h"
#include "serial.h"
#include "core_enums.h"

//**********************************************************************************************************************
//   CORE CLASS
// ********************************************************************************************************************* 

/**
 * This class the provides the basic motion control serial interface between the mbed and a Rampaging Chariot Master Motor Control board with an AUTO V1.0 PIC installed.
 *
 * The class abstracts the control of the serial interface between the mbed and master board by providing a set of <b>basic</b> motion control methods.
 *
 * These basic motion control methods can be utilised by both teams to create more complex compound motion control functions.
 *
 *
 */


class CORE {
    
            public:
    
            //CORE class constructor
            /**
            * @brief Create CORE instance (only one should be created)
            * @param tx_pin The mbed serial port Tx pin that is connected to the Master board Rx pin (p13 for core h/w)
            * @param rx_pin The mbed serial port Rx pin that is connected to the Master board Tx pin (p14 for core h/w)
            * @param buffer_size The required buffer size for the serial port interface to the Master board (default is 512 bytes/characters)
            */
            CORE(PinName tx_pin, PinName rx_pin, int buffer_size);
            
            //Public Member Functions
            
            /* Primatives */
    
            /** 
            * @brief Moves chariot straight forwards/backwards for the specified time at the specified power.
            * @param dir Direction (FORWARD OR BACKWARD) of travel required.
            * @param time_ms Duration (in ms) of travel required.
            * @param power Power/Speed (%) of travel required.
            */
            void straight(eDirection dir, int time_ms, short power);
            
            /** 
            * @brief Spot-turn (CW/CCW) for the specified time at the specified power.
            * @param dir Direction (CW OR CCW) of turn required.
            * @param time_ms Duration (in ms) of turn required.
            * @param power Power/Speed (%) of turn required.
            */
            void turn(eRotation rot, int time_ms, short power);
            
            /** 
            * @brief Stops chariot.
            */
            void stop(void);
            
            /** 
            * @brief Stops chariot (appears to be same deceleration as stop method...)
            */
            void emergency_stop(void);  
            /*            */
            
            /* Others */
            
            /** 
            * @brief Sends single forwards/backwards command to master board (only for advanced use in loops).
            * @param dir Direction (FORWARD or BACKWARD) of travel required.
            * @param power Power/Speed (%) of travel required.
            */
            void straight_burst(eDirection dir, short power);
            
            /** 
            * @brief Sends single CW/CCW spot-turn command to master board (only for advanced use in loops).
            * @param dir Direction (CW or CCW) of turn required.
            * @param power Power/Speed (%) of turn required.
            */
            void turn_burst(eRotation rot, short power);
            
            /** 
            * @brief Normal left turn for the specified time at the specified power (only for advanced use in loops).
            * @param power Power/Speed (%) of turn required.
            */
            void forwards_left(short power_forward, short power_left);
            
            /** 
            * @brief Normal left turn for the specified time at the specified power (only for advanced use in loops).
            * @param power Power/Speed (%) of turn required.
            */
            void forwards_right(short power_forward, short power_right);
        
            /*        */

            private:
            //Serial port to master board
            MODSERIAL master;
    
            };


#endif
