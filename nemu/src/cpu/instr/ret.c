#include "cpu/instr.h"

make_instr_func(ret_near)
{
    //pop eip
    OPERAND help;
    help.type = OPR_MEM;
    help.data_size = 32; //??s
    help.addr = cpu.esp;
    operand_read(&help);
    cpu.eip = help.val;
    cpu.esp += 4;
    return 1 + data_size / 8; //len?=0s
}