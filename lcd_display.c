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
#include <STDIO.H> 

void main(void){

    float fTemperature;                 // temperature value 
    char caTemperature[6];              // char temperature array 
    caTemperature[0]='\0';              // null terminate the character array 

    vWatchdog(OFF);                     // disable watchdog timer 
    vOSC_Init();                        // initialize device oscillator (2MHz) 
    vPort_Init();                       // initialize ports 0 and 1 
    vTimer2_Init();                     // initialize timer 2 for delay 
    vADC0_Init();                       // initialize temp. sensor and ADC0 
    LcdInit();                          // initialize the LCD display 

    while(1){

        fTemperature=fADC0_temp(); 

        sprintf(caTemperature, "%.1f", fTemperature);
        
        LcdWriteString("Temp: "); 
        LcdWriteString(&caTemperature); 
        LcdWriteChar(' '); 
        LcdWriteChar(0xDF);             // degrees symbol 
        LcdWriteChar('C');              // celsius 

        LcdClear(); 

    }

}



