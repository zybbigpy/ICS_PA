#include "nemu.h"
#include "cpu/cpu.h"
#include "memory/memory.h"
#include "device/mm_io.h"
#include <memory.h>
#include <stdio.h>


uint8_t hw_mem[MEM_SIZE_B];

uint32_t hw_mem_read(paddr_t paddr, size_t len) {
	uint32_t ret = 0;
	memcpy(&ret, hw_mem + paddr, len);
	return ret;
}

void hw_mem_write(paddr_t paddr, size_t len, uint32_t data) {
	memcpy(hw_mem + paddr, &data, len);
}

uint32_t paddr_read(paddr_t paddr, size_t len) {
	uint32_t ret = 0;
#ifdef CACHE_ENABLED
	ret = cache_read(paddr, len, L1_dcache);
#else
	ret = hw_mem_read(paddr, len);
#endif
	return ret;
}

void paddr_write(paddr_t paddr, size_t len, uint32_t data) {
#ifdef CACHE_ENABLED
	cache_write(paddr, len, data, L1_dcache);
#else
	hw_mem_write(paddr, len, data);
#endif
}


uint32_t laddr_read(laddr_t laddr, size_t len) {
#ifndef IA32_PAGE
	return paddr_read(laddr, len);
#else
	uint32_t paddr = laddr;
	if(cpu.cr0.pg == 1) { 
		if((laddr & 0xfff)+ len > 0x1000) { 
			// page across
			uint32_t res = 0;
			for (int i = len; i != 0; i--) {
				res = (res << 8) + laddr_read(paddr + i - 1, 1);
			}
			return res;
		} else {
			paddr = page_translate(laddr);
		}	
	}
	return paddr_read(paddr, len);
#endif
}

void laddr_write(laddr_t laddr, size_t len, uint32_t data) {
#ifndef IA32_PAGE
	paddr_write(laddr, len, data);
#else
	uint32_t paddr = laddr;
	if(cpu.cr0.pg == 1) {
		if((laddr & 0xfff) + len > 0x1000) {
			printf("page across! \n");
			for(int i = 0; i != len; i++) {
				laddr_write(paddr + i, 1, (data & 0xff));
				data >>= 8;
			}
			return ;
		} else {
			paddr = page_translate(laddr);
		}
	}
	return paddr_write(paddr, len, data);
#endif
}


uint32_t vaddr_read(vaddr_t vaddr, uint8_t sreg, size_t len) {
	assert(len == 1 || len == 2 || len == 4);
#ifndef IA32_SEG
	return laddr_read(vaddr, len);
#else
	uint32_t laddr = vaddr;
	if(cpu.cr0.pe == 1) {
		laddr = segment_translate (vaddr, sreg);
	}
	return laddr_read(laddr, len);
#endif
}

void vaddr_write(vaddr_t vaddr, uint8_t sreg, size_t len, uint32_t data) {
	assert(len == 1 || len == 2 || len == 4);
#ifndef IA32_SEG
	return laddr_write(vaddr, len, data);
#else
	uint32_t laddr = vaddr;
	if(cpu.cr0.pe == 1) {
		laddr = segment_translate(vaddr, sreg);
	}
	return laddr_write(laddr, len, data);
#endif
}

void init_mem() {
#ifdef CACHE_ENABLED
	init_cache();
#endif
	// clear the memory on initiation
	memset(hw_mem, 0, MEM_SIZE_B);

#ifdef TLB_ENABLED
	make_all_tlb();
	init_all_tlb();
#endif
}

uint32_t instr_fetch(vaddr_t vaddr, size_t len) {
	assert(len == 1 || len == 2 || len == 4);
	return vaddr_read(vaddr, SREG_CS, len);
}

uint8_t * get_mem_addr() {
	return hw_mem;
}
// uint8_t hw_mem[MEM_SIZE_B];

// uint32_t hw_mem_read(paddr_t paddr, size_t len) {
// 	uint32_t ret = 0;
// 	//printf("paddr:%x,len:%x\n",paddr,len);
// 	memcpy(&ret, hw_mem + paddr, len);
// 	//printf("ret=%x\n",ret);
// 	return ret;
// }

