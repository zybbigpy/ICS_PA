#include "nemu.h"
#include "cpu/cpu.h"
#include "memory/cache.h"
//#include "device/mm_io.h"
#include <memory.h>
#include <stdio.h>

CacheLine cache[CACHE_SIZE_B/CACHELINE_SIZE_B];

void init_cache() {
    // set all content especially validBit zero
    memset(cache, 0, sizeof(CacheLine)*1024);
}