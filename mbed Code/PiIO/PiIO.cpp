//**********************************************************************************************************************
//   GRADUATE RAMPAGING CHARIOTS PI (TP) INTERFACE - SOURCE FILE
// *********************************************************************************************************************
#include "PiIO.h"
#include "PiIOConfig.h"
#include "message_init.h"

//Constructor

PiIO::PiIO(Ethernet* eth_phy, const char* ip_address, masterController* controller, DigitalOut* eth_rx_led, DigitalOut* eth_tx_led)
{   
    _eth_phy = eth_phy;

    _eth_phy->address(_mac_addr); 

    _ip_address = ip_address;
    
    _controller = controller;
    
    _eth_rx_led = eth_rx_led;
    
    _eth_tx_led = eth_tx_led;

    //Initialise stop to false
    stop = false;

    //Run pi_message_init function to initialise messages
    pi_message_init(this);
    
}

void PiIO::start_interface(bool force_start)
{
    stop = false;
    
    short ID = -1;
    
    debug_status();
    debug.printf("PiIO: TP Interface initialised. Press ""s"" to disarm chariot at any time!");
    debug_newline();
    debug_newline();
    
    //If force start from command prompt
    if(force_start)
    {
        //Force arm the controller without requiring TP Ready message.
        _controller->arm();
    }
    
    //Message processing loop
    while(!stop)
    {
        ID = get_message();
        handle_message(ID);
        
        if(debug.getcNb() == 's')
        {
            //Stop interface
            stop_interface();
        }
    }
    
    return;
}

void PiIO::stop_interface(void)
{
    _controller->disarm();
    _eth_rx_led->write(0);
    _eth_tx_led->write(0);
    stop = true;
}

void PiIO::add_in_message(short ID, const char* name, unsigned short length, void (*handler)(PiIO*, masterController*))
{
    in_messages.push_back(message_in_t());
    
    in_messages[num_in_messages].ID = ID;
    in_messages[num_in_messages].payload_length = length;
    in_messages[num_in_messages].name = name;
    in_messages[num_in_messages++].handler = handler;
}

void PiIO::add_out_message(short ID, const char* name, unsigned short length)
{
    out_messages.push_back(message_out_t());
    
    out_messages[num_out_messages].ID = ID;
    out_messages[num_out_messages].payload_length = length;
    out_messages[num_out_messages++].name = name; 
}


short PiIO::get_message(void)
{
    char messageID;
    int size;
       
    //Clear frame buffer
    frame_buf.clear();
    
    //Attempt to receive ethernet frame

    //If ethernet not plugged in
    if(_eth_phy->link() == 0)
    {
        debug_error();
        debug.printf("PiIO: mbed to TP ethernet port unplugged!");
        debug_newline();
        wait(1);
        return -1;
    }
    
    //Check if frame waiting
    size  = _eth_phy->receive();
    
    //If no frame received, return
    if (size == 0){return -1;};

    //If here, valid ethernet frame received
    _eth_rx_led->write(1);
    
    char temp[size];
    frame_buf.reserve(size);
    
    //Read frame into temp
    _eth_phy->read(temp, size);
    
    //If invalid size etherent frame (<60 after FCS removed by PHY), return.
    //Must do after read otherwise malformed packet still be in phy buffer.
    if (size <60)
    {
        #ifdef FRAME_DEBUG
            debug.printf("PiIO: Malformed ethernet frame received and rejected!");
        #endif
        
        return -1;
    }

    //Insert temp (frame) into provided frame buffer
    frame_buf.insert(frame_buf.end(), &temp[0], &temp[size]);

    //Extract, validate and process frame payload and return detected message ID
    //Returns the detected messageID. Returns -1 if not our message format.
    messageID = parseFrame();
    
    _eth_rx_led->write(0);
    
    return messageID;   
    
}

short PiIO::parseFrame(void)
{
    
    //Parse the ethernet header
    parseEthernetHeader();

    #ifdef IP_USED
        //Parse the IPv4 header and return -1 if invalid
        if(!parseIPv4Header()){return -1;}
    #endif
    
    #ifdef UDP_USED
        //Parse the UDP header and return -1 if invalid
        if(!parseUDPHeader()){return -1;}
    #endif
    
    return parsePayload();
    
}

