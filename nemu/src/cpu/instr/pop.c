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

    //pop esi
    Esi.type = OPR_MEM;
    Esi.data_size = data_size;
    Esi.sreg = SREG_SS;
    Esi.addr = cpu.esp;
    operand_read(&Edi);
    cpu.esi = Esi.val;
    cpu.esp += data_size / 8;

    //pop ebp
    Ebp.type = OPR_MEM;
    Ebp.data_size = data_size;
    Ebp.sreg = SREG_SS;
    Ebp.addr = cpu.esp;
    operand_read(&Edi);
    cpu.esi = Ebp.val;
    cpu.esp += data_size / 8;

    //pop temp and throw away
    cpu.esp += data_size / 8;

    //pop ebx
    Ebx.type = OPR_MEM;
    Ebx.data_size = data_size;
    Ebx.sreg = SREG_SS;
    Ebx.addr = cpu.esp;
    operand_read(&Edi);
    cpu.esi = Ebx.val;
    cpu.esp += data_size / 8;



}