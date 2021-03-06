#include "cpu/instr.h"

make_instr_func(jmp_near)
{
    //rel 8 or 16
    OPERAND rel;
    rel.type = OPR_IMM;
    rel.sreg = SREG_CS;
    rel.data_size = data_size;
    rel.addr = eip + 1;

    operand_read(&rel);
    //printf("jmp_near val is 0x%x\n",rel.val);
    int offset = sign_ext(rel.val, data_size);
    // thank Ting Xu from CS'17 for finding this bug
    print_asm_1("jmp", "", 1 + data_size / 8, &rel);
    //printf("offset is %d\n",offset);
    cpu.eip += offset;
    //printf("eip is 0x%x\n",cpu.eip);

    return 1 + data_size / 8;
}

make_instr_func(jmp_short)
{
    //rel8
    OPERAND rel;
    rel.type = OPR_IMM;
    rel.sreg = SREG_CS;
    rel.data_size = 8;
    rel.addr = eip + 1;

    operand_read(&rel);
    //printf("jmp_near val is 0x%x\n",rel.val);
    int offset = sign_ext(rel.val, 8);
    print_asm_1("jmp", "", 2, &rel);
    //printf("offset is %d\n",offset);
    cpu.eip += offset;
    //printf("eip is 0x%x\n",cpu.eip);

    return 1 + 8 / 8;
}

make_instr_func(jmp_near_indirect)
{
    OPERAND rm;
    rm.data_size = data_size;
    rm.sreg = SREG_CS;
    int len = 1;
    // write addr and type for opr_rm
    len += modrm_rm(eip + 1, &rm);

    operand_read(&rm);
    cpu.eip = rm.val;

    return 0;
}

make_instr_func(jmp_far_imm)
{
    int len = 3 + data_size / 8;
    uint32_t ptr_15 = 0;
    uint32_t ptr_16_32 = 0;
    uint32_t ptr_16_47 = 0;
    if (cpu.cr0.pe == 0)
    { // real mode
        switch (data_size)
        {
        case 16:
            ptr_15 = instr_fetch(eip + 1, 2);
            ptr_16_32 = instr_fetch(eip + 3, 2);
            cpu.eip = ptr_16_32 & 0x0000FFFF;
            cpu.segReg[SREG_CS].val = ptr_15;
            load_sreg(SREG_CS);
            break;
        case 32:
            ptr_15 = instr_fetch(eip + 1, 2);
            ptr_16_47 = instr_fetch(eip + 3, 4);
            cpu.eip = ptr_16_47;
            cpu.segReg[SREG_CS].val = ptr_15;
            load_sreg(SREG_CS);
            break;
        default:
            break;
        }
    }
    return len;
}