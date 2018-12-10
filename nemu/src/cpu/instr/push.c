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
  OPERAND Eax,Ecx,Edx,Ebx,Temp,Ebp,Esi,Edi;
  uint32_t temp = cpu.esp;

  //push eax
  cpu.esp -= data_size / 8;
  Eax.data_size = data_size;
  Eax.addr = cpu.esp;
  Eax.sreg = SREG_SS;
  Eax.val = cpu.eax;
  operand_write(&Eax);
  
  //push ecx
  cpu.esp -= data_size / 8;
  Ecx.data_size = data_size;
  Ecx.addr = cpu.esp;
  Ecx.sreg = SREG_SS;
  Ecx.val = cpu.ecx;
  operand_write(&Ecx);

  //push edx
  cpu.esp -= data_size / 8;
  Edx.data_size = data_size;
  Edx.addr = cpu.esp;
  Edx.sreg = SREG_SS;
  Edx.val = cpu.edx;
  operand_write(&Edx);

  //push ebx
  cpu.esp -= data_size / 8;
  Ebx.data_size = data_size;
  Ebx.addr = cpu.esp;
  Ebx.sreg = SREG_SS;
  Ebx.val = cpu.ebx;
  operand_write(&Ebx);

  //push temp
  cpu.esp -= data_size / 8;
  Temp.data_size = data_size;
  Temp.addr = cpu.esp;
  Temp.sreg = SREG_SS;
  Temp.val = temp;
  operand_write(&Temp);

  //push ebp
  cpu.esp -= data_size / 8;
  Ebp.data_size = data_size;
  Ebp.addr = cpu.esp;
  Ebp.sreg = SREG_SS;
  Ebp.val = cpu.ebp;
  operand_write(&Ebp);

  //push esi
  cpu.esp -= data_size / 8;
  Esi.data_size = data_size;
  Esi.addr = cpu.esp;
  Esi.sreg = SREG_SS;
  Esi.val = cpu.esi;
  operand_write(&Esi);
  
  //push edi
  cpu.esp -= data_size / 8;
  Edi.data_size = data_size;
  Edi.addr = cpu.esp;
  Edi.sreg = SREG_SS;
  Edi.val = cpu.edi;
  operand_write(&Edi);  
}
