#include "nemu.h"
#include "cpu/cpu.h"
#include "memory/cache.h"
#include "memory/memory.h"
//#include "device/mm_io.h"
#include <memory.h>
#include <stdio.h>

CacheLine L1_dcache[CACHE_SIZE_B / CACHELINE_SIZE_B];

void init_cache() {
    // set all content especially validBit zero
    memset(L1_dcache, 0, sizeof(CacheLine)*1024);
}

/*
** Below are some help funcs.
*/

// get the flag of paddr
uint32_t get_paddr_flag(paddr_t paddr) {
    // first 23 bits of paddr
    uint32_t flag = paddr >> 9;
    return flag;
}

// get the set nuber of paddr
uint32_t get_paddr_setNo(paddr_t paddr) {
    // 3 bits in the middle of paddr
    uint32_t setNo = (paddr >> 6) & (0x7);
    return setNo;
}

// get the block address of the paddr
uint32_t get_paddr_blockAddr(paddr_t paddr) {
    // last 6 bits of paddr
    uint32_t blockAddr = paddr & 0x3f;
    return blockAddr;
}

/*
** Above are some help funcs.
*/

uint32_t cache_read(paddr_t paddr, size_t len, CacheLine* cache) {
    uint32_t flag = 0;
    uint32_t setNo = 0;
    uint32_t blockAddr = 0;
    uint32_t lineNoBgn = 0;
    uint32_t ret = 0;
    uint32_t lineNoHit = 0;
    bool hitStatus = false;
 
    flag = get_paddr_flag(paddr);
    setNo = get_paddr_setNo(paddr);
    blockAddr = get_paddr_blockAddr(paddr);
    lineNoBgn = setNo * 8;
    for(size_t i = 0; i < 8; ++i) {
        if(cache[lineNoBgn + i].bitAndFlag.flag == flag) {
            if(cache[lineNoBgn + i].bitAndFlag.validBit == 1) {
                hitStatus = true;
                lineNoHit = lineNoBgn + i;
            }
        }
    }

    if(hitStatus) {
        memcpy(&ret, &cache[lineNoHit].content[blockAddr], len);
        return ret;
    }
    else {
        memcpy(&ret, hw_mem + paddr, len);
        memcpy(cache[lineNoHit].content, hw_mem + paddr, len);
	    return ret;
    }

}

// write cache
void cache_write(paddr_t paddr, size_t len, uint32_t data, CacheLine* cache) {

}