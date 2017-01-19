//*********************************************************************************************************************
//   GPIO14 LIBRARY FOR MBED - SOURCE FILE
//   PAUL HARRIS, SEPTEMBER 2014
// *********************************************************************************************************************

#include "gpio14.h"

//gpio14 class constructor
gpio14::gpio14(I2C* i2c_p, int I2C_addr, const char* sensorA, const char* sensorB)
{
    i2c_pt = i2c_p;
    addr = I2C_addr << 1; //need to left shift by one as I2C API uses 7-bit addresses, 8th bit is read/write
    sA = sensorA;
    sB = sensorB;
    
    //Set sensors to enabled by default
    sA_enable = true;
    sB_enable = true;
    
};

//**********************************************************************************************************************
//   PRIMATIVE READ/WRITE OPERATIONS
// *********************************************************************************************************************

char gpio14::i2c_read_byte(const char* reg){
    temp[0] = 5;  //Initialise to 5 not 0 as a failure will also return zero
    int ack = 0; //Acknowledge from read/write operations
    
    ack = i2c_pt->write(addr, reg, 1, true);//Send a start followed by write address, followed by register (data), do not send stop sequence
    
    //If unsuccessful write
    if(ack != 0){
        debug_error();
        debug.printf("I2C bus write fail!");
        debug_newline();
        return 0;
    }
 
    ack = i2c_pt->read(addr, temp, 1);  //Send start (repeated start from read), followed by read address, then read 1 byte and send stop sequence
    
    //If successful read
    if(ack == 0){
    return temp[0];
    }
    //If unsuccessful read
    else{
        debug_error();
        debug.printf("I2C bus read fail!");
        debug_newline();
        return 0;
    }
};

int gpio14::i2c_read_2bytes(const char* reg){
    temp[0] = 0;
    temp[1] = 0;
    int ack = 0; //Acknowledge from read/write operations
    
    ack = i2c_pt->write(addr, reg, 1, true);//Send a start followed by write address, followed by register (data), do not send stop sequence
    
    //If unsuccessful write
    if(ack != 0){
        debug_error();
        debug.printf("I2C bus write fail!");
        debug_newline();
        return 0;
    }
    
    ack = i2c_pt->read(addr, temp, 2);  //Send start (repeated start from read), followed by read address, then read 2 bytes and send stop sequence
    
    //If successful read
    if(ack == 0){
    return int(((temp[0]<<8) | temp[1])); //Shift temp[0] left 8 bits (MSByte) and OR (bit-wise) with temp[1] (LSByte) to create 16 bit int result 
    }
    //If unsuccessful read
    else{
        debug_error();
        debug.printf("I2C bus read fail!");
        debug_newline();
        return 0;
    }
    
    
    
}

void gpio14::reg_write(const char* reg, char data){
    char reg_data[2];
    reg_data[0] = *reg;
    reg_data[1] = data;
    
    i2c_pt->write(addr, reg_data, 2);  
};


void gpio14::cmd_write(const char* cmd){ //Write a command to a specific register
    char cmd_data[2];
    cmd_data[0] = CMD[0];
    cmd_data[1] = *cmd;
    i2c_pt->write(addr, cmd_data, 2); 
};



//**********************************************************************************************************************
//   REGISTER READ FUNCTIONS
// *********************************************************************************************************************
char gpio14::read_firmware(void){
    return i2c_read_byte(REVISION);
};


int gpio14::read_result(void){
    return i2c_read_2bytes(RESULT);
};

char gpio14::read_AD_control(void){
    return i2c_read_byte(AD_CONTROL_READ);
};
    
    
char gpio14::read_portA_status(void){
   return i2c_read_byte(PORT_A_READ);
};

char gpio14::read_portB_status(void){
    return i2c_read_byte(PORT_B_READ);
};

char gpio14::read_PWM_value(void){
    return i2c_read_byte(PWM_READ);
};


//**********************************************************************************************************************
//   REGISTER WRITE FUNCTIONS
// *********************************************************************************************************************
void gpio14::set_portA_mask(char mask){
    reg_write(MASK_A, mask);
};

void gpio14::set_portB_mask(char mask){
    reg_write(MASK_B, mask);
};