void PiIO::parseEthernetHeader(void)
{
#ifdef FRAME_DEBUG
    //Extract destination and source addresses from frame
    char dest_address[6];
    char source_address[6];
    
    for(int i=0; i<12;i++)
    {
        if(i<6)
        {
            dest_address[i]=frame_buf.at(i);    
        }
        else
        {
            source_address[i-6]=frame_buf.at(i);    
        }    
    }
    
    debug_status();
    debug.printf("PiIO: Processing %d byte ethernet frame received from %02X:%02X:%02X:%02X:%02X:%02X to %02X:%02X:%02X:%02X:%02X:%02X", frame_buf.size(),
        source_address[0], source_address[1], source_address[2], source_address[3], source_address[4], source_address[5], 
        dest_address[0], dest_address[1], dest_address[2], dest_address[3], dest_address[4], dest_address[5]);
        
    debug_newline();        
#endif

    //Erase addresses from front of buffer and the EtherType field, leaving just ethernet payload
    frame_buf.erase(frame_buf.begin(), frame_buf.begin()+ 14);
}

bool PiIO::parseIPv4Header(void)
{
    short header_length;
    
    //Check if frame cannot possibly contain an IP header with a payload
    if(frame_buf.size() < IPV4_HDR_MIN_SIZE)
    {
        #ifdef FRAME_DEBUG
        debug_status();
        debug.printf("PiIO: Frame discarded - Does not contain an IPv4 header (validation stage 1/3).");
        debug_newline();
        #endif
        return false;
    }
    
    //Validate and process first byte (containing version and Internet Header Length fields)
    char first_byte = frame_buf.at(0);
    
    //Check that first four bits of first byte (Version field) are equal to 4 (IPv4)
    //debug.printf("IP Version: %d", (first_byte >> 4));

    if ((first_byte >> 4) != 4)
    {
        #ifdef FRAME_DEBUG
        debug_status();
        debug.printf("PiIO: Frame discarded - Does not contain an IPv4 header (validation stage 2/3).");
        debug_newline();
        #endif
        return false;
    }

    #ifdef UDP_USED
        //Validate the Protocol byte to ensure it indicates UDP present in payload
        char protocol_byte = frame_buf.at(9);
        
        if(protocol_byte != IPV4_PROTOCOL_UDP)
        {
            #ifdef FRAME_DEBUG
            debug_status();
            debug.printf("PiIO: Frame discarded - IPv4 header indicates payload protocol is not UDP (validation stage 3/3).");
            debug_newline();
            #endif
            return false;    
        }
    #endif
    
    //Extract the IPv4 header length in bytes from the Internet Header Length field
    header_length = (first_byte & 0x0F)*4;//Multiply by 4 as IHL is no. 4 byte words
    
    //debug.printf("Header Length: %d", header_length);
    
    #ifdef FRAME_DEBUG
        
        //Extract destination and source addresses from frame
        char dest_address[4];
        char source_address[4];
        
        for(int i=12; i<20;i++)
        {
            if(i<16)
            {
                source_address[i-12]=frame_buf.at(i);    
            }
            else
            {
                dest_address[i-16]=frame_buf.at(i);    
            }    
        }
        
        debug_status();
        debug.printf("PiIO: Processing IPv4 frame received from %d.%d.%d.%d to %d.%d.%d.%d",
            source_address[0], source_address[1], source_address[2], source_address[3], 
            dest_address[0], dest_address[1], dest_address[2], dest_address[3]);
        debug_newline();

    #endif

    //Erase IP header from buffer, leaving next layer's payload
    frame_buf.erase(frame_buf.begin(), frame_buf.begin() + header_length);
    
    return true;
}

