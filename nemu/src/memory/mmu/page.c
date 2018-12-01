#include "cpu/cpu.h"
#include "memory/memory.h"

// translate from linear address to physical address
paddr_t page_translate(laddr_t laddr) {
#ifndef TLB_ENABLED
	//printf("\nPlease implement page_translate()\n");
	//assert(0);
	uint32_t DIR = laddr >> 22;
	uint32_t PAGE = (laddr >> 12) & 0x3ff;
	uint32_t OFFSET = laddr & 0xfff;
	
#else	
	return tlb_read(laddr) | (laddr & PAGE_MASK);;
#endif
}
