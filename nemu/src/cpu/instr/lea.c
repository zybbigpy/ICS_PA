#include "cpu/instr.h"

make_instr_func(lea)
{
	OPERAND r;
	OPERAND rm;

	int len =1;
	len+=modrm_r_rm(eip+1,&r,&rm);
	r.val =rm.addr;
	operand_write(&r);
	return len;
}