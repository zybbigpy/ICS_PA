#include "cpu/instr.h"

make_instr_func(lidt) {
    // one byte for opcode and six bytes for src
    int len  = 7;
    uint16_t src_15 = instr_fetch(eip + 5, 2);
    uint32_t src_16_47 = instr_fetch(eip + 1, 4);
    switch(data_size) {
        case 16:
            cpu.idtr.limit = src_15;
            cpu.idtr.base = src_16_47 & 0x00FFFFFF;
            break;
        case 32:
            cpu.idtr.limit = src_15;
            cpu.idtr.base = src_16_47;
            break;
        default: 
            printf("error! in lidt\n.");
            break;
    }
    return len;
}