#include "cpu/instr.h"
void setPF(uint32_t result)
{
    int flag = 0;
    result = result & 0x000000ff;
    while (result != 0)
    {
        if (result % 2 == 1)
        {
            flag++;
        }
        result = result / 2;
    }
    if (flag % 2 == 0)
    {
        cpu.eflags.PF = 1;
    }
    else
    {
        cpu.eflags.PF = 0;
    }
}

void setZF(uint32_t result, size_t data_size)
{
    result = result & (0xffffffff >> (32 - data_size));
    cpu.eflags.ZF = (result == 0);
}

void setSF(uint32_t result, size_t data_size)
{
    result = sign_ext(result & (0xffffffff >> (32 - data_size)), data_size);
    cpu.eflags.SF = sign(result);
}

void setOF_add(uint32_t result, uint32_t src, uint32_t dest, size_t data_size)
{
    switch (data_size)
    {
    case 8:
        result = sign_ext(result & 0xff, 8);
        src = sign_ext(src & 0xff, 8);
        dest = sign_ext(dest & 0xff, 8);
        break;
    case 16:
        result = sign_ext(result & 0xffff, 16);
        src = sign_ext(src & 0xffff, 16);
        dest = sign_ext(dest & 0xffff, 16);
        break;
    default:
        break;
    }
    if (sign(src) == sign(dest))
    {
        if (sign(src) != sign(result))
        {
            cpu.eflags.OF = 1;
        }
        else
        {
            cpu.eflags.OF = 0;
        }
    }
    else
    {
        cpu.eflags.OF = 0;
    }
}
static void instr_execute_1op()
{
    operand_read(&opr_src);
    opr_src.val += 1;
    operand_write(&opr_src);
}

make_instr_impl_1op(inc, r, v)
    make_instr_impl_1op(inc, rm, v)