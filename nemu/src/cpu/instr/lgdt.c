#include "cpu/instr.h"

make_instr_func(lgdt) {
    // one byte for opcode and six bytes for src
    int len  = 7;
    switch(data_size) {
        case 16:
        case 32:
        default: pritf("error! in lgdt\n.");
    }
}
