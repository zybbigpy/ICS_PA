#include "cpu/instr.h"

static void instr_execute_1op() {
  OPERAND help;
  operand_read(&opr_src);
  cpu.esp -= opr_src.data_size/8;
  help.addr = cpu.esp ;
  help.type = OPR_MEM;
  help.val = opr_src.val;
  operand_write(&help);
}

make_instr_impl_1op(push, r, v)
