#include "cpu/instr.h"

make_instr_func(ret_near){
    //pop eip
    OPERAND help;
    cpu.esp -= 4;//maybe 2??
    help.type = OPR_MEM;
    help.data_size = 32;
    help.val = cpu.eip;
    help.addr = cpu.esp;
    operand_write(&help);

}