#include "cpu/instr.h"
make_instr_func(call_near)
{
    //push eip
    OPERAND help;
    cpu.esp -= 4;//maybe 2??
    help.type = OPR_MEM;
    help.data_size = 32;
    help.val = cpu.eip;
    help.addr = cpu.esp;
    operand_write(&help);

    //eip - rel32
    OPERAND rel;
    rel.type = OPR_IMM;
    rel.sreg = SREG_CS;
    printf("datasize is %d\n",data_size);
    rel.data_size = data_size;
    rel.addr = eip + 1;

    operand_read(&rel);
    printf("call_near val is 0x%x\n", rel.val);
    int offset = sign_ext(rel.val, data_size);
    printf("offset is %d\n", offset);
    cpu.eip += offset;
    printf("eip is 0x%x\n", cpu.eip);

    return 1 + data_size / 8;
}