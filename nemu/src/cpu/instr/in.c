#include "cpu/instr.h"
#include "device/port_io.h"

make_instr_func(in_b) {
   cpu.eax = (uint8_t) pio_read(cpu.edx, 1);

make_instr_func(in_v) {

}