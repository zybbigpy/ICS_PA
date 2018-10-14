#include "cpu/instr.h"
static void instr_execute_2op() {
  operand_read(&opr_src);
  operand_read(&opr_dest);
  opr_dest.val = alu_and(opr_dest.val,opr_src.val,data_size);
  //printf("after and opr_dest-val is: 0x%x\n",opr_dest.val);
  operand_write(&opr_dest);
}

make_instr_impl_2op(test, r, rm, b)
make_instr_impl_2op(test, r, rm, v)
make_instr_impl_2op(test, i, a, b)
make_instr_impl_2op(test, i, a, v)
make_instr_impl_2op(test, i, rm, b)
make_instr_impl_2op(test, i, rm, v)