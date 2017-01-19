#include "IPv4.h"

//Constructor
    IPv4Hdr::IPv4Hdr()
    {
        hdr.version_ihl = (4 << 4) | sizeof(IPv4Hdr_t);
        hdr.dscp_ecn = 0;
        hdr.total_len = sizeof(IPv4Hdr);
        hdr.ID = 0;
        hdr.flags_frag_offset = 0;
        hdr.ttl = 8;
        setProtocol(0x8F); //First unassigned IANA protocol
        hdr.checksum = 0;
        setSourceAddr(0,0,0,0);
        setDestAddr(0,0,0,0);
    }

    void IPv4Hdr::setSourceAddr(const char addr1, const char addr2, const char addr3, const char addr4)
    {
        //Store in network order without using htonl
        #if BYTE_ORDER == BIG_ENDIAN
        hdr.src_addr = (u32_t)((addr1 & 0xFF) << 24) | \
        (u32_t)((addr2) & 0xFF) << 16)) | \
        (u32_t)((addr3) & 0xFF) << 8))  | \
        (u32_t)(addr4) & 0xFF);
        #else
        hdr.src_addr = (u32_t)((addr4 & 0xFF) << 24) | \
        (u32_t)((addr3 & 0xFF) << 16) | \
        (u32_t)((addr2 & 0xFF) << 8)  | \
        (u32_t)(addr1 & 0xFF);
        #endif
    }
    
    void IPv4Hdr::setDestAddr(const char addr1, const char addr2, const char addr3, const char addr4)
    {
        //Store in network order without using htonl
        #if BYTE_ORDER == BIG_ENDIAN
        hdr.dest_addr = (u32_t)((addr1 & 0xFF) << 24) | \
        (u32_t)((addr2 & 0xFF) << 16) | \
        (u32_t)((addr3 & 0xFF) << 8)  | \
        (u32_t)(addr4 & 0xFF);
        #else
        hdr.dest_addr = (u32_t)((addr4 & 0xFF) << 24) | \
        (u32_t)((addr3 & 0xFF) << 16) | \
        (u32_t)((addr2 & 0xFF) << 8)  | \
        (u32_t)(addr1 & 0xFF);
        #endif
    }
    
    void IPv4Hdr::setProtocol(const char protocol)
    {
        hdr.protocol = protocol;
    }
    
    void IPv4Hdr::genCRC(void)
    {
        hdr.checksum = lwip_standard_chksum((void*)&hdr, sizeof(IPv4Hdr));
    }
    
    void IPv4Hdr::setPayloadLength(unsigned int len)
    {
        hdr.total_len = lwip_htons(sizeof(IPv4Hdr) + len);
    }
    
    void IPv4Hdr::print(void)
    {
        debug.printf(
            "IPv4 Header:\n\r"
            "Version/IHL: %u (fixed)\n\r"
            "DSCP/ECN: %u (fixed)\n\r"
            "Total Length: %u\n\r"
            "ID: %u (fixed)\n\r"
            "Flags/Frag: %u (fixed)\n\r"
            "TTL: %u (fixed)\n\r"
            "Protocol: %u\n\r"
            "Checksum: %u\n\r"
            "Source IP: %u\n\r"
            "Dest. IP: %u\n\r",
            hdr.version_ihl,
            hdr.dscp_ecn,
            lwip_ntohs(hdr.total_len),
            lwip_ntohs(hdr.ID),
            lwip_ntohs(hdr.flags_frag_offset),
            hdr.ttl,
            hdr.protocol,
            lwip_ntohs(hdr.checksum),
            lwip_ntohl(hdr.src_addr),
            lwip_ntohl(hdr.dest_addr));
    }

    void IPv4Hdr::getSourceAddr(char* ip_addr)
    {
        u32_t a = lwip_ntohl(hdr.src_addr);
        sprintf(ip_addr, "%d:%d:%d:%d", a & 0xFF000000, a & 0x00FF0000, a & 0x0000FF00, a & 0x000000FF);
    }
    
    void IPv4Hdr::getDestAddr(char* ip_addr)
    {
        u32_t a = lwip_ntohl(hdr.dest_addr);
        sprintf(ip_addr, "%d:%d:%d:%d", a & 0xFF000000, a & 0x00FF0000, a & 0x0000FF00, a & 0x000000FF);
    }
    
    u8_t IPv4Hdr::getProtocol(void)
    {
        return hdr.protocol;
    }
    
    u16_t IPv4Hdr::getCRC(void)
    {
        return lwip_ntohs(hdr.checksum);
    }
    
    u16_t IPv4Hdr::getTotalLength(void)
    {
        return lwip_ntohs(hdr.total_len);
    }