#include "cpu/instr.h"

make_instr_func(ret_near) {
    //pop eip
    OPERAND help;
    help.type = OPR_MEM;
    help.data_size = data_size; //??s
    help.addr = cpu.esp;
    help.sreg = SREG_SS;
    operand_read(&help);
    cpu.eip = help.val;
    cpu.esp += data_size / 8;
    return 0; //len?=0s
}

make_instr_func(ret_near_imm16) {
    //pop eip
    OPERAND help;
    help.type = OPR_MEM;
    help.data_size = data_size; //??s
    help.addr = cpu.esp;
    help.sreg = SREG_SS;
    operand_read(&help);
    cpu.eip = help.val;
    cpu.esp += data_size / 8;
    //esp + imm
    OPERAND imm;
    imm.type = OPR_IMM;
    imm.addr = eip + 1;
    imm.data_size = 16;
    operand_read(&imm);
    cpu.esp += imm.val;
    return 0; //len?=0s
}