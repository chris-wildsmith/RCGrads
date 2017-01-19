#ifndef GPIO14_MESSAGES_H
#define GPIO14_MESSAGES_H


//Define read registers
const char REVISION[] = {0x00};            // Firmware revision register
const char RESULT[] = {0x01};                // Result high byte register
//const char RESULT[] = {0x02};              // Result low-byte register - don't bother with this as can read two consectutive bytes - slave will auto-increment to 2nd result register on 2nd read (provided repeated start between reads and no stop sequence)
const char AD_CONTROL_READ[] = {0x03};     // Analogue-digital control status register
const char PORT_A_READ[] = {0x04};         // Port A digital GPIO status register
const char PORT_B_READ[] = {0x05};         // Port B digital GPIO status register
const char PWM_READ[] = {0x06};            // Read PWM value from pin RB3 register

//Define write registers
const char CMD[] = {0x00};                 // Command register
const char MASK_A[] = {0x01};              // GPIO direction mask port A register
const char MASK_B[] = {0x02};              // GPIO direction mask port B register
const char AD_CONTROL_WRITE[] = {0x03};    // Analogue-digital control register
const char PORT_A_WRITE[] = {0x04};        // Port A digital GPIO write register
const char PORT_B_WRITE[] = {0x05};        // Port B digital GPIO write register
const char PWM_WRITE[] = {0x06};           // Set PWM value for pin RB3 register
const char ADDR_CHANGE[] = {0x07};         // Change I2C address register

//Define commands

    //Define General Commands
    const char NO_OP[] = {0x00};            // No operation
    const char PULLB_ON[] = {0x01};         // PORTB pull-up resistors active
    const char PULLB_OFF[] = {0x02};        // PORT B pull-ups resistors disabled
    const char GET_AD0[] = {0x03};          // Get Analogue Channel 0 (RA0)
    const char GET_AD1[] = {0x04};          // Get Analogue Channel 1 (RA1)
    const char GET_AD2[] = {0x05};          // Get Analogue Channel 2 (RA2)
    const char GET_AD3[] = {0x06};          // Get Analogue Channel 3 (RA3)
    const char GET_AD4[] = {0x07};          // Get Analogue Channel 4 (RA4)
    const char GET_S4A[] = {0x08};          // Get HC-SRF04 range value - Trig on RB0, Echo on RB2
    const char GET_S4B[] = {0x09};          // Get HC-SRF04 range value - Trig on RB6, Echo on RB7
    const char GET_S5A[] = {0x0A};          // Get HC-SRF05 range value - Trig + Echo on RB6
    const char GET_S5B[] = {0x0B};          // Get HC-SRF05 range value - Trig + Echo on RB7
    const char SET_US[] = {0x0C};           // sonar ranging in uS
    const char SET_CM[] = {0x0D};           // sonar ranging in cm
    const char SET_IN[] = {0x0E};           // sonar ranging in inches
    
    //Define digital GPIO Commands (Set, Clear and Toggle)
    
    //Bit Set commands
        const char SET_RA0[] = {0x10};          
        const char SET_RA1[] = {0x11};
        const char SET_RA2[] = {0x12};
        const char SET_RA3[] = {0x13};
        const char SET_RA4[] = {0x14};
        //const char SET_RA5[] = {0x15};          // not available on GPIO14 (Input only)
        const char SET_RA6[] = {0x16};
        const char SET_RA7[] = {0x17};
        const char SET_RB0[] = {0x18};
        //const char SET_RB1[] = {0x19};          // not available on GPIO14 (SDA)
        const char SET_RB2[] = {0x1a};
        const char SET_RB3[] = {0x1b};
        //const char SET_RB4[] = {0x1c};          // not available on GPIO14 (SCL)
        const char SET_RB5[] = {0x1d};
        const char SET_RB6[] = {0x1e};
        const char SET_RB7[] = {0x1f};
        
    //Bit Clear Commands
        const char CLR_RA0[] = {0x20};
        const char CLR_RA1[] = {0x21};
        const char CLR_RA2[] = {0x22};
        const char CLR_RA3[] = {0x23};
        const char CLR_RA4[] = {0x24};
        //const char CLR_RA5[] = {0x25};         // not available on GPIO14 (Input only)
        const char CLR_RA6[] = {0x26};
        const char CLR_RA7[] = {0x27};
        const char CLR_RB0[] = {0x28};
        //const char CLR_RB1[] = {0x29};         // not available on GPIO14 (SDA)
        const char CLR_RB2[] = {0x2a};
        const char CLR_RB3[] = {0x2b};
        //const char CLR_RB4[] = {0x2c};         // not available on GPIO14 (SCL)
        const char CLR_RB5[] = {0x2d};
        const char CLR_RB6[] = {0x2e};
        const char CLR_RB7[] = {0x2f};
        
    //Bit Toggle Commands
        const char TOG_RA0[] = {0x30};
        const char TOG_RA1[] = {0x31};
        const char TOG_RA2[] = {0x32};
        const char TOG_RA3[] = {0x33};
        const char TOG_RA4[] = {0x34};
        //const char TOG_RA5[] = {0x35         // not available on GPIO14 (Input only)
        const char TOG_RA6[] = {0x36};
        const char TOG_RA7[] = {0x37};
        const char TOG_RB0[] = {0x38};
        //const char TOG_RB1[] = {0x39};         // not available on GPIO14 (SDA)
        const char TOG_RB2[] = {0x3a};
        const char TOG_RB3[] = {0x3b};
        //const char TOG_RB4[] = {0x3c};         // not available on GPIO14 (SCL)
        const char TOG_RB5[] = {0x3d};
        const char TOG_RB6[] = {0x3e};
        const char TOG_RB7[] = {0x3f};

#endif