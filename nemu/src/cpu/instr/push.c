#include "cpu/instr.h"

static void instr_execute_1op() {
  OPERAND help;
  opr_src.sreg = SREG_DS;
  operand_read(&opr_src);
  //  esp - 4 or esp - 2 (no esp - 1)
  //  use oprsrc.datasize is wrong for the case of imm8 
  cpu.esp -= data_size / 8;
  help.addr = cpu.esp;
  help.sreg = SREG_SS;
  help.data_size = data_size;
  help.type = OPR_MEM;
  //for imm 8 (IA32-book)
  help.val = sign_ext(opr_src.val, data_size);
  operand_write(&help);
}

make_instr_impl_1op(push, r, v)
make_instr_impl_1op(push, rm, v)
make_instr_impl_1op(push, i, b)
make_instr_impl_1op(push, i, v)

// push all regs

make_instr_func(pusha) {
  OPERAND Eax,Ecx,Eex,Ebx,Temp,Ebp,Esi,Edi;
  uint32_t temp = cpu.esp;

  //push eax
  cpu.esp -= data_size / 8;
  Eax.data_size = data_size;
  Eax.addr = cpu.esp;
  Eax.sreg = SREG_SS;
  Eax.val = cpu.eax;
  operand_write(&Eax);
}
