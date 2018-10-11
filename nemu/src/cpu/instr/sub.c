#include "cpu/instr.h"

static void instr_execute_2op() {
  operand_read(&opr_src);
  operand_read(&opr_dest);
  opr_dest.val = alu_sub(opr_src.val,opr_src.val,opr_src.data_size);
  operand_write(&opr_dest);
}

make_instr_impl_2op(sub, i, rm, b)
