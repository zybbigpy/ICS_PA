#include "cpu/instr.h"

static void instr_execute_2op() {
  operand_read(&opr_src);
  operand_read(&opr_dest);
  //printf("opr_src-val is:  0x%x\n",opr_src.val);
  //printf("opr_dest-val is: 0x%x\n",opr_dest.val);
  opr_dest.val = alu_sub(sign_ext(opr_src.val, opr_src.data_size), opr_dest.val, opr_dest.data_size);
  //printf("after sub opr_dest-val is: 0x%x\n",opr_dest.val);
  operand_write(&opr_dest);
}

make_instr_impl_2op(sub, i, rm, bv)
make_instr_impl_2op(sub, i, rm, v)
make_instr_impl_2op(sub, r, rm, v)
make_instr_impl_2op(sub, r, rm, b)
make_instr_impl_2op(sub, rm, r, v)
make_instr_impl_2op(sub, rm, r, b)
make_instr_impl_2op(sub, i, a, b)
make_instr_impl_2op(sub, i, a, v)
make_instr_impl_2op(sub, i, rm, b)