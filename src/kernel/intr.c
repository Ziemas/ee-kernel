#include "common.h"

struct list_head {
    // TODO think about the order
    struct list_head *prev, *next;
};

struct IntHandler {
    /* 0x00 */ struct list_head l;
    /* 0x08 */ void (*handler)();
    /* 0x0c */ int gp;
    /* 0x10 */ void* arg;
    /* 0x14 */ int state;
};

struct IntQueue {
    struct list_head l;
    int entries;
};

// intc handlers
extern struct IntQueue D_8001B418[INTC_MAX];
// dmac handlers
extern struct IntQueue D_8001B4D0[DMAC_MAX];

extern struct IntHandler D_8001B590[129];

// int handler pool list
extern struct list_head D_8001B410;
// number of used int handlers
extern int D_8001B400;

// list pop
struct list_head* func_80006420(struct list_head* list);
// list remove
struct list_head* func_800064B0(struct list_head* node);
// list insert
void func_800064D0(struct list_head*, struct list_head*);

// backing array for intc pool entries
extern struct IntHandler D_8001B590[129];

// VSYNC flag ptr
extern int* D_8001B404;
// VSYNC CSR ptr
extern u_long* D_8001B408;

void func_80000DC0(int);
int func_800029C0(void*, void*, ...);

extern void* D_800174E4;

// pop int handler pool
struct IntHandler* func_800015E0()
{
    struct list_head* i;

    i = func_80006420(&D_8001B410);
    if (!i) {
        return 0;
    }

    D_8001B400++;

    return (struct IntHandler*)i;
}

// return to pool
void func_80001628(int arg0)
{
    func_800064D0(&D_8001B410, &D_8001B590[arg0].l);
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
            asm volatile("move %0, $gp \n" : "=r"(gp));
            asm volatile("move $gp, %0 \n" ::"r"(hnd->gp));
            asm volatile("mfc0 %0, $14 \n" : "=r"(epc));

            res = func_800029C0(D_800174E4, hnd->handler, inum, hnd->arg, epc);

            if (res < 0) {
                asm volatile("move $gp, %0 \n" ::"r"(gp));
                return;
            }

            asm volatile("move $gp, %0 \n" ::"r"(gp));
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
            asm volatile("move %0, $gp \n" : "=r"(gp));
            asm volatile("move $gp, %0 \n" ::"r"(hnd->gp));
            asm volatile("mfc0 %0, $14 \n" : "=r"(epc));

            res = func_800029C0(D_800174E4, hnd->handler, inum, hnd->arg, epc);

            if (res < 0) {
                asm volatile("move $gp, %0 \n" ::"r"(gp));
                return;
            }

            asm volatile("move $gp, %0 \n" ::"r"(gp));
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

int func_800018F0(int cause, void (*handler)(int, void*, void*), int next, void* arg, int unk)
{
    struct IntHandler* hnd;
    u_int gp;

    if (unk != 0 && cause == INTC_SBUS) {
        return -1;
    }

    if (cause >= (u_int)INTC_MAX) {
        return -1;
    }

    hnd = func_800015E0();
    if (!hnd) {
        return -1;
    }

    asm("move %0, $gp \n" : "=r"(gp));

    hnd->handler = handler;
    hnd->gp = gp;
    hnd->arg = arg;
    hnd->state = unk;

    switch (next) {
    case -1:
        func_800064D0(&D_8001B418[cause].l, &hnd->l);
        break;
    case 0:
        func_800064D0(D_8001B418[cause].l.next, &hnd->l);
        break;
    default:
        if (next < 0 || next - 1 > 0x7fu || D_8001B590[next].state == 3) {
            return -1;
        }

        func_800064D0(&D_8001B590[next].l, &hnd->l);
        break;
    }
    D_8001B418[cause].entries++;

    return hnd - D_8001B590;
}

// AddIntcHandler
int func_80001A70(int cause, void (*handler)(int, void*, void*), int next, void* arg)
{
    return func_800018F0(cause, handler, next, arg, 2);
}

int func_80001A90(int cause, void (*handler)(int, void*, void*), int next, void* arg)
{
    return func_800018F0(cause, handler, next, arg, 0);
}

// RemoveIntcHandler2
// INCLUDE_ASM("asm/kernel/nonmatchings/intr", func_80001AB0);
int func_80001AB0(int cause, int hid)
{
    if (hid < 0 || hid - 1 > 0x7fu) {
        return -1;
    }

    if (D_8001B590[hid].state == 3) {
        return -1;
    }

    D_8001B590[hid].state = 3;
    D_8001B590[hid].handler = NULL;

    func_800064B0(&D_8001B590[hid].l);
    func_80001628(hid);

    D_8001B418[cause].entries--;

    return D_8001B418[cause].entries;
}

int func_80001B50(int cause, void (*handler)(int, void*, void*), int next, void* arg, int unk)
{
    struct IntHandler* hnd;
    u_int gp;

    if (cause >= (u_int)DMAC_MAX) {
        return -1;
    }

    hnd = func_800015E0();
    if (!hnd) {
        return -1;
    }

    asm("move %0, $gp \n" : "=r"(gp));

    hnd->handler = handler;
    hnd->gp = gp;
    hnd->arg = arg;
    hnd->state = unk;

    switch (next) {
    case -1:
        func_800064D0(&D_8001B4D0[cause].l, &hnd->l);
        break;
    case 0:
        func_800064D0(D_8001B4D0[cause].l.next, &hnd->l);
        break;
    default:
        if (next < 0 || next - 1 > 0x7fu || D_8001B590[next].state == 3) {
            return -1;
        }

        func_800064D0(&D_8001B590[next].l, &hnd->l);
        break;
    }
    D_8001B4D0[cause].entries++;

    return hnd - D_8001B590;
}

int func_80001CB8(int cause, void (*handler)(int, void*, void*), int next, void* arg)
{
    return func_80001B50(cause, handler, next, arg, 2);
}

int func_80001CD8(int cause, void (*handler)(int, void*, void*), int next, void* arg)
{
    return func_80001B50(cause, handler, next, arg, 0);
}

//INCLUDE_ASM("asm/kernel/nonmatchings/intr", func_80001CF8);
int func_80001CF8(int cause, int hid)
{
    if (hid < 0 || hid - 1 > 0x7fu) {
        return -1;
    }

    if (D_8001B590[hid].state == 3) {
        return -1;
    }

    D_8001B590[hid].state = 3;
    D_8001B590[hid].handler = NULL;

    func_800064B0(&D_8001B590[hid].l);
    func_80001628(hid);

    D_8001B4D0[cause].entries--;

    return D_8001B4D0[cause].entries;
}

// probably more
