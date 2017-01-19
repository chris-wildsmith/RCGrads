//*********************************************************************************************************************
//   SENSORBUS LIBRARY FOR MBED - HEADER FILE
//   PAUL HARRIS, DECEMBER 2014
// *********************************************************************************************************************

#ifndef SENSORBUS_H
#define SENSORBUS_H

#include "mbed.h"
#include "gpio14.h"
#include "enums_sensorbus.h"
#include "serial.h"

class sensorBus{
    public:
    
    //Constructor
    sensorBus(I2C* i2c_p);
        
    //Public methods
    int read(eSensor s);
    void enable(bool front_enable, bool front_right_enable, bool rear_right_enable, bool rear_enable, bool rear_left_enable, bool front_left_enable);
    void pbit(void);
    void readings(void);
    
    private:
    
    //F + R sensors connected
    gpio14 gpio1;
    // FL + RL sensors connected
    gpio14 gpio2;
    // FR + RR sensors connected
    gpio14 gpio3;
    
    };
    

#endif