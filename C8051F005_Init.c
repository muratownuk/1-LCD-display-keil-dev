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
void vUART_Init(void); 

/*
    global variables 
*/
unsigned char TX_Ready; 

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
    use internal oscillator (OSCICN) at 16MHz (SYSCLK) and turn off external 
    oscillator (OSCXCN) 

    parameters: none 
    return    : none 
*/
void vOSC_Init(void){

    // XOSCMD2-0=000 (off) and XFCN2-0=000 (default) 
    OSCXCN&=~0x70;
    // MSCLKE=0, CLKSL=0 (internal), IOSCEN=1 (default) and IFCN1-0=11 16MHz 
    OSCICN|=0x03; 

}

/*
    vPort_Init: 
    Tx & Rx of UART are routed to P0.0 and P0.1, respectively
    crossbar enabled (XBARE), weak pull-ups enabled 
    P0.0 configured as push-pull output, P0.1 as open-drain (input)  

    parameters: none 
    return    : none 
 */
void vPort_Init(void){

    XBR0|=0x04;                         // UARTEN=1       
    XBR2|=0x40;                         // WEAKPUD=0 and XBARE=1 
    PRT0CF|=0x01;                       // P0.0 push-pull and P0.1 open-drain  

}

/*
    vTimer2_Init: 
    uses SYSCLK as timebase (CKCON.5)
    RCLK=TCLK=1 where timer 2 is in baud generator mode  

    parameters: none 
    return    : none 
*/
void vTimer2_Init(void){

    CKCON|=0x20;                        // T2M=1 
    T2CON|=0x30;                        // RCLK=TCLK=1 
    
    RCAP2L=0x98;                        // values from config2 tool 
    RCAP2H=0xFF; 
    
    T2=RCAP2;                           // initialize T2 value 

}

/*
    vUART_Init: 
    UART operated in mode 1 asynchronous 8-bit variable baud rate using timer 
    2 overflow; UART reception enabled 

    parameters: none 
    return    : none 
*/
void vUART_Init(void){

    // SM0-1=01 mode 1 8-bit UART, variable baud rate; REN=1 receive enable  
    SCON|=0x50; 

    ES=1;                               // enable serial port (UART) interrupt
    TX_Ready=1;                         // UART ready to transmit 

}

