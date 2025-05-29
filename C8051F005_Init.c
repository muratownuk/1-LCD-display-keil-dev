/*
    C8051F005_Init: 
    this module contains all the initialization/configuration routines for     
    this project (device C8051F005). 
*/
#define _C8051F005_INIT_C_

/*
    includes 
*/
#include "./misc/device-files/si_toolchain.h" 
#include "./misc/device-files/c8051F000_defs.h" 
#include "on_off.h" 
#include "C8051F005_Init.h" 

/*
    function prototypes 
*/
void vWatchdog(bit status); 
void vOSC_Init(void); 
void vPort_Init(void); 
void vTimer2_Init(void); 

/*
    routines 
*/
/*
    vWatchdog: 
    turn watchdog timer ON or OFF. 

    parameters: status 
        bit status: 
        pass ON(1) or OFF(0) to keep watchdog ON or OFF, respectively. 
    return    : none      
*/
void vWatchdog(bit status){

    if(status==ON)
        return;                         // watchdog is enabled on power-on 
    else{
        WDTCN=0xDE;                     // disable watchdog timer 
        WDTCN=0xAD;
    }

}

/*
    vOSC_Init: 
    use internal oscillator (OSCICN) at 2MHz (default-SYSCLK) and turn off 
    external oscillator (OSCXCN) 

    parameters: none 
    return    : none 
*/
void vOSC_Init(void){

    // XOSCMD2-0=000 (off) and XFCN2-0=000 (default) 
    OSCXCN&=~0x70;

}

/*
    vPort_Init: 
    crossbar enabled (XBARE), weak pull-ups enabled.
    P0.0-7 configured as open-drain (default). The data (P0) to/from LCD is 
    controlled through lcd module. 
    P1.0-2 configured as push-pull output, P1.3-7 configured as open-drain. 
    P1.7 as pushbutton (open-drain) on C8051F005. 


    parameters: none 
    return    : none 
 */
void vPort_Init(void){

    XBR2|=0x40;                         // WEAKPUD=0 and XBARE=1
    // P1.0-2 as push-pull and P1.3-7 as open-drain  
    PRT1CF|=0x07; 

}

/*
    vTimer2_Init: 
    uses SYSCLK/12 as timebase (T2M-CKCON.5) 
    C/T2=0 (T2CON.2) timer 2 configured as timer (clock defined by T2M)  

    parameters: none 
    return    : none 
*/
void vTimer2_Init(void){

    CKCON&=~0x20;                       // T2M=0 

    RCAP2=-(SYSCLK/12/1000);            // timer 2 overflow rate 1KHz
    T2=RCAP2;                           // initialize T2 value 

    ET2=0;                              // disable T2 interrupts if enabled

}
