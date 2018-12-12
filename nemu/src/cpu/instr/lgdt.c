#include "cpu/instr.h"

make_instr_func(lgdt) { 
	// datasize = 32
	int len = 1;
	OPERAND data;
	data.type = OPR_IMM;
	data.data_size = 16;
	len += modrm_rm(eip + 1, &data);
	operand_read(&data);
	cpu.gdtr.limit = data.val;
	data.data_size = 32;
	data.addr += 2;
	operand_read(&data);
	print_asm_1("lgdt", "", 2, &data);
	cpu.gdtr.base = data.val;
	return len;
}