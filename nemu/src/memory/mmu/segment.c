#include "cpu/cpu.h"
#include "memory/memory.h"

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
	uint32_t laddr_segtable_fnd = laddr_segtable_bgn + (cpu.segReg[sreg].index << 3);
	
	// load the segdesc
	SegDesc sd;
	memcpy(sd.val[0], laddr_segtable_fnd, 4);
	memcpy(sd.val[1], laddr_segtable_fnd + 4, 4);

	// load cache part of segreg according to the segdesc
	cpu.segReg[sreg].soft_use = 0;
	cpu.segReg[sreg].privilege_level =0;
	cpu.segReg[sreg].type =0;
	cpu.segReg[sreg].base =0;
	cpu.segReg[sreg].limit=0;
}
