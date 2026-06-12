#include "common.h"

struct list_head {
    struct list_head *next, *prev;
};

extern struct list_head D_8001B410;
extern int D_8001B400;
struct list_head* func_80006420(struct list_head* list);
void func_800064D0(struct list_head*, struct list_head*);
extern struct list_head D_8001B590[];

struct list_head* func_800015E0()
{
    struct list_head* i;

    i = func_80006420(&D_8001B410);
    if (!i) {
        return 0;
    }

    D_8001B400++;

    return i;
}

void func_80001628(int arg0)
{
    func_800064D0(&D_8001B410, (arg0 * 0x18) + (void*)D_8001B590);
    D_8001B400 -= 1;
}

// default intc handler
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
