#include "cpu/instr.h"
#include "device/port_io.h"

make_instr_func(out_b) {
   cpu.eax = (uint8_t) pio_read(cpu.edx, 1);
   return 1;
}

make_instr_func(out_v) {
    cpu.eax = pio_read(cpu.edx, 4);
    return 1;
}