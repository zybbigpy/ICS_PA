#include "cpu/intr.h"
#include "cpu/instr.h"
#include "memory/memory.h"


void raise_intr(uint8_t intr_no) {
#ifdef IA32_INTR
	//printf("Please implement raise_intr()");
	//assert(0);
	laddr_t idt_entry = cpu.idtr.base + intr_no *sizeof(GateDesc);
	GateDesc idt;
	idt.val[0] = laddr_read(idt_entry, 4);
	idt.val[1] = laddr_read(idt_entry + 4, 4);

#endif
}

void raise_sw_intr(uint8_t intr_no) {
	// return address is the next instruction
	cpu.eip += 2;
	raise_intr(intr_no);
}
