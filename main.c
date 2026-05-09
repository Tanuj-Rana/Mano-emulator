#include "memory.h"
#include "cpu.h"
#include "opcode.h"
#include "decode.h"
#include "execute.h"
#include <stdio.h>
#include <stdint.h>

int main(){
    FILE *fp = fopen("assembly.bin","rb");
    
    if(fp==NULL){
        printf("Error : file  is not found or can't be opened ! ");
        return -1;
    }

    uint8_t instructions[2];
    
    uint16_t address = 0;

    // fread() will read from assembled.bin file ,
    // it will read 2 elements of size 1 byte each and store it in memory
    while(fread(instructions,sizeof(uint8_t),2,fp)==2){
        memory[address++]=instructions[0];
        memory[address++]=instructions[1];
    }

    fclose(fp);
    CPU cpu;
    cpu.pc=INSTRUCTION_START;

    cpu.ac = 0;
    cpu.E  = 0;
    cpu.ir = 0;
    cpu.mar = 0;
    cpu.mdr = 0;
    cpu.halted =0;
    cpu.IEN = 0;


    while(cpu.halted==0){
        //fetch
        cpu.ir=memory_read(cpu.pc);
        cpu.pc+=2;

        //decode
        uint16_t opcode = decode_instruction_opcode(cpu.ir);
        cpu.mar = decode_instruction_address(cpu.ir);

        // execute 
        execute(&cpu,opcode);
    }
    
    return 0;
}


 