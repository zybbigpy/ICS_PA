#include "cpu/instr.h"

make_instr_func(ret_near)
{
    //pop eip
    OPERAND help;
    help.type = OPR_MEM;
    help.data_size = data_size; //??s
    help.addr = cpu.esp;
    operand_read(&help);
    cpu.eip = help.val;
    cpu.esp += data_size / 8;
    return 0; //len?=0s
}