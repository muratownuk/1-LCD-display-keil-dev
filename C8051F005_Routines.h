#ifndef _C8051F005_ROUTINES_H_ 
    #define _C8051F005_ROUTINES_H_

    /*
        defines 
    */
    #define DELAY 1000 

    #ifndef _C8051F005_ROUTINES_C_ 

        // function prototypes (for external use) 
        extern void vTimer2(bit status); 
        extern void vWait_ms(unsigned int ms); 

    #endif

#endif


