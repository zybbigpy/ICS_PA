#include "cpu/instr.h"

static void instr_execute_2op() {
  operand_read(&opr_src);
  operand_read(&opr_dest);
  //printf("opr_src-val is:  0x%x\n",opr_src.val);
  //printf("opr_dest-val is: 0x%x\n",opr_dest.val);
  alu_sub(sign_ext(opr_src.val, opr_src.data_size), \
							opr_dest.val, opr_dest.data_size);
  //printf("EIP:0x %x\n",cpu.eip);
  //printf("after cmp opr_dest-val is: 0x%x\n",opr_dest.val);

}

make_instr_impl_2op(cmp, i, rm, bv)
make_instr_impl_2op(cmp, i, rm, v)
make_instr_impl_2op(cmp, r, rm, v)
make_instr_impl_2op(cmp, r, rm, b)
make_instr_impl_2op(cmp, rm, r, v)
make_instr_impl_2op(cmp, rm, r, b)
make_instr_impl_2op(cmp, i, a, b)
make_instr_impl_2op(cmp, i, a, v)
make_instr_impl_2op(cmp, i, rm, b)