// void hw_mem_write(paddr_t paddr, size_t len, uint32_t data) {
// 	memcpy(hw_mem + paddr, &data, len);
// }

// uint32_t paddr_read(paddr_t paddr, size_t len) {
// 	uint32_t ret = 0;
// 	//ret=cache_read(paddr,len,cache_mem);
// 	if(is_mmio(paddr)!=-1){
// 		ret = mmio_read(paddr,len,is_mmio(paddr));
// 	}
// 	else{
// 		ret = hw_mem_read(paddr, len);
// 	}
// 	return ret;
// }

// void paddr_write(paddr_t paddr, size_t len, uint32_t data) {
// 	//cache_write(paddr,len,data,cache_mem);
// 	if(is_mmio(paddr)!=-1){
// 		mmio_write(paddr,len,data,is_mmio(paddr));
// 	}
// 	else{
// 		hw_mem_write(paddr, len, data);
// 	}
// }


// uint32_t laddr_read(laddr_t laddr, size_t len) {
// 	paddr_t paddr=laddr;
// 	if(cpu.cr0.pg==1){	
// 		if(((laddr&0xFFF)+len)>0x1000){
// 			uint32_t ret,len1,len2;
// 			len1=0x1000-(laddr&0xFFF);
// 			len2=(laddr&0xFFF)+len-0x1000;
// 			paddr=page_translate(laddr);
// 			ret=paddr_read(paddr,len1);
// 			paddr=page_translate(laddr+0x1000-(laddr&0xFFF));
// 			ret+=paddr_read(paddr,len2)<<(8*len1);
// 			//printf("ret = %x,ebp =%x\n",ret,cpu.ebp);
// 			return ret;
// 		}
// 		paddr=page_translate(laddr);
// 	}
// 	return paddr_read(paddr, len);
// }

// void laddr_write(laddr_t laddr, size_t len, uint32_t data) {
// 	paddr_t paddr=laddr;
// 	//``printf("writing to %x\n",laddr);
// 	if(cpu.cr0.pg==1){
// 		if(((laddr&0xFFF)+len)>0x1000){
// 			//printf("laddr is %x\n",laddr);
// 			uint32_t len1,len2;
// 			len1=0x1000-(laddr&0xFFF);
// 			len2=(laddr&0xFFF)+len-0x100;
// 			paddr=page_translate(laddr);
// 			paddr_write(paddr,len1,data&((1<<(len1*8+1))-1));
// 			paddr=page_translate(laddr+0x1000-(laddr&0xFFF));
// 			paddr_write(paddr,len2,data>>len1*8);
// 			return;
// 		}
// 		paddr=page_translate(laddr);
// 	}
// 	paddr_write(paddr, len, data);
// }


// uint32_t vaddr_read(vaddr_t vaddr, uint8_t sreg, size_t len) {
// 	assert(len == 1 || len == 2 || len == 4);
// 	laddr_t laddr=vaddr;
// 	if(cpu.cr0.pe==1){
// 		laddr=segment_translate(laddr,sreg);
// 	}
// 	return laddr_read(laddr, len);
// }

// void vaddr_write(vaddr_t vaddr, uint8_t sreg, size_t len, uint32_t data) {
// 	//printf(" %x,%d ",vaddr,len);
// 	assert(len == 1 || len == 2 || len == 4);
// 	laddr_t laddr=vaddr;
// 	if(cpu.cr0.pe==1){
// 		laddr=segment_translate(laddr,sreg);
// 	}
// 	laddr_write(laddr, len,data);
// }

// void init_mem() {
// 	// clear the memory on initiation
// 	init_cache();
// 	memset(hw_mem, 0, MEM_SIZE_B);

// #ifdef TLB_ENABLED
// 	init_all_tlb();
// 	make_all_tlb();
// #endif
// }

// uint32_t instr_fetch(vaddr_t vaddr, size_t len) {
// 	assert(len == 1 || len == 2 || len == 4);
// 	return vaddr_read(vaddr, SREG_CS, len);
// }

// uint8_t * get_mem_addr() {
// 	return hw_mem;
// }
