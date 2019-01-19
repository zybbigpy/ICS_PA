#include "cpu/cpu.h"
#include "memory/memory.h"
#include "stdio.h"

// return the linear address from the virtual address and segment selector
uint32_t segment_translate(uint32_t offset, uint8_t sreg) {
	/* TODO: perform segment translation from virtual address to linear address
	 * by reading the invisible part of the segment register 'sreg'
	 */
	uint32_t laddr = 0;
	uint32_t base = cpu.segReg[sreg].base;
	laddr = base + offset;
	return laddr;
}

// load the invisible part of a segment register
void load_sreg(uint8_t sreg) {
	/* TODO: load the invisibile part of the segment register 'sreg' by reading the GDT.
	 * The visible part of 'sreg' should be assigned by mov or ljmp already.
	 */

	// find the addr of the segtable
	uint32_t laddr_segtable_bgn = cpu.gdtr.base;
	// the size of segdesc is 8 bytes 
	uint32_t laddr_segtable_offset = cpu.segReg[sreg].index * sizeof(SegDesc);
	// define the segdesc find
	uint32_t laddr_segtable_fnd = laddr_segtable_bgn + laddr_segtable_offset;
	
	// load the segdesc
	SegDesc sd;
	sd.val[0] = laddr_read(laddr_segtable_fnd, 4);
	sd.val[1] = laddr_read(laddr_segtable_fnd + 4, 4);

	// // load cache part of segreg according to the segdesc
	printf("cpu cr0 pe = %d \n", cpu.cr0.pe);
	printf("sd.present = %d \n", sd.present);
	assert(sd.present==1);
	cpu.segReg[sreg].soft_use = sd.soft_use;
	cpu.segReg[sreg].privilege_level = sd.soft_use;
	cpu.segReg[sreg].type = sd.type;
	cpu.segReg[sreg].base = (sd.base_31_24 << 24) + (sd.base_23_16 << 16) 
							+ sd.base_15_0;
	cpu.segReg[sreg].limit = (sd.limit_19_16 << 16) + sd.limit_15_0;
	// for debug use
	if(cpu.cr0.pe == 0) {
		assert(sd.granularity == 1);
		assert(cpu.segReg[sreg].base == 0x0);
		assert(cpu.segReg[sreg].limit == 0xfffff);
	}
}
