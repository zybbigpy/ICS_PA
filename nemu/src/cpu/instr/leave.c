#include "cpu/instr.h"

make_instr_func(leave)
{
    cpu.esp = cpu.ebp;
    OPERAND help;
    //pop ebp(old ebp value in stack)
    help.addr = cpu.esp;
    help.data_size = data_size;
    help.type = OPR_MEM;
    operand_read(&help);
    cpu.ebp = help.val;
    cpu.esp += data_size / 8;
    return 1;
}