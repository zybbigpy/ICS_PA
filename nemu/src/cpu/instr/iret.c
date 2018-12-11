#include "cpu/instr.h"

#define pop(reg)            \
OPERAND help;               \
help.type = OPR_MEM;        \
help.data_size = data_size; \
help.addr = cpu.esp;        \
help.sreg = SREG_SS;        \
operand_read(&help);        \
cpu.reg = help.val;         \
cpu.esp += data_size / 8;   \

make_instr_func(iret) {
    pop(eip)
    pop(cs)
    pop(eflags)
    return 0;
}