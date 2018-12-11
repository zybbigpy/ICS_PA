#include "cpu/instr.h"

// make_instr_func(lgdt) {
//     // one byte for opcode and six bytes for src
//     int len  = 7;
//     uint16_t src_15 = instr_fetch(eip + 5, 2);
//     uint32_t src_16_47 = instr_fetch(eip + 1, 4);
//     switch(data_size) {
//         case 16:
//             cpu.gdtr.limit = src_15;
//             cpu.gdtr.base = src_16_47 & 0x00FFFFFF;
//             break;
//         case 32:
//             cpu.gdtr.limit = src_15;
//             cpu.gdtr.base = src_16_47;
//             break;
//         default: 
//             printf("error! in lgdt\n.");
//             break;
//     }
//     return len;
// }

// static void instr_execute_1op() {
// 	// printf("lidt..\n");
// 	laddr_t mem_addr = opr_src.val;
// 	// printf("mem_addr = 0x%x\n", mem_addr);
// 	cpu.gdtr.limit = laddr_read(mem_addr, 2) & 0xffff;
// 	cpu.gdtr.base = laddr_read(mem_addr + 2, 4) & 0xffffffff;
// 	if (data_size == 16)
// 		cpu.gdtr.base &= 0x00ffffff;
// 	// printf("idtr: limit = 0x%x, base = 0x%x\n", cpu.idtr.limit, cpu.idtr.base);

// }

// make_instr_impl_1op(lgdt, rm, v)


make_instr_func(lgdt) {//Consider datasize==32 only
		int len=1;
        OPERAND data;
        data.type = OPR_IMM;
        data.data_size = 16;
		len += modrm_rm(eip + 1, &data);
        operand_read(&data);
		cpu.gdtr.limit=data.val;
		//printf("addr is %x\n",data.addr);
        data.data_size = 32;
		data.addr+=2;
        operand_read(&data);
		print_asm_1("lgdt", "", 2, &data);
		cpu.gdtr.base=data.val;
		//printf("GDTR is %x,%x\n",cpu.GDTR.base,cpu.GDTR.limit);
		return len;
}
