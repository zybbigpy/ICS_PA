#include "cpu/intr.h"
#include "cpu/instr.h"
#include "memory/memory.h"

#define push(reg, size, help)    \
OPERAND help;		       \
cpu.esp -= size / 8;   	   \
help.data_size = size;     \
help.addr = cpu.esp;       \
help.sreg = SREG_SS;       \
help.val = cpu.reg;        \
help.type = OPR_MEM;	   \
operand_write(&help);      \

void raise_intr(uint8_t intr_no) {
#ifdef IA32_INTR
	//printf("Please implement raise_intr()");
	//assert(0);
	push(eflags.val, data_size, help1)
	push(cs.val, data_size, help2)
	push(eip, data_size, help3)

	//cpu.eflags.IF = 0;
	//cpu.eflags.TF = 0;

	laddr_t idt_entry = cpu.idtr.base + intr_no *sizeof(GateDesc);
	GateDesc idt;
	idt.val[0] = laddr_read(idt_entry, 4);
	idt.val[1] = laddr_read(idt_entry + 4, 4);

	assert(idt.present == 1);
	if(idt.type == 0xe) {
		cpu.eflags.IF = 0;
	}
	cpu.eip = (idt.offset_31_16 << 16) + idt.offset_15_0;
	cpu.cs.val = idt.selector;
	load_sreg(SREG_CS);

#endif
}

void raise_sw_intr(uint8_t intr_no) {
	// return address is the next instruction
	cpu.eip += 2;
	raise_intr(intr_no);
}
