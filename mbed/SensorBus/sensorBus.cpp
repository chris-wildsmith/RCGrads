//*********************************************************************************************************************
//   SENSORBUS LIBRARY FOR MBED - HEADER FILE
//   PAUL HARRIS, DECEMBER 2014
// *********************************************************************************************************************

#include "sensorBus.h"

//**********************************************************************************************************************
//   INITIALISATION FUNCTION
// *********************************************************************************************************************

sensorBus::sensorBus(I2C* i2c_p): gpio1(i2c_p, 0x20, "Front", "Back"), gpio2(i2c_p, 0x21, "Front-Left", "Back-Left"), gpio3(i2c_p, 0x22, "Front-Right", "Back-Right")
{
    //Enable all sensors on each GPIO14 chip by default
    gpio1.sA_enable = true;
    gpio1.sB_enable = true;
    gpio2.sA_enable = true;
    gpio2.sB_enable = true;
    gpio3.sA_enable = true;
    gpio3.sB_enable = true;

    //Set all GPIO14 chips to report distances in cm
    gpio1.set_sonar_units(cm);
    gpio2.set_sonar_units(cm);
    gpio3.set_sonar_units(cm);
    
}

void sensorBus::enable(bool front_enable, bool front_right_enable, bool rear_right_enable, bool rear_enable, bool rear_left_enable, bool front_left_enable){
    
    //Enable sensors on each GPIO14 chip depending on enable arguments
    gpio1.sA_enable = front_enable;
    gpio1.sB_enable = rear_enable;
    gpio2.sA_enable = front_left_enable;
    gpio2.sB_enable = rear_left_enable;
    gpio3.sA_enable = front_right_enable;
    gpio3.sB_enable = rear_right_enable;
    
}

int sensorBus::read(eSensor s){
    
    int temp_reading = 0;
    
    if (s == F)
    {
        if(gpio1.sA_enable)
        {
            //Take reading
            temp_reading = gpio1.read_SRF04A();
            //If reading is greater than 1200, ranging units have reverted to default and module must have reset
            if(temp_reading > 1200)
            {
                debug_error();
                debug.printf("SensorBus: GPIO14 Module 1 reset detected.  REINITIALISING MODULE...");
                debug_newline();
                
                gpio1.set_sonar_units(cm);
                return 0;
            }
            return temp_reading;
        }
        else {debug_error();debug.printf("SensorBus: Attempted read of FRONT sensor failed! - not enabled!");}
    }
    else if (s == B)
    {
        if(gpio1.sB_enable)
        {
            //Take reading
            temp_reading = gpio1.read_SRF04B();
            //If reading is greater than 1200, ranging units have reverted to default and module must have reset
            if(temp_reading > 1200)
            {
                debug_error();
                debug.printf("SensorBus: GPIO14 Module 1 reset detected.  REINITIALISING MODULE...");
                debug_newline();
                
                gpio1.set_sonar_units(cm);
                return 0;
            }
            return temp_reading;
        }
        else {debug_error();debug.printf("SensorBus: Attempted read of REAR sensor failed! - not enabled!");}
    }
    else if (s == FL)
    {
        if(gpio2.sA_enable)
        {
            //Take reading
            temp_reading = gpio2.read_SRF04A();
            //If reading is greater than 1200, ranging units have reverted to default and module must have reset
            if(temp_reading > 1200)
            {
                debug_warn();
                debug.printf("SensorBus: GPIO14 Module 2 reset detected.  REINITIALISING MODULE...");
                debug_newline();
                
                gpio2.set_sonar_units(cm);
                return 0;
            }
            return temp_reading;
        }
        else {debug_error();debug.printf("SensorBus: Attempted read of FRONT LEFT sensor failed! - not enabled!");}
    }
    else if (s == BL)
    {
        if(gpio2.sB_enable)
        {
            //Take reading
            temp_reading = gpio2.read_SRF04B();
            //If reading is greater than 1200, ranging units have reverted to default and module must have reset
            if(temp_reading > 1200)
            {
                debug_error();
                debug.printf("SensorBus: GPIO14 Module 2 reset detected.  REINITIALISING MODULE....");
                debug_newline();
                
                gpio2.set_sonar_units(cm);
                return 0;
            }
            return temp_reading;
        }
        else {debug_error();debug.printf("SensorBus: Attempted read of REAR LEFT sensor failed! - not enabled!");}
    }
    else if (s == FR)
    {
        if(gpio3.sA_enable)
        {
            //Take reading
            temp_reading = gpio3.read_SRF04A();
            //If reading is greater than 1200, ranging units have reverted to default and module must have reset
            if(temp_reading > 1200)
            {
                debug_error();
                debug.printf("SensorBus: GPIO14 Module 3 reset detected.  REINITIALISING MODULE...");
                debug_newline();
                
                gpio3.set_sonar_units(cm);
                return 0;
            }
            return temp_reading;
        }
        else {debug_error();debug.printf("SensorBus: Attempted read of FRONT RIGHT sensor failed! - not enabled!");}
    }
    else if (s == BR)
    {
        if(gpio3.sB_enable)
        {
            //Take reading
            temp_reading = gpio3.read_SRF04B();
            //If reading is greater than 1200, ranging units have reverted to default and module must have reset
            if(temp_reading > 1200)
            {
                debug_error();
                debug.printf("SensorBus: GPIO14 Module 3 reset detected.  REINITIALISING MODULE...");
                debug_newline();
                
                gpio3.set_sonar_units(cm);
                return 0;
            }
            return temp_reading;
        }
        else {debug_error();debug.printf("SensorBus: Attempted read of REAR RIGHT sensor failed! - not enabled!");}
    }

    debug_newline();
    //Return 0 if any sensor is not enabled.
    return 0;

}

