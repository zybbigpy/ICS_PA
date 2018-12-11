#include "cpu/instr.h"

#define pop(reg)            \
OPERAND help;               \
help.type = OPR_MEM;        \
help.data_size = data_size; \
help.addr = cpu.esp;        \
help.sreg = SREG_SS;        \

make_instr_func(iret) {
    uint8_t no = instr_fetch(eip + 1, 1);
    raise_sw_intr(no);
    return 0;
}