#include "common.h"

struct list_head {
    struct list_head *next, *prev;
};

extern struct list_head D_8001B410;
extern int D_8001B400;
struct list_head *func_80006420(struct list_head *list);


struct list_head *func_800015E0()
{
	struct list_head* i;

	i = func_80006420(&D_8001B410);
	if (!i) {
		return 0;
	}

	D_8001B400++;

	return i;
}

INCLUDE_ASM("asm/kernel/nonmatchings/intr", func_80001628);

INCLUDE_ASM("asm/kernel/nonmatchings/intr", func_80001670);

INCLUDE_ASM("asm/kernel/nonmatchings/intr", func_800017D8);

INCLUDE_ASM("asm/kernel/nonmatchings/intr", func_800018F0);

INCLUDE_ASM("asm/kernel/nonmatchings/intr", func_80001A70);

INCLUDE_ASM("asm/kernel/nonmatchings/intr", func_80001A90);

INCLUDE_ASM("asm/kernel/nonmatchings/intr", func_80001AB0);

INCLUDE_ASM("asm/kernel/nonmatchings/intr", func_80001B50);

INCLUDE_ASM("asm/kernel/nonmatchings/intr", func_80001CB8);

INCLUDE_ASM("asm/kernel/nonmatchings/intr", func_80001CD8);

INCLUDE_ASM("asm/kernel/nonmatchings/intr", func_80001CF8);
