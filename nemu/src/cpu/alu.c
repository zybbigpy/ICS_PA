#include "cpu/cpu.h"
void set_CF_add(uint32_t result,uint32_t src,size_t data_size){
  result = sign_ext(result&(0xffffffff>>(32-data_size)),data_size);
  src = sign_ext(src&(0xffffffff>>(32-data_size)),data_size);
  cpu.eflags.CF=result<src;
}
void set_PF(uint32_t result){
  int flag = 0;
  result=result&0x000000ff;
  while(result!=0)
  {
    if(result%2==1)
    { flag++;}
    result=result/2;
  }
  if(flag%2==0)
  {
    cpu.eflags.PF=1;
  }
  else {
    cpu.eflags.PF=0;
  }
  
}
void set_ZF(uint32_t result,size_t data_size){

  result=result&(0xffffffff>>(32-data_size));
  cpu.eflags.ZF=(result==0);
}
void set_SF(uint32_t result,size_t data_size)
{
  result=sign_ext(result&(0xffffffff>>(32-data_size)),data_size);
  cpu.eflags.SF=sign(result);
}
void set_OF_add(uint32_t result,uint32_t src,uint32_t dest,size_t data_size){
  switch(data_size){
    case 8:
      result=sign_ext(result&0xff,8);
      src=sign_ext(src&0xff,8);
      dest=sign_ext(dest&0xff,8);
      break;
    case 16: 
      result=sign_ext(result&0xffff,16);
      src=sign_ext(src&0xffff,16);
      dest=sign_ext(dest&0xffff,16);
      break;
    default:break;
  } 
  if(sign(src)==sign(dest)){
    if(sign(src)!=sign(result)){cpu.eflags.OF=1;}
    else{cpu.eflags.OF=0;} 
  }
  else{
    cpu.eflags.OF=0;
  }
}
uint32_t alu_add(uint32_t src, uint32_t dest, size_t data_size) {
#ifdef NEMU_REF_ALU
	return __ref_alu_add(src, dest, data_size);
#else

  uint32_t res = 0;
  res = dest+ src;
  
  set_CF_add(res,src,data_size);
  set_ZF(res,data_size);
  set_PF(res);
  set_SF(res,data_size);
  set_OF_add(res,src,dest,data_size);
  return res&(0xffffffff>>(32-data_size));
	//printf("\e[0;31mPlease implement me at alu.c\e[0m\n");
	
  //assert(0);
	//return 0;
#endif 
}

uint32_t alu_adc(uint32_t src, uint32_t dest, size_t data_size) {
#ifdef NEMU_REF_ALU
	return __ref_alu_adc(src, dest, data_size);
#else
	printf("\e[0;31mPlease implement me at alu.c\e[0m\n");
	assert(0);
	return 0;
#endif
}


void set_CF_sub(uint32_t result,uint32_t src,size_t data_size){
  result = sign_ext(result&(0xffffffff>>(32-data_size)),data_size);
  src = sign_ext(src&(0xffffffff>>(32-data_size)),data_size);
  cpu.eflags.CF=result>src;
}
uint32_t alu_sub(uint32_t src, uint32_t dest, size_t data_size) {
#ifdef NEMU_REF_ALU
	return __ref_alu_sub(src, dest, data_size);
#else
	//printf("\e[0;31mPlease implement me at alu.c\e[0m\n");
  uint32_t res = 0;
  res = dest - src;
  
  set_CF_sub(res,dest,data_size);
  set_ZF(res,data_size);
  set_PF(res);
  set_SF(res,data_size);
  //OF is the same as add 
  set_OF_add(res,src,dest,data_size);
  //	assert(0);
  return res&(0xffffffff>>(32-data_size));
	//return 0;
#endif
}

uint32_t alu_sbb(uint32_t src, uint32_t dest, size_t data_size) {
#ifdef NEMU_REF_ALU
	return __ref_alu_sbb(src, dest, data_size);
#else
	printf("\e[0;31mPlease implement me at alu.c\e[0m\n");
	assert(0);
	return 0;
#endif
}


