#include "cpu/instr.h"

static void instr_execute_1op()
{
  OPERAND help;
  operand_read(&opr_src);
  //esp-4 or esp-2
  cpu.esp -= opr_src.data_size / 8;
  help.addr = cpu.esp;
  help.data_size = opr_src.data_size;
  help.type = OPR_MEM;
  //for imm 8(IA32-book)
  help.val = sign_ext(opr_src.val, data_size);
  operand_write(&help);
}

make_instr_impl_1op(push, r, v)
make_instr_impl_1op(push, rm, v)
make_instr_impl_1op(push, i, b)