void gpio14::set_AD_control(char control){
    reg_write(AD_CONTROL_WRITE, control);
};

void gpio14::set_portA_values(char values){
    reg_write(PORT_A_WRITE, values);
};
void gpio14::set_portB_values(char values){
    reg_write(PORT_B_WRITE, values);    
};

void gpio14::set_PWM_value(char value){
    reg_write(PWM_WRITE, value);
};

void gpio14::set_I2C_addr(char addr_new){
    char sequence[4] = {};
    
    sequence[0] = 0xA0;
    sequence[1] = 0xAA;
    sequence[2] = 0xA5;
    sequence[3] = addr_new;
    
    short i = 0;
    
    //Sequence must be written in four seperate transactions

    reg_write(ADDR_CHANGE, sequence[i++]); //Write sequence[0]. Post-increment seq_ptr to point to sequence[1]
    reg_write(ADDR_CHANGE, sequence[i++]); //Write sequence[1]. Post-increment seq_ptr to point to sequence[2]
    reg_write(ADDR_CHANGE, sequence[i++]); //Write sequence[2]. Post-increment seq_ptr to point to sequence[3]
    reg_write(ADDR_CHANGE, sequence[i]);  // Write sequence[3]. 
};


//**********************************************************************************************************************
//   GPIO14 COMMAND REGISTER FUNCTIONS
// *********************************************************************************************************************

void gpio14::set_pullupsB(eStatus status){
    
    if (status == ON)
    {
        cmd_write(PULLB_ON);    
    }
    
    else //status == OFF
    {
        cmd_write(PULLB_OFF);    
    }
       
};


int gpio14::read_AD(ePins pin){
    
    int result;
    
    if(pin == RA0)
    {
        cmd_write(GET_AD0);
    }
  
    else if(pin == RA1)
    {
        cmd_write(GET_AD1);
    }
    else if(pin == RA2)
    {
        cmd_write(GET_AD2);
    }
  
    else if(pin == RA3)
    {
        cmd_write(GET_AD3);
    }
    
    else  //Pin == RA4
    {
        cmd_write(GET_AD4);
    }
    
    wait(0.5); //Wait for conversion
    
    //Read AD_control set up to determine justification of AD result in the result register(s)
        char ad_control = read_AD_control();
    
        //Extract bit 7 (justification bit)
        ad_control &= 0x80;
        //Check bit 7 - set = right justified, unset = left justified
        
        if(ad_control == 0x80){
            return read_result(); //If right justified, return result
        }
        else {
            result = read_result();
            result = result >> 6; //If left justified, remove left justification and return
            return result;
        }
  
};


int gpio14::read_SRF04A(void){
    
    wait_ms(10); //Wait to prevent consecutive calls to function providing unstable readings.  10ms allows sensor time to settle before next reading.
    cmd_write(GET_S4A);
    wait_ms(70); //Documentation says wait at least 60ms before result will be ready. GPIO14 will not respond to I2C commands until after finished ranging.
    return read_result();
};

int gpio14::read_SRF04B(void){
    
    wait_ms(10); //Wait to prevent consecutive calls to function providing unstable readings.  10ms allows sensor time to settle before next reading.
    cmd_write(GET_S4B);
    wait_ms(70); //Documentation says wait at least 60ms before result will be ready. GPIO14 will not respond to I2C commands until after finished ranging.
    return read_result();
};
    
int gpio14::read_SRF05A(void){
    wait_ms(10); //Wait to prevent consecutive calls to function providing unstable readings.  10ms allows sensor time to settle before next reading.
    cmd_write(GET_S5A);
    wait_ms(70); //Documentation says wait at least 60ms before result will be ready. GPIO14 will not respond to I2C commands until after finished ranging.
    return read_result();
};


int gpio14::read_SRF05B(void){
    wait_ms(10); //Wait to prevent consecutive calls to function providing unstable readings.  10ms allows sensor time to settle before next reading.
    cmd_write(GET_S5B);
    wait_ms(70); //Documentation says wait at least 60ms before result will be ready. GPIO14 will not respond to I2C commands until after finished ranging.
    return read_result();
};

