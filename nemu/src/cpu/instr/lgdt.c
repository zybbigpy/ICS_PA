#include "cpu/instr.h"

make_instr_func(lgdt) { 
	// datasize = 32
	int len = 1;
	OPERAND rm1;
	rm1.type = OPR_IMM;
	rm1.data_size = 16;
	len += modrm_rm(eip + 1, &rm1);
	operand_read(&rm1);
	cpu.gdtr.limit = rm1.val;

	OPERAND rm2;
	rm2.data_size = 32;
	rm2.addr = rm1.addr + 2;
	rm2.sreg = rm1.sreg;
	rm2.type = OPR_IMM;
	operand_read(&rm2);
	cpu.gdtr.base = rm2.val;
	// print_asm_1("lgdt", "", 2, &data);
	return len;
}