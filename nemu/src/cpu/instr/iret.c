#include "cpu/instr.h"


make_instr_func(iret) {
    uint8_t no = instr_fetch(eip + 1, 1);
    raise_sw_intr(no);
    return 0;
}