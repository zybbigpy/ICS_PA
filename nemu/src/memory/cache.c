#include "nemu.h"
#include "cpu/cpu.h"
#include "memory/cache.h"
//#include "device/mm_io.h"
#include <memory.h>
#include <stdio.h>

CacheLine L1_dcache[CACHE_SIZE_B/CACHELINE_SIZE_B];

void init_cache() {
    // set all content especially validBit zero
    memset(L1_dcache, 0, sizeof(CacheLine)*1024);
}

/*
** Below are some help funcs.
*/

// get the flag of paddr
uint32_t get_paddr_flag(paddr_t paddr) {

}

// get the set nuber of paddr
uint32_t get_paddr_setNo(paddr_t paddr) {

}

//get the block address of the paddr
uint32_t get_paddr_blockAddr(paddr_t paddr) {

}

uint32_t cache_read(paddr_t paddr, size_t len, CacheLine* cache) {

}

/*
** Above are some help funcs.
*/


// write cache
void cache_write(paddr_t paddr, size_t len, uint32_t data, CacheLine* cache) {

}