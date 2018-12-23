#include "cpu/instr.h"
#include "device/port_io.h"

make_instr_func(out_b) {
   pio_write(cpu.edx & 0xffff, 1, cpu.eax);
   return 1;
}

make_instr_func(out_v) {
    if(data_size == 16) {
        cpu.eax = pio_read(cpu.edx & 0xffff, 2);
    }
    else if(data_size == 32) {
        cpu.eax = pio_read(cpu.edx & 0xffff, 4);
    }
    return 1;
}