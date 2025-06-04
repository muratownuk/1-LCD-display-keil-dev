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

/*
    defines 
*/
#define     PRESSED     1 

/*
    function prototypes 
*/
void vDisplay_temp(float temperature, bit cf);

/*
    sbit definitions 
*/
SI_SBIT(button, P1, 7); 

void main(void){
    
    SI_BIT(celsius_fahrenheit);         // flag to swap between C/F 
    
    celsius_fahrenheit=0;               // 0=celsius; 1=fahrenheit 

    vWatchdog(OFF);                     // disable watchdog timer 
    vOSC_Init();                        // initialize device oscillator (2MHz) 
    vPort_Init();                       // initialize ports 0 and 1 
    vTimer2_Init();                     // initialize timer 2 for delay 
    vADC0_Init();                       // initialize temp. sensor and ADC0 
    LcdInit();                          // initialize the LCD display 

    while(1){ 

        if(button==PRESSED){ 

            celsius_fahrenheit=~celsius_fahrenheit; 

            // simple debounce
            while(button==PRESSED)
                ; 
            vWait_ms(DELAY);  

        } 

        vDisplay_temp(fADC0_temp(), celsius_fahrenheit); 

    }

}

/*
    routines: 
*/
/*
    vDisplay_temp: 
    this routine displays the temperature in celsius (default) or fahrenheit (
    doing the necessary conversion). 

    parameters: temperature, cf 
        float temperature: the temperature to be displayed (default=celsius).

        bit   cf         : celsius-fahrenheit flag for display method.  

    return    : none 
*/ 
void vDisplay_temp(float temperature, bit cf){
    
    static float fTemperature; 
    static char sTemperature[6];        // temperature string (char array) 
    sTemperature[0]='\0';               // null terminate the string 

    if(!cf){                            // display in celsius 

        fTemperature=temperature;       // no need for conversion 

        sprintf(sTemperature, "%.1f", fTemperature); 
        
        LcdWriteString("Temp: "); 
        LcdWriteString(&sTemperature); 
        LcdWriteChar(' '); 
        LcdWriteChar(0xDF);             // degrees symbol 
        LcdWriteChar('C');              // celsius 

        LcdClear(); 

    } 
    else{                               // display in fahrenheit 

        // convert from celsius to fahrenheit 
        fTemperature=(temperature*(9/5.0))+32;  

        sprintf(sTemperature, "%.1f", fTemperature); 
        
        LcdWriteString("Temp: "); 
        LcdWriteString(&sTemperature); 
        LcdWriteChar(' '); 
        LcdWriteChar(0xDF);             // degrees symbol 
        LcdWriteChar('F');              // fahrenheit  

        LcdClear(); 

    } 

}


