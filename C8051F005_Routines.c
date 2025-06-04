/*
    C8051F005_Routines: 
    this module contains routines that are commonly used for the device 
    C8051F005. 
*/
#define _C8051F005_ROUTINES_C_

/*
    includes 
*/
#include "./misc/device-files/si_toolchain.h" 
#include "./misc/device-files/c8051F000_defs.h" 
#include "on_off.h" 
#include "C8051F005_Routines.h" 

/*
    function prototypes 
*/
void vTimer2(bit status); 
void vWait_ms(unsigned int ms); 
float fADC0_temp(void); 

/*
    global variables 
*/
    long accumulator=0; 
    int count=INT_DEC; 

/*
    routines 
*/
/*
    vTimer2: 
    start/stop timer 2 (TR2). 

    parameters: status
        bit status: ON to start timer 2, OFF to stop.  
    return    : none 
*/
void vTimer2(bit status){

    if(status==ON)
        TR2=ON; 
    else 
        TR2=OFF; 

}

/* 
    vWait_ms: 
    this routine generates a delay of <ms> milliseconds. 

    parameters: ms 
        unsigned int ms: number of milliseconds of delay (0 to 65535).  
    return    : none 
*/
void vWait_ms(unsigned int ms){

    vTimer2(ON);                        // start timer 2 

    while(ms){
        TF2=0;                          // clear timer 2 flag 

        while(!TF2)                     // wait until timer 2 overflows 
            ;  

        ms--;                           // decrement ms 
    }

    vTimer2(OFF);                       // stop timer 2 

}


/*
    fADC0_temp: 
    this routine measures, samples and returns internal temperature (in 
    degrees celsius) of the device VIA ADC0. 

    parameters: none 

    return    : temp_measure 
        float temp_measure: the resulting temperature measurement.  
*/
float fADC0_temp(void){ 

    float temp_measure; 

    do{ 

        ADBUSY=1;                       // start ADC conversion 

        while(ADBUSY)
            ;                           // let conversion complete 

        // integrate & decimate 
        accumulator+=ADC0; 
        count--; 

    } while(count!=0); 

    // convert raw result to celsius 
    temp_measure=accumulator>>12; 
    temp_measure=(temp_measure/131072*5-0.776)/0.00286; 
    accumulator=0;              // reset accumulator 
    count=INT_DEC;              // reset integrate-decimate counter 

    return temp_measure; 

}