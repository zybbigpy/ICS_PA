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

static void instr_execute_1op() {
	// printf("lidt..\n");
	laddr_t mem_addr = opr_src.val;
	// printf("mem_addr = 0x%x\n", mem_addr);
	cpu.idtr.limit = laddr_read(mem_addr, 2) & 0xffff;
	cpu.idtr.base = laddr_read(mem_addr + 2, 4) & 0xffffffff;
	if (data_size == 16)
		cpu.idtr.base &= 0x00ffffff;
	// printf("idtr: limit = 0x%x, base = 0x%x\n", cpu.idtr.limit, cpu.idtr.base);

}

make_instr_impl_1op(lidt, rm, v)