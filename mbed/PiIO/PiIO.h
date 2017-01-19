//**********************************************************************************************************************
//   GRADUATE RAMPAGING CHARIOTS PI (TP) INTERFACE - HEADER FILE
// *********************************************************************************************************************

#ifndef INTERFACE_H
#define INTERFACE_H

#include "mbed.h"
#include "serial.h"
#include "enums.h"
#include "masterController.h"

#include <vector>


class PiIO
{
    public:
        
        //Constructor
        PiIO(Ethernet* eth_phy, const char* ip_address, masterController* controller, DigitalOut* eth_rx_led, DigitalOut* eth_tx_led);
        
        //Public Member variables
        
        std::vector<char> frame_buf;
    
        //Public Member Functions
        void start_interface(bool force_start);
        void stop_interface(void);
        
        void add_in_message(short ID, const char* name, unsigned short length, void (*handler)(PiIO*, masterController*));
        void add_out_message(short ID, const char* name, unsigned short length);
        
        void send_message(char messageID, const char* payload);
        const char* getIPAddress(void);
        char* getMACAddress(void);

    private:
        
        //Private Member variables
        Ethernet* _eth_phy;
        masterController* _controller;
        DigitalOut* _eth_rx_led;
        DigitalOut* _eth_tx_led;
        const char* _ip_address;
        char _mac_addr[6];
        int num_in_messages;
        int num_out_messages;
        bool stop;
        //Structure to hold in messages
        struct message_in_struct
        {
            char ID;
            const char* name;
            unsigned short payload_length;
            void (*handler)(PiIO*, masterController*);
        };
    
        //Type def of message_in structure
        typedef struct message_in_struct message_in_t;
        
        //Structure to hold out messages
        struct message_out_struct
        {
            char ID;
            const char* name;
            unsigned short payload_length;
        };
    
        //Type def of message_out structure
        typedef struct message_out_struct message_out_t;
        
        //Vector containers to hold vector of in/out message structures
        std::vector<message_in_t> in_messages;
        std::vector<message_out_t> out_messages;
    
        //Private Member Functions
        int get_index(eCommsDir dir, char messageID);
        short get_message(void);
        short parseFrame(void);
        void parseEthernetHeader(void);
        bool parseIPv4Header(void);
        bool parseUDPHeader(void);
        short parsePayload(void);
        bool len_check(int length);
        bool isValidheader(char messageID, unsigned short payload_length);
        void handle_message(short messageID);
        
};

#endif


