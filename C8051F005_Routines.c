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
void vGlobalInterrupts(bit status); 
void vTimer2(bit status); 

/*
    routines 
*/
/*
    vGlobalInterrupts: 
    enables/disables global interrupts (EA). 

    parameters: status 
        bit status: ON to enable , OFF to disable. 
    return    : none 
*/
void vGlobalInterrupts(bit status){

    if(status==ON)
        EA=ON; 
    else 
        EA=OFF; 

}

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


