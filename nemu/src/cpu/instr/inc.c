#include "cpu/instr.h"


static void instr_execute_1op()
{
    operand_read(&opr_src);
    opr_dest.val = alu_add(1,opr_dest.val,opr_dest.data_size);


    operand_write(&opr_src);
}

make_instr_impl_1op(inc, r, v)
make_instr_impl_1op(inc, rm, v)