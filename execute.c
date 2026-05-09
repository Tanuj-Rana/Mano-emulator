#include "execute.h"
#include "opcode.h"
#include "cpu.h"
#include "memory.h"
#include <stdio.h>
#include <stdlib.h>

void execute(CPU *cpu, uint16_t opcode) {

    switch(opcode) {

        case ADD:{
            if(cpu->mar!=0xFFFF) cpu->mdr=memory_read(cpu->mar*2);
            else { //to handle immediate operand
                uint16_t im12 = cpu->ir & 0x0FFF;
                if(im12 & 0x0800){
                    cpu->mdr = (int16_t)(im12 | 0xF000);
                }
                else{
                    cpu->mdr = (int16_t)im12;
                }
            }
            uint16_t oldac=cpu->ac;

            uint32_t result=(uint32_t)cpu->mdr + (uint32_t)cpu->ac;

            cpu->ac=(uint16_t)result;

            //flags
            cpu->E=(result >> 16) & 1;
            cpu->Z=(cpu->ac == 0);
            cpu->V=((~(cpu->mdr^oldac)& (oldac^cpu->ac))>>15)&1;
            cpu->N=(cpu->ac >> 15) & 1;

            break;
        }
        case AND:{

            if(cpu->mar!=0xFFFF) cpu->mdr=memory_read(cpu->mar*2);
            else { //to handle immediate operand
                uint16_t imm12 = cpu->ir & 0x0FFF;
                if(imm12 & 0x0800){
                    cpu->mdr = (int16_t)(imm12 | 0xF000);
                }
                else{
                    cpu->mdr = (int16_t)imm12;
                }
            }

            cpu->ac=cpu->mdr & cpu->ac;

            //flags
            cpu->Z=(cpu->ac == 0);
            cpu->N=(cpu->ac >> 15) & 1;

            break;
        }
        case LDA:{

            if(cpu->mar!=0xFFFF) cpu->mdr=memory_read(cpu->mar*2);
            else cpu->mdr=(cpu->ir & 0x0FFF); //to handle immediate operand

            cpu->ac=cpu->mdr;

            //flags
            cpu->Z=(cpu->ac == 0);
            cpu->N=(cpu->ac >> 15) & 1;

            break;
        }
        case STA:{

            if(cpu->mar == 0xFFFF) {
                printf("Error: STA cannot use immediate !\n");
                exit(1);
            }

            memory_write(cpu->mar*2,cpu->ac);

            //not alu operation so, no flags !

            break;
        }
        case BUN:{

            if(cpu->mar==0xFFFF){
                printf("Error: BUN cannot use immediate !\n");
                exit(1);
            }
            cpu->pc=cpu->mar*2;

            break;
        }
        case BSA:{

            if(cpu->mar == 0xFFFF) {
                printf("Error: BSA cannot use immediate !\n");
                exit(1);
            }
            memory_write(cpu->mar*2,cpu->pc);
            cpu->pc= (cpu->mar *2 ) +  2;

            break;
        }
        case ISZ:{

            if(cpu->mar == 0xFFFF) {
                printf("Error: ISZ cannot use immediate !\n");
                exit(1);
            }
            cpu->mdr=memory_read(cpu->mar*2);
            cpu->mdr++;
            memory_write(cpu->mar*2,cpu->mdr);
            if(cpu->mdr == 0) cpu->pc+=2;
            break;
        }
        case CLA:{

            //Register_reference_instructions starts from here

            cpu->ac=0;

            cpu->N=0;
            cpu->Z=1;

            break;
        }
        case CLE:{

            cpu->E=0;

            break;
        }
        case CMA:{

            cpu->ac=~(cpu->ac);

            cpu->Z=(cpu->ac == 0);
            cpu->N=(cpu->ac >> 15) & 1;

            break;
        }
        case CME:{

            cpu->E=!(cpu->E);

            break;
        }
        case CIR:{

            uint8_t oldE=cpu->E;
            cpu->E=cpu->ac & 1; //new E gets LSB
            cpu->ac=cpu->ac>>1; //shift right
            cpu->ac|=(oldE<<15); //old E enters MSB

            break;
        }

        case CIL:{

            uint8_t oldE=cpu->E;

            cpu->E=(cpu->ac>>15) & 1; //new E gets old MSB

            cpu->ac=((cpu->ac<<1)|oldE); //shift left and old E enters LSB

            break;
        }
        case INC:{

            cpu->ac++;

            cpu->Z=(cpu->ac ==0);
            cpu->N=(cpu->ac >>15) & 1;

            break;
        }
        case SPA:{

            if((((cpu->ac)>>15) & 1) ==0) cpu->pc+=2;

            break;
        }
        case SNA:{

            if((((cpu->ac)>>15) & 1) ==1) cpu->pc+=2;

            break;
        }
        case SZA:{

            if((cpu->ac) ==0) cpu->pc+=2;

            break;
        }
        case SZE:{

            if(cpu->E == 0){
                cpu->pc+=2;
            }

            break;
        }
        case HLT:{
            cpu->halted=1;
            break;
        }
        case INP:{
            char ch;
            scanf(" %c",&ch);
            cpu->INPR=ch;
            cpu->FGI=1;

            cpu->ac=cpu->INPR;
            cpu->FGI=0;

            cpu->Z=(cpu->ac == 0);
            cpu->N=0;

            break;
        }
        case OUT:{
            cpu->OUTR=cpu->ac & 0xFF;
            printf("%c",cpu->OUTR);
            cpu->FGO=1;
            break;
        }
        case SKI:{
            if(cpu->FGI == 1)
                cpu->pc+=2;
            break;
        }
        case SKO:{
            if(cpu->FGO == 1)
                cpu->pc+=2;

            break;
        }
        case ION:{
            cpu->IEN=1;
            break;
        }
        case IOF:{
            cpu->IEN=0;
            break;
        }
        default:{
            printf("Error: Invalid opcode!\n");
            cpu->halted=1;
            exit(1);
        }
    }
}