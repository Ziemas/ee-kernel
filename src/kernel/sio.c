#include "common.h"

// sio putc
INCLUDE_ASM("asm/kernel/nonmatchings/sio", func_80015700);

// sio status
INCLUDE_ASM("asm/kernel/nonmatchings/sio", func_80015748);

// PIF puts
void func_80015838(char* s) {
   	volatile struct pif_reg *pif = PIFREG;
    char c = *s;
    
    while (*s != 0) {
	    pif->com_send = *s;
	    pif->unk30 = 1;
        while (!(pif->unk20 & 2))
            ;
	    pif->unk2C = 2;

        c = *s++;
    }
}