bool PiIO::parseUDPHeader(void)
{   
    //Check if frame cannot possibly contain an UDP header with a payload
    if(frame_buf.size() < UDP_HDR_SIZE)
    {
        #ifdef FRAME_DEBUG
        debug.printf("PiIO: Frame discarded: Does not contain valid UDP header!");
        debug_newline();
        #endif
        return false;
    }
    
    #ifdef FRAME_DEBUG
        //Extract destination and source ports from frame
        char dest_port_temp[2];
        char source_port_temp[2];
        unsigned short dest_port;
        unsigned short source_port;
        
        for(int i=0; i<4;i++)
        {
            if(i<2)
            {
                source_port_temp[i]=frame_buf.at(i);    
            }
            else
            {
                dest_port_temp[i-2]=frame_buf.at(i);    
            }    
        }
        
        source_port = short(source_port_temp[0] << 8 | source_port_temp[1]);  //Shift temp[0] left 8 bits (MSByte) and OR (bit-wise) with temp[1] (LSByte) to create unsigned short result 
        dest_port = short(dest_port_temp[0] << 8 | dest_port_temp[1]); 
        
        debug_status();
        debug.printf("PiIO: Processing UDP frame received from port %d to port %d",
            source_port, dest_port);
        debug_newline();        
    #endif

    //Erase UDP header from buffer, leaving next layer's payload
    frame_buf.erase(frame_buf.begin(), frame_buf.begin()+ UDP_HDR_SIZE);

    return true;
}

short PiIO::parsePayload(void)
{
    char payload_length_temp[2] = {NULL};
    unsigned short payload_length;
    char messageID;
    
    //Print payload contents
    #ifdef FRAME_DEBUG
    debug.printf("Payload data: ");
    for(int i=0; i<frame_buf.size();i++)
    {
        debug.printf("%02X ", frame_buf.at(i));    
    }
    debug_newline();
    #endif
    
    //If first byte of payload is not START_MESSAGE reject frame
    if(frame_buf.at(0) != START_MESSAGE)
    {    
        //Empty buffer and return
        #ifdef PI_DEBUG
            debug_status();
            debug.printf("PiIO: Unrecognised payload format. Frame discarded.");
            debug_newline();
        #endif
        frame_buf.clear();
        //Return -1 as messageID (indicates invalid message payload received)
        return -1;
    }

    //START_MESSAGE is first byte, remove from frame buffer
    frame_buf.erase(frame_buf.begin());
    
    //Extract header bytes
    messageID = frame_buf.at(0);

    payload_length_temp[0] = frame_buf.at(1);
    payload_length_temp[1] = frame_buf.at(2);
    
    //Shift payload_length[0] left 8 bits (MSByte) and OR (bit-wise) with payload_length[1] (LSByte) to create 16 bit int result 
    payload_length = short(((payload_length_temp[0] << 8) | payload_length_temp[1]));
    
    //Check for valid header - i.e. There is a message ID and payload_length match in in_messages.
    if(isValidheader(messageID, payload_length))
    {
        //Erase message ID and length bytes from front of buffer, leaving just message payload (if any)
        frame_buf.erase(frame_buf.begin(), frame_buf.begin()+ 3);
        
        //Remove all bytes (padding) from back of payload up to END_MESSAGE byte
        while(frame_buf.back() != END_MESSAGE)
        {
            frame_buf.pop_back();    
        }
        //Remove END_MESSAGE byte
        frame_buf.pop_back();
        
        //If actual payload length does not match payload length stated in header, discard message
        if(!len_check(payload_length))
        {
            //Empty buffer and return
            #ifdef PI_DEBUG
                debug_warn();
                debug.printf("PiIO: Actual payload length does not match payload length stated in header! Message discarded!");
                debug_newline();
            #endif
            frame_buf.clear();
            //Return -1 as messageID (indicates invalid message payload received)
            return -1;
        }
        //If actual payload length matches payload length, return message ID.
        else
        {
            //Valid message parsed - return messageID for message handler.
            return messageID;
        }
        
    }
    
    //Invalid header 
    else
    {
        #ifdef PI_DEBUG
            debug_warn();
            debug.printf("PiIO: Invalid message header received from TP. Message discarded.");
            debug_newline();
        #endif
        //Return -1 as messageID (indicates invalid message payload received)
        return -1;   
    }
   
}

bool PiIO::len_check(int length)
{
    if(frame_buf.size() == length){return true;}
    else {return false;}
}


