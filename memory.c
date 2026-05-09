#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "memory.h"
#include "cpu.h"

uint8_t memory[8192];

uint16_t memory_read(uint16_t address){
    if(address+1>=MEMORY_SIZE){
        printf("Error : trying to access out of bound memory ! ");
        exit(1);
    }
    // joining unit of 8 bits 
    uint16_t value =(((uint16_t)memory[address]<<8 ) | (memory[address+1]));
    return value;
}

void memory_write(uint16_t addr, uint16_t value){
    if (addr+1>= MEMORY_SIZE){
        printf("Error: Memory write out of bounds\n");
        exit(1);
    }
    memory[addr]=(value>>8)&0xFF;
    memory[addr+1]=value&0xFF;
}


