#include "cpu/instr.h"

static void instr_execute_1op()
{
    OPERAND help;
    help.addr = cpu.esp;
    help.data_size = opr_src.data_size;
    help.type = OPR_MEM;
    operand_read(&help);
    opr_src.val = help.val;
    operand_write(&opr_src);
    cpu.esp += opr_src.data_size / 8;
}

make_instr_impl_1op(pop, r, v)