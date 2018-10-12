#include "cpu/instr.h"

static void instr_execute_2op() {
  operand_read(&opr_src);
  operand_read(&opr_dest);
  printf("opr_src-val is:  0x%x\n",opr_src.val);
  printf("opr_dest-val is: 0x%x\n",opr_dest.val);
  opr_dest.val = alu_adc(opr_src.val,opr_dest.val,opr_dest.data_size);
  printf("after sub opr_dest-val is: 0x%x\n",opr_dest.val);
  operand_write(&opr_dest);
}

make_instr_impl_2op(adc, i, rm, bv)