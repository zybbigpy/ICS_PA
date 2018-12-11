#include "cpu/instr.h"
#include "cpu/intr.h"

make_instr_func(int_) {
    uint8_t no = instr_fetch(eip + 1, 1);
    raise_sw_intr(no);
    return 0;
}