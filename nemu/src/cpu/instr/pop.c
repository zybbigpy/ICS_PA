#include "cpu/instr.h"

static void instr_execute_1op() {
    OPERAND help;
    help.addr = cpu.esp;
    help.data_size = data_size;
    help.type = OPR_MEM;
    help.sreg = SREG_SS;
    operand_read(&help);
    opr_src.val = help.val;
    opr_src.sreg = SREG_DS;
    operand_write(&opr_src);
    cpu.esp += data_size / 8;
}

make_instr_impl_1op(pop, r, v)

// pop all regs 

make_instr_func(popa) {
    OPERAND Eax,Ecx,Edx,Ebx,Temp,Ebp,Esi,Edi;
    
    //pop edi
    Edi.type = OPR_MEM;
    Edi.data_size = data_size;
    Edi.sreg = SREG_SS;
    Edi.addr = cpu.esp;
    operand_read(&Edi);
    cpu.edi = Edi.val;
    cpu.esp += data_size / 8;
}