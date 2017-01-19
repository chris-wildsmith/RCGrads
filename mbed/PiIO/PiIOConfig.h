//**********************************************************************************************************************
//   GRADUATE RAMPAGING CHARIOTS PI INTERFACE CONFIG HEADER FILE
// *********************************************************************************************************************

#ifndef PI_IO_CONFIG_H
#define PI_IO_CONFIG_H

//<--***BEGIN DEBUG CONFIGURATION***-->

//Comment this out if message handler debug is not required
//define MESSAGE_HANDLER_DEBUG

//Comment this out if high level pi interface debug not required
//#define PI_DEBUG

//Comment this out if low level pi interface debug not required
//#define FRAME_DEBUG


//<--***END DEBUG CONFIGURATION***-->


//<--***BEGIN PROTOCOL CONFIGURATION***-->

//Start and end message byte definitions
#define START_MESSAGE  0xFF
#define END_MESSAGE '\n'

//Define which protocols are used in received messages from TP (if all commented out, will use raw ethernet)
#define IP_USED
//#define UDP_USED

//<--***END PROTOCOL CONFIGURATION***-->


//<--***BEGIN IPv4 CONFIGURATION***-->

//The minimum valid size of an IPv4 header
#define IPV4_HDR_MIN_SIZE 20

//The IANA IPv4 Protocol ID for UDP
#define IPV4_PROTOCOL_UDP 0x11

//<--***END IPv4 CONFIGURATION***-->


//<--***BEGIN UDP CONFIGURATION***-->

//The size of a valid UDP header (fixed)
#define UDP_HDR_SIZE 8
//Define UDP to connect to
#define PORT 5050

//<--***END UDP CONFIGURATION***-->

#endif
