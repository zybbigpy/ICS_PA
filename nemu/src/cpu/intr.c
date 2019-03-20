#include "cpu/intr.h"
#include "cpu/instr.h"
#include "memory/memory.h"

void raise_intr(uint8_t intr_no) {
#ifdef IA32_INTR
  // printf("int_ \n");
  // assert(0);

  // push eflags
  cpu.esp -= 4;
  vaddr_write(cpu.esp, SREG_SS, 4, cpu.eflags.val);
  // push cs
  cpu.esp -= 2;
  vaddr_write(cpu.esp, SREG_SS, 2, cpu.cs.val);
  // push eip
  cpu.esp -= 4;
  vaddr_write(cpu.esp, SREG_SS, 4, cpu.eip);

  GateDesc idt;
  // clear IF if interupt
  if (idt.type == 0xe) {
    cpu.eflags.IF = 0;
    // cpu.eflags.TF = 0;
  }

  idt.val[0] = laddr_read(cpu.idtr.base + intr_no * 8, 4);
  idt.val[1] = laddr_read(cpu.idtr.base + intr_no * 8 + 4, 4);
  cpu.eip = (idt.offset_31_16 << 16) + idt.offset_15_0;
  cpu.cs.val = idt.selector;
#endif
}

void raise_sw_intr(uint8_t intr_no) {
  // return address is the next instruction
  cpu.eip += 2;
  raise_intr(intr_no);
}
