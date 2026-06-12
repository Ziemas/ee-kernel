#include "common.h"

struct list_head {
    // TODO think about the order
    struct list_head *prev, *next;
};

struct IntHandler {
    /* 0x00 */ struct list_head l;
    /* 0x08 */ void (*handler)();
    /* 0x0c */ int unkC;
    /* 0x10 */ void* arg;
    /* 0x14 */ int state;
};

struct IntQueue {
    struct list_head l;
    int entries;
};

extern struct IntQueue D_8001B418[INTC_MAX];
extern struct IntQueue D_8001B4D0[DMAC_MAX];

extern struct IntHandler D_8001b590[129];

// int handler pool list
extern struct list_head D_8001B410;
// number of used int handlers
extern int D_8001B400;

// list pop
struct list_head* func_80006420(struct list_head* list);
// list insert
void func_800064D0(struct list_head*, struct list_head*);

// backing array for ntc pool entries
extern struct list_head D_8001B590[];

// VSYNC flag ptr
extern int* D_8001B404;
// VSYNC CSR ptr
extern u_long* D_8001B408;

void func_80000DC0(int);
int func_800029C0(void*, void*, ...);

extern void* D_800174E4;

// pop int handler pool
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

// return to pool
void func_80001628(int arg0)
{
    func_800064D0(&D_8001B410, (arg0 * 0x18) + (void*)D_8001B590);
    D_8001B400 -= 1;
}

// INTC irq handler
void func_80001670(int inum)
{
    struct IntHandler* hnd;
    u_int gp, epc;
    int i, res;

    if (inum == INTC_VBLANK_S && D_8001B404) {
        *D_8001B404 = 1;
        D_8001B404 = NULL;

        if (D_8001B408) {
            // read GS CSR
            *D_8001B408 = *(volatile u_long*)0xb2001000;
            D_8001B408 = NULL;
        }
    }

    hnd = (struct IntHandler*)D_8001B418[inum].l.next;
    for (i = 0; i < D_8001B418[inum].entries; i++) {
        if (hnd->state == 2) {
            __asm__ __volatile__("move %0, $gp \n" : "=r"(gp));
            __asm__ __volatile__("move $gp, %0 \n" ::"r"(hnd->unkC));
            __asm__ __volatile__("mfc0 %0, $14 \n" : "=r"(epc));

            res = func_800029C0(D_800174E4, hnd->handler, inum, hnd->arg, epc);

            if (res < 0) {
                __asm__ __volatile__("move $gp, %0 \n" ::"r"(gp));
                return;
            }

            __asm__ __volatile__("move $gp, %0 \n" ::"r"(gp));
        } else if (hnd->state == 0) {
            hnd->handler(inum);
        }

        hnd = (struct IntHandler*)hnd->l.next;
    }

    if (i == 0) {
        kprintf("# INTC(%d) Handler does not exist.\n", inum);
        func_80000DC0(1);
    }
}

// DMAC irq handler
void func_800017D8(int inum)
{
    struct IntHandler* hnd;
    u_int gp, epc;
    int i, res;

    hnd = (struct IntHandler*)D_8001B4D0[inum].l.next;
    for (i = 0; i < D_8001B4D0[inum].entries; i++) {
        if (hnd->state == 2) {
            __asm__ __volatile__("move %0, $gp \n" : "=r"(gp));
            __asm__ __volatile__("move $gp, %0 \n" ::"r"(hnd->unkC));
            __asm__ __volatile__("mfc0 %0, $14 \n" : "=r"(epc));

            res = func_800029C0(D_800174E4, hnd->handler, inum, hnd->arg, epc);

            if (res < 0) {
                __asm__ __volatile__("move $gp, %0 \n" ::"r"(gp));
                return;
            }

            __asm__ __volatile__("move $gp, %0 \n" ::"r"(gp));
        } else if (hnd->state == 0) {
            hnd->handler(inum);
        }

        hnd = (struct IntHandler*)hnd->l.next;
    }

    if (i == 0) {
        kprintf("# DMAC(%d) Handler does not exist.\n", inum);
        func_80000DC0(1);
    }
}

INCLUDE_ASM("asm/kernel/nonmatchings/intr", func_800018F0);

INCLUDE_ASM("asm/kernel/nonmatchings/intr", func_80001A70);

INCLUDE_ASM("asm/kernel/nonmatchings/intr", func_80001A90);

INCLUDE_ASM("asm/kernel/nonmatchings/intr", func_80001AB0);

INCLUDE_ASM("asm/kernel/nonmatchings/intr", func_80001B50);

INCLUDE_ASM("asm/kernel/nonmatchings/intr", func_80001CB8);

INCLUDE_ASM("asm/kernel/nonmatchings/intr", func_80001CD8);

INCLUDE_ASM("asm/kernel/nonmatchings/intr", func_80001CF8);