void gpio14::set_sonar_units(eUnits units){
    
    if(units == us)
    {
        cmd_write(SET_US);
    }
    
    else if(units == cm)
    {
        cmd_write(SET_CM);
    }
    
    else //Inches
    {
        cmd_write(SET_IN);
    }
    
};




void gpio14::set_portA(ePins pin, eBit_value value){
    
    if(pin == RA0)
    {
        if(value == SET)
        {
            cmd_write(SET_RA0);   
        }
        
        else if(value == CLEAR)
        {
            cmd_write(CLR_RA0);
        } 
        
        else
        {
            cmd_write(TOG_RA0);
        }  
    }
    
    else if(pin == RA1)
    {
        if(value == SET)
        {
            cmd_write(SET_RA1);   
        }
        
        else if(value == CLEAR)
        {
            cmd_write(CLR_RA1);
        } 
        
        else
        {
            cmd_write(TOG_RA1);
        }
    }
    
    else if(pin == RA2)
    {
        if(value == SET)
        {
            cmd_write(SET_RA2);   
        }
        
        else if(value == CLEAR)
        {
            cmd_write(CLR_RA2);
        } 
        
        else
        {
            cmd_write(TOG_RA2);
        }
    }
    
    else if(pin == RA3)
    {
        if(value == SET)
        {
            cmd_write(SET_RA3);   
        }
        
        else if(value == CLEAR)
        {
            cmd_write(CLR_RA3);
        } 
        
        else
        {
            cmd_write(TOG_RA3);
        }
    }
    
    else if(pin == RA4)
    {
        if(value == SET)
        {
            cmd_write(SET_RA4);   
        }
        
        else if(value == CLEAR)
        {
            cmd_write(CLR_RA4);
        } 
        
        else
        {
            cmd_write(TOG_RA4);
        }
    }
    
    else if(pin == RA6)
    {
        if(value == SET)
        {
            cmd_write(SET_RA6);   
        }
        
        else if(value == CLEAR)
        {
            cmd_write(CLR_RA6);
        } 
        
        else
        {
            cmd_write(TOG_RA6);
        }
    }
    
    else //RA7
    {
        if(value == SET)
        {
            cmd_write(SET_RA7);   
        }
        
        else if(value == CLEAR)
        {
            cmd_write(CLR_RA7);
        } 
        
        else
        {
            cmd_write(TOG_RA7);
        }
        
    }
    
};


void gpio14::set_portB(ePins pin, eBit_value value)
{
    
    if(pin == RB0)
    {
        if(value == SET)
        {
            cmd_write(SET_RB0);   
        }
        
        else if(value == CLEAR)
        {
            cmd_write(CLR_RB0);
        } 
        
        else
        {
            cmd_write(TOG_RB0);
        }  
    }
    
    else if(pin == RB2)
    {
        if(value == SET)
        {
            cmd_write(SET_RB2);   
        }
        
        else if(value == CLEAR)
        {
            cmd_write(CLR_RB2);
        } 
        
        else
        {
            cmd_write(TOG_RB2);
        }
    }
    
    else if(pin == RB3)
    {
        if(value == SET)
        {
            cmd_write(SET_RB3);   
        }
        
        else if(value == CLEAR)
        {
            cmd_write(CLR_RB3);
        } 
        
        else
        {
            cmd_write(TOG_RB3);
        }
    }
    
    else if(pin == RB5)
    {
        if(value == SET)
        {
            cmd_write(SET_RB5);   
        }
        
        else if(value == CLEAR)
        {
            cmd_write(CLR_RB5);
        } 
        
        else
        {
            cmd_write(TOG_RB5);
        }
    }
    
    else if(pin == RB6)
    {
        if(value == SET)
        {
            cmd_write(SET_RB6);   
        }
        
        else if(value == CLEAR)
        {
            cmd_write(CLR_RB6);
        } 
        
        else
        {
            cmd_write(TOG_RB6);
        }
    }
    
    else //RB7
    {
        if(value == SET)
        {
            cmd_write(SET_RB7);   
        }
        
        else if(value == CLEAR)
        {
            cmd_write(CLR_RB7);
        } 
        
        else
        {
            cmd_write(TOG_RB7);
        }
        
    }

}
