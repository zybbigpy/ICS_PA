#include "cpu/instr.h"

static void instr_execute_1op() {
  operand_read(&opr_src);
  cpu.esp -= 4;
  opr_dest.type = OPR_MEM;
  opr_dest.addr = cpu.esp;
  oprr_dest.val = opr_src.val;
  operand_write(&opr_dest);
}

make_instr_impl_1op(push,r,l)
