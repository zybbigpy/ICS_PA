#include "memory/cache.h"
#include "cpu/cpu.h"
#include "memory/memory.h"
#include "nemu.h"
//#include "device/mm_io.h"
#include <memory.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

CacheLine L1_dcache[CACHE_SIZE_B / CACHELINE_SIZE_B];

void init_cache() {
  // set all content especially validBit zero
  memset(L1_dcache, 0, sizeof(CacheLine) * 1024);
}

/*
** Below are some help funcs.
*/

// get the flag of paddr
uint32_t get_paddr_flag(paddr_t paddr) {
  // first 19 bits of paddr
  uint32_t flag = paddr >> 13;
  return flag;
}

// get the set number of paddr
uint32_t get_paddr_setNo(paddr_t paddr) {
  // 3 bits in the middle of paddr
  uint32_t setNo = (paddr >> 6) & (0x7f);
  return setNo;
}

// get the block address of the paddr
uint32_t get_paddr_blockAddr(paddr_t paddr) {
  // last 6 bits of paddr
  uint32_t blockAddr = paddr & 0x3f;
  return blockAddr;
}

uint32_t chooseLine(uint32_t lineNoBgn, CacheLine* cache) {
  bool find = false;
  uint32_t linechosen = 0;
  for (size_t i = 0; i < SET_SIZE; ++i) {
    if (cache[lineNoBgn + i].bitAndFlag.validBit == 0) {
      find = true;
      linechosen = lineNoBgn + i;
    }
  }
  // random selection algorithm
  if (find == false) {
    srand(time(NULL));
    linechosen = lineNoBgn + rand() % SET_SIZE;
  }
  return linechosen;
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
  uint32_t lineNoChosen = 0;
  bool hitStatus = false;

  flag = get_paddr_flag(paddr);
  setNo = get_paddr_setNo(paddr);
  blockAddr = get_paddr_blockAddr(paddr);
  lineNoBgn = setNo * SET_SIZE;

  for (size_t i = 0; i < SET_SIZE; ++i) {
    if (cache[lineNoBgn + i].bitAndFlag.flag == flag) {
      if (cache[lineNoBgn + i].bitAndFlag.validBit == 1) {
        hitStatus = true;
        // printf("Hit Cache!\n");
        lineNoHit = lineNoBgn + i;
      }
    }
  }

  if (blockAddr + len >= 64) {
    hitStatus = false;
  }

  if (hitStatus) {
    memcpy(&ret, &cache[lineNoHit].content[blockAddr], len);
    return ret;
  } else {
    lineNoChosen = chooseLine(lineNoBgn, cache);
    memcpy(&ret, hw_mem + paddr, len);
    memcpy(cache[lineNoChosen].content, hw_mem + ((paddr >> 6) << 6),
           BLOCK_SIZE);
    cache[lineNoChosen].bitAndFlag.validBit = 1;
    cache[lineNoChosen].bitAndFlag.flag = flag;
    return ret;
  }
}

// write cache
void cache_write(paddr_t paddr, size_t len, uint32_t data, CacheLine* cache) {
  uint32_t flag = 0;
  uint32_t setNo = 0;
  uint32_t lineNoBgn = 0;

  flag = get_paddr_flag(paddr);
  setNo = get_paddr_setNo(paddr);
  // blockAddr = get_paddr_blockAddr(paddr);
  lineNoBgn = setNo * SET_SIZE;
  // two blocks
  for (size_t i = 0; i < 2 * SET_SIZE; ++i) {
    if (cache[lineNoBgn + i].bitAndFlag.flag == flag) {
      if (cache[lineNoBgn + i].bitAndFlag.validBit == 1) {
        // hitStatus = true;
        cache[lineNoBgn + i].bitAndFlag.validBit = 0;
      }
    }
  }

  memcpy(hw_mem + paddr, &data, len);
}