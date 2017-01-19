#ifndef IPV4_H
#define IPV4_H

#include "options.h"
#include "inet_chksum.h"
#include "serial.h"

typedef struct PACK_STRUCT{
u8_t version_ihl;
u8_t dscp_ecn;
u16_t total_len;
u16_t ID;
u16_t flags_frag_offset;
u8_t ttl;
u8_t protocol;
u16_t checksum;
u32_t src_addr;
u32_t dest_addr;
}IPv4Hdr_t;


class IPv4Hdr
{
    public:
    
    //Constructor
    IPv4Hdr(void);

    //Public methods
    void setSourceAddr(const char addr1, const char addr2, const char addr3, const char addr4);
    void setDestAddr(const char addr1, const char addr2, const char addr3, const char addr4);
    void setProtocol(const char);
    void genCRC(void);
    void setPayloadLength(unsigned int len);
    void print(void);
    
    void getSourceAddr(char* ip_addr);
    void getDestAddr(char* ip_addr);
    u8_t getProtocol(void);
    u16_t getCRC(void);
    u16_t getTotalLength(void);
    
    
    private:
    //Private variables
    IPv4Hdr_t hdr;
};
#endif