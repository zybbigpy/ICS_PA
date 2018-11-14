#include "nemu.h"
#include "cpu/cpu.h"
#include "memory/cache.h"
#include "device/mm_io.h"
#include <memory.h>
#include <stdio.h>

CacheLine cache[];