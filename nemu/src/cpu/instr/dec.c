#include "cpu/instr.h"

static void instr_execute_1op()
{
    operand_read(&opr_src);
    // reserve the CF flag
    uint32_t CF_R = cpu.eflags.CF;
    opr_src.val = alu_sub(1, opr_src.val, opr_src.data_size);
    cpu.eflags.CF = CF_R;
    operand_write(&opr_src);
}

make_instr_impl_1op(dec, r, v)
make_instr_impl_1op(dec, rm, v)