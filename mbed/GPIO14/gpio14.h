//*********************************************************************************************************************
//   GPIO14 LIBRARY FOR MBED - HEADER FILE
//   PAUL HARRIS, SEPTEMBER 2014
// *********************************************************************************************************************

#ifndef GPIO14_H
#define GPIO14_H

#include "mbed.h"
#include "gpio14_messages.h"
#include "gpio14_enums.h"
#include "serial.h"

class gpio14{
    public:
    
    //Constructor
    gpio14(I2C* i2c_p, int I2C_addr, const char* sensorA, const char* sensorB);
    
    //Public variables
    int addr; // I2C address of gpio14 chip
    
    bool sA_enable, sB_enable;
    
    const char* sA;
    const char* sB;
    
    //gpio14 public methods
    
    void init(void);
    
    //Register methods
    char read_firmware(void);
    int read_result(void);
    char read_AD_control(void);
    char read_portA_status(void);
    char read_portB_status(void);
    char read_PWM_value(void);
    
    void set_portA_mask(char mask);
    void set_portB_mask(char mask);
    void set_AD_control(char control);
    void set_portA_values(char values);
    void set_portB_values(char values);
    void set_PWM_value(char value);
    void set_I2C_addr(char addr_new);
    
    //Command methods
    void set_pullupsB(eStatus status);
    int read_AD(ePins pin);
    int read_SRF04A(void);
    int read_SRF04B(void);
    int read_SRF05A(void);
    int read_SRF05B(void);
    void set_sonar_units(eUnits units);
    
    void set_portA(ePins pin, eBit_value value);
    void set_portB(ePins pin, eBit_value value);
    
 
    private:
    
    I2C* i2c_pt; //Pointer to I2C bus object to use
    
    char temp[2];  //Two byte array to hold read results from gpio14 I2C read
    
    //I2C byte read functions
    char i2c_read_byte(const char* reg);
    int i2c_read_2bytes(const char* reg);
    
    //I2C GPIO14 Specific write functions
    void reg_write(const char* reg, char data);
    void cmd_write(const char* cmd);
    
    
    };
 
#endif
