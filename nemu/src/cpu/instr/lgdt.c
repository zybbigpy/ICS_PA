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
	
	data.data_size = 32;
	data.addr += 2;
	operand_read(&data);
	cpu.gdtr.base = data.val;
	// print_asm_1("lgdt", "", 2, &data);
	return len;
}