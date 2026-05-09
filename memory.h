#ifndef MEMORY_H
#define MEMORY_H

#include <stdint.h>

extern uint8_t memory[8192];
extern uint16_t memory_read(uint16_t address);
extern void memory_write(uint16_t addr, uint16_t value);
#define MEMORY_SIZE 8195
#define DATA_START 0
#define INSTRUCTION_START 1000

#endif