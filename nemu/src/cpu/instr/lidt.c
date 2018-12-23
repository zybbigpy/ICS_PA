#include "cpu/instr.h"

// make_instr_func(lidt) {
//     // one byte for opcode and six bytes for src
//     int len  = 7;
//     uint16_t src_15 = instr_fetch(eip + 5, 2);
//     uint32_t src_16_47 = instr_fetch(eip + 1, 4);
//     switch(data_size) {
//         case 16:
//             cpu.idtr.limit = src_15;
//             cpu.idtr.base = src_16_47 & 0x00FFFFFF;
//             break;
//         case 32:
//             cpu.idtr.limit = src_15;
//             cpu.idtr.base = src_16_47;
//             break;
//         default:
//             printf("error! in lidt\n.");
//             break;
//     }
//     return len;
// }

// static void instr_execute_1op() {
// 	// printf("lidt..\n");
// 	laddr_t mem_addr = opr_src.val;
// 	// printf("mem_addr = 0x%x\n", mem_addr);
// 	cpu.idtr.limit = laddr_read(mem_addr, 2) & 0xffff;
// 	cpu.idtr.base = laddr_read(mem_addr + 2, 4) & 0xffffffff;
// 	if (data_size == 16)
// 		cpu.idtr.base &= 0x00ffffff;
// 	// printf("idtr: limit = 0x%x, base = 0x%x\n", cpu.idtr.limit, cpu.idtr.base);

// }

// make_instr_impl_1op(lidt, rm, v)

make_instr_func(lidt) { 
	int len = 1;
	OPERAND rm1;
	rm1.type = OPR_IMM;
	rm1.data_size = 16;
	len += modrm_rm(eip + 1, &rm1);
	operand_read(&rm1);
	cpu.idtr.limit = rm1.val;

	OPERAND rm2;
	rm2.data_size = 32;
	rm2.addr = rm1.addr + 2;
	rm2.sreg = rm1.sreg;
	rm2.type = OPR_IMM;
	operand_read(&rm2);
	cpu.idtr.base = rm2.val;
	// print_asm_1("lidt", "", 2, &data);
	return len;
}