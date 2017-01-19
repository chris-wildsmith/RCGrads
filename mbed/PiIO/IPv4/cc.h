#ifndef __CC_H__ 
#define __CC_H__ 

//cc.h - COMPILER CONFIGURATION/OPTIONS

#include <stdint.h>
#include "mbed.h"

/* Types based on stdint.h */
typedef uint8_t     u8_t; 
typedef int8_t      s8_t; 
typedef uint16_t    u16_t; 
typedef int16_t     s16_t; 
typedef uint32_t    u32_t; 
typedef int32_t     s32_t; 

//Define compiler attribute to pack a struct (or any other variable)
#define PACK_STRUCT __attribute__ ((__packed__))

#define LITTLE_ENDIAN 1234

#define BIG_ENDIAN 4321

//Define the byte order of the system
#define BYTE_ORDER LITTLE_ENDIAN /* ARM/LPC17xx is little endian only */

//Use the platform optimised byteswap functions for hton and ntoh functions
#define LWIP_PLATFORM_BYTESWAP 1

//Define the LPC1768 platform specific optimised htons function
#define LWIP_PLATFORM_HTONS(x)      __REV16(x)
#define LWIP_PLATFORM_HTONL(x)      __REV(x)

#if BYTE_ORDER == BIG_ENDIAN /*No byte swapping needed. htons and ntohl do nothing*/
    #define lwip_htons(x) (x)
    #define lwip_ntohs(x) (x)
    #define lwip_htonl(x) (x)
    #define lwip_ntohl(x) (x)
    #define PP_HTONS(x) (x)
    #define PP_NTOHS(x) (x)
    #define PP_HTONL(x) (x)
    #define PP_NTOHL(x) (x)
#else /* BYTE_ORDER != BIG_ENDIAN -> Little endian system -> Byte swapping needed for hton and ntoh functions*/
    #if LWIP_PLATFORM_BYTESWAP
        #define lwip_htons(x) LWIP_PLATFORM_HTONS(x)
        #define lwip_ntohs(x) LWIP_PLATFORM_HTONS(x)
        #define lwip_htonl(x) LWIP_PLATFORM_HTONL(x)
        #define lwip_ntohl(x) LWIP_PLATFORM_HTONL(x)
    #else /* !LWIP_PLATFORM_BYTESWAP -> Use default non platform optimised reference byteswap functions in options.c*/
        u16_t lwip_htons(u16_t x);
        u16_t lwip_ntohs(u16_t x);
        u32_t lwip_htonl(u32_t x);
        u32_t lwip_ntohl(u32_t x);
    #endif /* LWIP_PLATFORM_BYTESWAP */

    /* These macros should be calculated by the preprocessor and are used
       with compile-time constants only (so that there is no little-endian
       overhead at runtime). */
    #define PP_HTONS(x) ((((x) & 0xff) << 8) | (((x) & 0xff00) >> 8))
    #define PP_NTOHS(x) PP_HTONS(x)
    #define PP_HTONL(x) ((((x) & 0xff) << 24) | \
                         (((x) & 0xff00) << 8) | \
                         (((x) & 0xff0000UL) >> 8) | \
                         (((x) & 0xff000000UL) >> 24))
    #define PP_NTOHL(x) PP_HTONL(x)

#endif /* BYTE_ORDER == BIG_ENDIAN */

#endif