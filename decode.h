#ifndef DECODE_H
#define DECODE_H
#include <stdint.h>

extern uint16_t decode_instruction_opcode(uint16_t ir);
extern uint16_t decode_instruction_address(uint16_t ir);
#endif