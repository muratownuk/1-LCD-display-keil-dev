/*
    lcd_display: 
    this is the main module where the program starts. the C8051F005 oscillator 
    frequency is default (2MHz). 
*/ 
/*
    includes 
*/
#include "./misc/device-files/si_toolchain.h" 
#include "./misc/device-files/c8051F000_defs.h" 
#include "on_off.h" 
#include "C8051F005_Init.h" 
#include "C8051F005_Routines.h" 
#include "lcd.h" 


void main(void){

    
    vWatchdog(OFF);                     // disable watchdog timer 
    vOSC_Init();                        // initialize device oscillator (2MHz) 
    vPort_Init();                       // initialize ports 0 and 1 
    vTimer2_Init();                     // initialize timer 2 for delay 
    vADC0_Init();                       // initialize temp. sensor and ADC0 
    LcdInit();                          // initialize the LCD display 

    while(1){

        // forever loop write code here... 

    }

}

