#ifndef CPU_H
#define CPU_H
#include <stdint.h>

 typedef struct 
{
    int16_t ac;
    uint16_t pc; 
    int16_t ir; 

    int16_t mdr; 
    
    uint16_t mar; 

    uint16_t r[8]; 

    uint8_t Z;   // for Zero
    uint8_t N;   // for Negative
    uint8_t E;   // for Carry
    uint8_t V;   // for Overflow

    uint8_t halted;
    
    uint8_t FGI;
    uint8_t FGO;
    uint8_t INPR;
    uint8_t OUTR;
    uint8_t IEN;
    
}CPU;

#endif