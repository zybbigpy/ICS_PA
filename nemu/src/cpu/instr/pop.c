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

#define pop(opr, reg)           \
opr.type = OPR_MEM;             \
opr.data_size = data_size;      \
opr.sreg = SREG_SS;             \
opr.addr = cpu.esp;             \
operand_read(&opr);             \
cpu.reg = opr.val;              \
cpu.esp += data_size / 8;       \

make_instr_func(popa) {
    OPERAND Eax,Ecx,Edx,Ebx,Ebp,Esi,Edi;
    
    //pop edi
    pop(Edi, edi)
    // Edi.type = OPR_MEM;
    // Edi.data_size = data_size;
    // Edi.sreg = SREG_SS;
    // Edi.addr = cpu.esp;
    // operand_read(&Edi);
    // cpu.edi = Edi.val;
    // cpu.esp += data_size / 8;

    //pop esi
    pop(Esi, esi)
    // Esi.type = OPR_MEM;
    // Esi.data_size = data_size;
    // Esi.sreg = SREG_SS;
    // Esi.addr = cpu.esp;
    // operand_read(&Esi);
    // cpu.esi = Esi.val;
    // cpu.esp += data_size / 8;

    //pop ebp
    pop(Ebp, ebp)
    // Ebp.type = OPR_MEM;
    // Ebp.data_size = data_size;
    // Ebp.sreg = SREG_SS;
    // Ebp.addr = cpu.esp;
    // operand_read(&Ebp);
    // cpu.ebp = Ebp.val;
    // cpu.esp += data_size / 8;

    //pop temp and throw away
    cpu.esp += data_size / 8;

    //pop ebx
    pop(Ebx, ebx)
    // Ebx.type = OPR_MEM;
    // Ebx.data_size = data_size;
    // Ebx.sreg = SREG_SS;
    // Ebx.addr = cpu.esp;
    // operand_read(&Ebx);
    // cpu.ebx = Ebx.val;
    // cpu.esp += data_size / 8;

    //pop edx
    Edx.type = OPR_MEM;
    Edx.data_size = data_size;
    Edx.sreg = SREG_SS;
    Edx.addr = cpu.esp;
    operand_read(&Edx);
    cpu.edx = Edx.val;
    cpu.esp += data_size / 8;

    //pop ecx
    Ecx.type = OPR_MEM;
    Ecx.data_size = data_size;
    Ecx.sreg = SREG_SS;
    Ecx.addr = cpu.esp;
    operand_read(&Ecx);
    cpu.ecx = Ecx.val;
    cpu.esp += data_size / 8;  

    //pop eax
    Eax.type = OPR_MEM;
    Eax.data_size = data_size;
    Eax.sreg = SREG_SS;
    Eax.addr = cpu.esp;
    operand_read(&Eax);
    cpu.eax = Eax.val;
    cpu.esp += data_size / 8; 

    return 1;
}