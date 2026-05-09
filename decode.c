#include "cpu.h"
#include "memory.h"



uint16_t decode_instruction_opcode(uint16_t ir){
    // for decoding instruction
   uint16_t opcode = ir;
   uint16_t opcode1 = ir>>12;
   if((ir & 0x8000) ==0){ //check ith bit
        if((opcode1 & 0x7)!=7){
            return ( opcode1 & 0x7);
        }
        else{ //for register refrence 
            //for i/o refrence ith-> 0 and rest opcode bits 111
            for(int i=0;i<16;++i){
                if( (opcode & (1<<i) ) != 0){
                    return 70+i;
                }
            }
        }
    }
   else{ 
        if((opcode1 & 0x7)!=7){
            return ( opcode1 & 0x7);
        }
        else{ //for i/o refrence ith-> 1 and rest opcode bits 111
            for(int i=0;i<6;++i){
                if((opcode & (1<<i)) != 0){
                return 170 + i;
                }
            }
        }
    }

    return -1;
}


uint16_t decode_instruction_address(uint16_t ir){

    if(((ir >> 15) & 1) ==0){
        return 0xFFFF;   // no address rerurned
    }
    else{
        return ir & 0x0FFF;
    }
}