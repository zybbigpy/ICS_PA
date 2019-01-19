#include "cpu/cpu.h"
#include "memory/memory.h"

// translate from linear address to physical address
paddr_t page_translate(laddr_t laddr) {
#ifndef TLB_ENABLED
	//printf("\nPlease implement page_translate()\n");
	//assert(0);
	// uint32_t DIR = laddr >> 22;
	// uint32_t PAGE = (laddr >> 12) & 0x3ff;
	// uint32_t OFFSET = laddr & 0xfff;
	// uint32_t paddr = 0;
	// uint32_t page_dir_base_addr = cpu.cr3.pdbr << 12;
	// PDE pde;
	// memcpy(&pde, hw_mem + page_dir_base_addr + DIR * 4, 4);
	// assert(pde.present == 1);
	// uint32_t page_tbl_base_addr = pde.page_frame << 12;
	// PTE pte;
	// memcpy(&pte, hw_mem + page_tbl_base_addr + PAGE * 4, 4);
	// assert(pte.present == 1);
	// paddr = (pte.page_frame << 12) + OFFSET;
	// return paddr;
	PDE pde;
	PTE pte;
	paddr_t paddr=0;
	paddr_t pageTable_addr;
	paddr_t pageDir_addr;
	int pageDir_index=laddr>>22;
	int pageTable_index=(laddr>>12)&0x3FF;
	int offset=laddr&0xFFF;
	pageDir_addr=cpu.cr3.pdbr*0x1000;
	//printf("%x locating\n",laddr);
	pde.val=paddr_read(pageDir_addr+pageDir_index*4,4);
	if(pde.present==0){
		printf("laddr is %d \n", laddr);
		printf("laddr is %x,eip is %x\n",laddr,cpu.eip);
		assert(pde.present==1);
	}
	pageTable_addr=pde.page_frame*0x1000;
	//printf("addr is %x\n",pageTable_addr+pageTable_index*4);
	pte.val=paddr_read(pageTable_addr+pageTable_index*4,4);
	if(pte.present==0){
		printf("laddr is %x,tabel addr is %x,eip is %x\n",laddr,pde.page_frame,cpu.eip);
		assert(pte.present==1);
	}
	paddr=pte.page_frame*0x1000+offset;
	//if(laddr>0xa0000&&laddr<0xafa00) 	printf("laddr is %x,tabladdr is %x,diraddr is %x,paddr is%x\n",laddr,pageTable_addr,pageDir_addr,paddr);
	return paddr;
#else	
	return tlb_read(laddr) | (laddr & PAGE_MASK);;
#endif
}