//**********************************************************************************************************************
//   PBIT FUNCTION
// *********************************************************************************************************************
    
void sensorBus::pbit(void){
    
    gpio14* gpio_pt_array[3];
    gpio_pt_array[0] = &gpio1;
    gpio_pt_array[1] = &gpio2;
    gpio_pt_array[2] = &gpio3;
    

    debug_command();
    debug.printf("**** SensorBus: Running PBIT. Please wait for the results... ****");
    debug_newline();
    debug_newline();
    
    
    int i = 0;
    
    //GPIO14 modules PBIT
    
    debug.printf("GPIO14 Module Comms Results:");
    debug_newline();
    debug_newline();
    
    for (i = 0; i < 3; i++)
    {
        if(gpio_pt_array[i]->read_firmware() == 2)
        {
            debug_status();
            debug.printf("GPIO14 MODULE %d COMMS: PASS!", i+1);
            debug_newline();
        }
        else
        {
            debug_error();
            debug.printf("GPIO14 MODULE %d COMMS: FAIL! Check connections!", i+1);
            debug_newline();
        }
    
    }
    
    debug_newline();
    debug_newline();
    
    //HC-SRF04 sensors PBIT
    
    debug.printf("HC-SRF04 Sensor Results (only enabled sensors listed):");
    debug_newline();
    debug_newline();
    
    for (i = 0; i < 3; i++)
    {
        if(gpio_pt_array[i]->sA_enable)
        {    if(gpio_pt_array[i]->read_SRF04A() > 0)
            {
                debug_status();
                debug.printf("GPIO14 MODULE %d %s SENSOR: PASS!", i+1, gpio_pt_array[i]->sA);
                debug_newline();   
            }
            else
            {
                debug_error();
                debug.printf("GPIO14 MODULE %d %s SENSOR: FAIL! Check connections!", i+1, gpio_pt_array[i]->sA);
                debug_newline();
            }
        }
        
        if(gpio_pt_array[i]->sB_enable)
        {
            if(gpio_pt_array[i]->read_SRF04B() > 0)
            {
                debug_status();
                debug.printf("GPIO14 MODULE %d %s SENSOR: PASS!", i+1, gpio_pt_array[i]->sB);
                debug_newline();   
            }
            else
            {
                debug_error();
                debug.printf("GPIO14 MODULE %d %s SENSOR: FAIL! Check connections!", i+1, gpio_pt_array[i]->sB);
                debug_newline();
            }
        }
    }
    debug_newline();
}

void sensorBus::readings(void)
{
    char temp;
    
    debug_command();
    debug.printf("SensorBus: Displaying sensor readings every 1s - press spacebar to stop...");
    debug_newline();
    debug_newline();
    
    while(1)
    {
        if(debug.readable())
        {
            temp = debug.getc();
            //If spacebar pressed, return.
            if(temp == ' ')
            {
                break;    
            }
        }
        
        debug_status();
        debug.printf("F:%dcm , B:%dcm , FL:%dcm , BL:%dcm , FR:%dcm , RR:%dcm", read(F), read(B), read(FL), read(BL), read(FR), read(BR));
        debug_newline();
        
        wait(1);
    }
    
    
}