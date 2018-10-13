#include "cpu/instr.h"

make_instr_func(lea)
{
    OPERAND R;
    OPERAND M;
    R.data_size = M.data_size = data_size;
    int len = 1;
    len += modrm_r_rm(eip + 1, &R, &M);
    operand_read(&M);
    R.val = M.addr;
    operand_write(&R);
    print_asm_2("lea", "", len, &M, &R);

    return len;
}