void PiIO::send_message(char messageID, const char* payload)
{
    _eth_tx_led->write(1);
    
    //Get message index from message_ID
    int i = get_index(OUT, messageID);
    
    //If there is no matching message ID, do not send and return
    if(i<0)
    {
        #ifdef PI_DEBUG
            debug_error();
            debug.printf("PiIO: Msg send aborted: Attempted to send a non-defined message ID %d!", messageID);
            debug_newline();
        #endif
        
        return;
    }
    
    //Get required message payload length
    int length = (int)out_messages[i].payload_length;
       
    //Initialise payload array first element to 0.  Partial initialisation sets rest of array to 0 (padding).
    char frame_payload[60] = {0};
    
    char payload_length_temp[2] = {NULL, NULL};
    
    //Extract upper byte of length
    payload_length_temp[0] = (char)(length >> 8);
    //Extract lower byte of length
    payload_length_temp[1] = (char)(length);
    
    //Add MAC Destination (broadcast)
    frame_payload[0] = 0xFF;
    frame_payload[1] = 0xFF; 
    frame_payload[2] = 0xFF;
    frame_payload[3] = 0xFF; 
    frame_payload[4] = 0xFF; 
    frame_payload[5] = 0xFF;
    
    //Add MAC Source
    frame_payload[6] =  0x00;
    frame_payload[7] =  0x02; 
    frame_payload[8] =  0xF7;
    frame_payload[9] =  0xF2; 
    frame_payload[10] = 0x09; 
    frame_payload[11] = 0x54;
    
    //Add Ethertype
    frame_payload[12] =  0x06;
    frame_payload[13] =  0x00; 
    
    //Add frame payload
    
    //Add start message byte
    frame_payload[14] = 0xFF;
    //Add message ID
    frame_payload[15] = messageID;
    //Add payload length bytes
    frame_payload[16] = payload_length_temp[0];
    frame_payload[17] = payload_length_temp[1];
   
   //Add message payload
    for(int k = 0; k<length; k++)
    {
        frame_payload[18+k] = payload[k];    
    }
    
    //Add end message
    frame_payload[18 + length] = END_MESSAGE;
    
    //Remaining entries of frame_payload are zero (padding)
    
    //Send frame payload
    _eth_phy->write(frame_payload, 60);
    _eth_phy->send();
    _eth_tx_led->write(0);
    
    #ifdef PI_DEBUG
        debug_status();
        debug.printf("PiIO: Sending Message ID %d (%s) to TP...", messageID, out_messages[i].name);
        debug_newline();
    #endif

}

int PiIO::get_index(eCommsDir dir, char messageID)
{
   if(dir == IN)
   {
        for(int i=0; i<num_in_messages; i++)
        {
            if(in_messages[i].ID == messageID)
            {
                return i;
            }
        }
    }
    else //OUT
    {
        for(int i=0; i<num_out_messages; i++)
        {
            if(out_messages[i].ID == messageID)
            {
                return i;
            }
        }
    }
    //No message defined matching the messageID passed in
    return -1;
}


bool PiIO::isValidheader(char messageID, unsigned short payload_length)
{  
    //Find the index of stored message matching the messageID passed in (if any)
    int i = get_index(IN, messageID);
    
    //debug.printf("%d %d %d ", messageID, payload_length, i);
    
    //If there is no matching message type with ID matching the passed in messageID  -> Not a valid header
    if(i<0)
    {
        #ifdef PI_DEBUG
            debug_error();
            debug.printf("PiIO: Message ID %d received does not match any defined message!", messageID);
            debug_newline();
        #endif
        
        return false;
    }
    
    //Check if payload_length matches required payload length of matched message
    if(in_messages[i].payload_length == payload_length)
    {
        return true;    
    }
    
    //No length match -> Not a valid header
    return false;
}

void PiIO::handle_message(short messageID)
{
    //If valid message payload received from parse_message
    if(messageID != -1)
    {
        //Get message index from message_ID
        int i = get_index(IN, messageID);

        //If there is a message with this ID defined.  Should be as this will already have been checked.
        if(i>=0)
        {
            #ifdef PI_DEBUG
                debug_status();
                debug.printf("PiIO: Processing Message ID %d (%s) message from TP...", messageID, in_messages[i].name);
                debug_newline();
            #endif
            
            //Invoke corresponding message handler
            (*in_messages[i].handler)(this, _controller);
        }
    }
    //Clear frame buffer
    frame_buf.clear();
}

const char* PiIO::getIPAddress(void)
{
     return _ip_address;   
}


char* PiIO::getMACAddress(void)
{
    return _mac_addr;
}

