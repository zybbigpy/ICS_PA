#include "cpu/instr.h"

make_instr_func(leave) {
    // ebp -> esp
    cpu.esp = cpu.ebp;
    OPERAND help;
    //pop ebp(old ebp value in stack)
    help.addr = cpu.esp;
    help.data_size = data_size;
    help.type = OPR_MEM;
    help.sreg = SREG_CS;
    operand_read(&help);
    cpu.ebp = help.val;
    cpu.esp += data_size / 8;
    return 1;
}