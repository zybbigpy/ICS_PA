#include "cpu/instr.h"
#include "device/port_io.h"

make_instr_func(out_b) {
   pio_write(cpu.edx & 0xffff, 1, cpu.eax & 0xff);
   return 1;
}

make_instr_func(out_v) {
    if(data_size == 16) {
        pio_write(cpu.edx & 0xffff, 2, cpu.eax & 0xffff);
    }
    else if(data_size == 32) {
        pio_write(cpu.edx & 0xffff, 4, cpu.eax);
    }
    return 1;
}