uint64_t alu_mul(uint32_t src, uint32_t dest, size_t data_size) {
#ifdef NEMU_REF_ALU
	return __ref_alu_mul(src, dest, data_size);
#else
	printf("\e[0;31mPlease implement me at alu.c\e[0m\n");
	assert(0);
	return 0;
#endif
}

int64_t alu_imul(int32_t src, int32_t dest, size_t data_size) {
#ifdef NEMU_REF_ALU
	return __ref_alu_imul(src, dest, data_size);
#else
	printf("\e[0;31mPlease implement me at alu.c\e[0m\n");
	assert(0);
	return 0;
#endif
}

uint32_t alu_div(uint64_t src, uint64_t dest, size_t data_size) {
#ifdef NEMU_REF_ALU
	return __ref_alu_div(src, dest, data_size);
#else
	printf("\e[0;31mPlease implement me at alu.c\e[0m\n");
	assert(0);
	return 0;
#endif
}

int32_t alu_idiv(int64_t src, int64_t dest, size_t data_size) {
#ifdef NEMU_REF_ALU
	return __ref_alu_idiv(src, dest, data_size);
#else
	printf("\e[0;31mPlease implement me at alu.c\e[0m\n");
	assert(0);
	return 0;
#endif
}

uint32_t alu_mod(uint64_t src, uint64_t dest) {
#ifdef NEMU_REF_ALU
	return __ref_alu_mod(src, dest);
#else
	printf("\e[0;31mPlease implement me at alu.c\e[0m\n");
	assert(0);
	return 0;
#endif
}

int32_t alu_imod(int64_t src, int64_t dest) {
#ifdef NEMU_REF_ALU
	return __ref_alu_imod(src, dest);
#else
	printf("\e[0;31mPlease implement me at alu.c\e[0m\n");
	assert(0);
	return 0;
#endif
}

uint32_t alu_and(uint32_t src, uint32_t dest, size_t data_size) {
#ifdef NEMU_REF_ALU
	return __ref_alu_and(src, dest, data_size);
#else
	printf("\e[0;31mPlease implement me at alu.c\e[0m\n");
	assert(0);
	return 0;
#endif
}

uint32_t alu_xor(uint32_t src, uint32_t dest, size_t data_size) {
#ifdef NEMU_REF_ALU
	return __ref_alu_xor(src, dest, data_size);
#else
	printf("\e[0;31mPlease implement me at alu.c\e[0m\n");
	assert(0);
	return 0;
#endif
}

uint32_t alu_or(uint32_t src, uint32_t dest, size_t data_size) {
#ifdef NEMU_REF_ALU
	return __ref_alu_or(src, dest, data_size);
#else
	printf("\e[0;31mPlease implement me at alu.c\e[0m\n");
	assert(0);
	return 0;
#endif
}

uint32_t alu_shl(uint32_t src, uint32_t dest, size_t data_size) {
#ifdef NEMU_REF_ALU
	return __ref_alu_shl(src, dest, data_size);
#else
	printf("\e[0;31mPlease implement me at alu.c\e[0m\n");
	assert(0);
	return 0;
#endif
}

uint32_t alu_shr(uint32_t src, uint32_t dest, size_t data_size) {
#ifdef NEMU_REF_ALU
	return __ref_alu_shr(src, dest, data_size);
#else
	printf("\e[0;31mPlease implement me at alu.c\e[0m\n");
	assert(0);
	return 0;
#endif
}

uint32_t alu_sar(uint32_t src, uint32_t dest, size_t data_size) {
#ifdef NEMU_REF_ALU
	return __ref_alu_sar(src, dest, data_size);	
#else
	printf("\e[0;31mPlease implement me at alu.c\e[0m\n");
	assert(0);
	return 0;
#endif
}

uint32_t alu_sal(uint32_t src, uint32_t dest, size_t data_size) {
#ifdef NEMU_REF_ALU
	return __ref_alu_sal(src, dest, data_size);
#else
	printf("\e[0;31mPlease implement me at alu.c\e[0m\n");
	assert(0);
	return 0;
#endif
}
