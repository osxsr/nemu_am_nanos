#include <cpu/decode.h>
#include "../local-include/rtl.h"

#define INSTR_LIST(f) f(lui) f(lw) f(sw) f(inv) f(nemu_trap) f(addi) f(auipc) f(jal) f(jalr) \
                      f(beq) f(sltiu) f(slti) f(bne) f(add) f(sub) f(slt) f(sltu) f(xor) f(or)\
                      f(sh) f(srai) f(srli) f(slli) 

def_all_EXEC_ID();
