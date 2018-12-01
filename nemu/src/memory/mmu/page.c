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
	uint32_t paddr = 0;
	uint32_t page_dir_base_addr = cpu.cr3.pdbr << 12;
	PDE pde;
	memcpy(&pde, hw_mem + page_dir_base_addr + DIR*4, 4);
	uint32_t page_tbl_base_addr = pde.page_frame << 12;
	PTE pte;
	memcpy(&pte, hw_mem + page_tbl_base_addr + PAGE*4, 4);
	paddr = pte.page_frame << 12 + OFFSET;
	return paddr;

#else	
	return tlb_read(laddr) | (laddr & PAGE_MASK);;
#endif
}
