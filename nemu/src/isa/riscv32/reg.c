#include <isa.h>
#include "local-include/reg.h"
#define REGS_LEN sizeof(regs)/sizeof(const char *)

const char *regs[] = {
  "$0", "ra", "sp", "gp", "tp", "t0", "t1", "t2",
  "s0", "s1", "a0", "a1", "a2", "a3", "a4", "a5",
  "a6", "a7", "s2", "s3", "s4", "s5", "s6", "s7",
  "s8", "s9", "s10", "s11", "t3", "t4", "t5", "t6"
};

void isa_reg_display() {
	for(int i=0;i<REGS_LEN;i++){
		printf("%-15s%-15x%-15d\n",regs[i],cpu.gpr[i]._32,cpu.gpr[i]._32);
	}
	printf("%-15s%-15x%-15d\n","pc",cpu.pc,cpu.pc);
}

word_t isa_reg_str2val(const char *s, bool *success) {
	*success = true;
	if(strcmp(s, "pc") == 0)
		return cpu.pc;
	for(int i=0;i<REGS_LEN;i++){
		if(strcmp(s,regs[i]) == 0)
		{
			return cpu.gpr[i]._32;
		}
	}
	*success = false;
  	return 0;
}
