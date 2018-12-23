#include "cpu/instr.h"
#include "device/port_io.h"

make_instr_func(in_b) {
   cpu.eax = (uint8_t) pio_read(cpu.edx & 0xffff, 1);
   return 1;
}

make_instr_func(in_v) {
    cpu.eax = pio_read(cpu.edx & 0xffff, data_size / 4);
    return 1;
}