#include "cpu/instr.h"

make_instr_func(jmp_near) {
        OPERAND rel;
        rel.type = OPR_IMM;
	rel.sreg = SREG_CS;
        rel.data_size = data_size;
        rel.addr = eip + 1;

        operand_read(&rel);
        printf("jmp_near val is 0x%x/n",rel.val);
	int offset = sign_ext(rel.val, data_size);
	print_asm_1("jmp", "", 2, &rel);
        printf("offset is %d/n",offset);
	cpu.eip += offset;
        printf("eip is 0x%x\n",cpu.eip);

        return 1 + data_size / 8;
}

