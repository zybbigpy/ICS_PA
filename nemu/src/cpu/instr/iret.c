#include "cpu/instr.h"

#define pop(reg, name)            \
OPERAND name;               \
name.type = OPR_MEM;        \
name.data_size = data_size; \
name.addr = cpu.esp;        \
name.sreg = SREG_SS;        \
operand_read(&name);        \
cpu.reg = name.val;         \
cpu.esp += data_size / 8;   \

make_instr_func(iret) {
    pop(eip, help0)

    // pop cs
    OPERAND help;              
    help.type = OPR_MEM;       
    help.data_size = 16;   
    help.addr = cpu.esp;       
    help.sreg = SREG_SS;       
    operand_read(&help);       
    cpu.cs.val = help.val;         
    cpu.esp += 2;  

    pop(eflags.val, help2)
    return 0;
}