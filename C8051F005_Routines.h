#ifndef _C8051F005_ROUTINES_H_ 
    #define _C8051F005_ROUTINES_H_

    /*
        defines 
    */
    #define     DELAY       1000 
    #define     INT_DEC     4096 

    #ifndef _C8051F005_ROUTINES_C_ 

        // function prototypes (for external use)  
        extern void vWait_ms(unsigned int ms); 
        extern float fADC0_temp(void); 
        
    #endif

#endif


