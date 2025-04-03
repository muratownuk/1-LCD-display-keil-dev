#ifndef _C8051F005_INIT_H_ 
    #define _C8051F005_INIT_H_ 

    /*
        defines 
    */
    #define SYSCLK  16000000            // chip operating frequency 

    #ifndef _C8051F005_INIT_C_ 

        // function prototypes (for external use) 
        extern void vWatchdog(bit status); 
        extern void vOSC_Init(void); 
        extern void vPort_Init(void); 
        extern void vTimer2_Init(void); 
        extern void vUART_Init(void); 

        // global variables (for external use) 
        extern unsigned char TX_Ready; 

    #endif

#endif

