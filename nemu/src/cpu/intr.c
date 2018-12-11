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
		union{
		GateDesc Gatedesc;
		uint32_t val[2];
	} GD;
	
	//push 
	cpu.esp-=4;
	vaddr_write(cpu.esp,SREG_SS,4,cpu.eflags.val);
	//printf("esp\n");
	cpu.esp-=2;
	vaddr_write(cpu.esp,SREG_SS,2,cpu.cs.val);
	cpu.esp-=4;
	vaddr_write(cpu.esp,SREG_SS,4,cpu.eip);
	//set flag
	cpu.eflags.IF=0;
	cpu.eflags.TF=0;

	//jmp
	GateDesc idt;
	idt.val[0]=laddr_read(cpu.idtr.base+intr_no*8,4);
	idt.val[1]=laddr_read(cpu.idtr.base+intr_no*8+4,4);
	cpu.eip=idt.offset_15_0+(idt.offset_31_16<<16);
	//cpu.CS.val=GD.Gatedesc.type;
	//load_sreg(SREG_CS);
	//printf("IDTR is %x\n",cpu.IDTR.base);
	
	return;

#endif
}

void raise_sw_intr(uint8_t intr_no) {
	// return address is the next instruction
	cpu.eip += 2;
	raise_intr(intr_no);
}
