#include "cpu/instr.h"
make_instr_func(call_near) {
    //push eip
    OPERAND help;
    cpu.esp -= data_size / 8;                   //maybe datasize=16
    help.type = OPR_MEM;
    help.sreg = SREG_SS;
    help.data_size = data_size;
    help.val = cpu.eip + 1 + data_size / 8;     // eip + len(opcode) + len(data)
    help.addr = cpu.esp;
    operand_write(&help);                       //write will do eip(ip) -> stack

    //eip - rel32(or rel 16) realize like jmp_near
    OPERAND rel;
    rel.type = OPR_IMM;
    //rel.sreg = SREG_CS;//is it necessary??
    //printf("datasize is %d\n",data_size);
    rel.data_size = data_size;
    rel.addr = eip + 1;
    rel.sreg = SREG_CS;

    operand_read(&rel);
    //printf("call_near val is 0x%x\n", rel.val);
    int offset = sign_ext(rel.val, data_size);
    //printf("offset is %d\n", offset);
    cpu.eip += offset;
    //printf("eip is 0x%x\n", cpu.eip);

    return 1 + data_size / 8;
}

make_instr_func(call_near_indirect) {
    // //push eip
    // OPERAND help;
    // cpu.esp -= data_size / 8;               //maybe 2
    // help.type = OPR_MEM;
    // help.data_size = data_size;
    // help.val = cpu.eip + 1 + data_size / 8;
    // help.addr = cpu.esp;  
    // help.sreg = SREG_SS; 
    // operand_write(&help);                   //write will do eip(ip) -> stack

    // //realize like jmp_near_indirect
    // OPERAND rm;
    // rm.data_size = data_size;
    // rm.sreg = SREG_CS;
    // int len = 1;
    // len += modrm_rm(eip + 1, &rm);          // write addr and type for opr_rm
    // operand_read(&rm);
    // cpu.eip = rm.val;
    int len = 1;
    OPERAND rm;
    cpu.esp -= 4;
    len += modrm_rm(eip + 1, &rm);
    rm.data_size = data_size;
    operand_read(&rm);
    vaddr_write(cpu.esp, SREG_SS, 4, eip + len);
    cpu.eip = rm.val;
    return 0;
}