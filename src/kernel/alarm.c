#include "common.h"
#include "eeregs.h"
#include "intr.h"

struct alarm {
    int (*handler)();
    void* arg;
    u_int gp;
    int time;
    int target;
};

extern u_long D_8001C228; // active alarm bitfield
extern int D_8001C230; // alarm count
extern struct alarm D_8001C238[64]; // alarms
extern char D_8001C738[65]; // alarm queue

#if 1
INCLUDE_ASM("asm/kernel/nonmatchings/alarm", func_80002318);
#else
// idk if this is real
static inline int getAlarm()
{
    int i;

    for (i = 0; i < 64; i++) {
        if (!((D_8001C228 >> i) & 1)) {
            D_8001C228 |= (1ull << i);
            return i;
        }
    }

    return -1;
}

// SetAlarm
int func_80002318(u_short time, void(*cbfunc), void* arg)
{
    u_int gp, current_time, target_time;
    u_long status;
    int aidx;

    aidx = getAlarm();
    if (aidx < 0) {
        return -1;
    }

    asm volatile("move %0, $gp \n" : "=r"(gp));

    D_8001C238[aidx].handler = cbfunc;
    D_8001C238[aidx].arg = arg;
    D_8001C238[aidx].gp = gp;

    current_time = *T3_COUNT;

    D_8001C238[aidx].time = current_time;
    target_time = current_time + time;

    if (target_time >= 0x10000) {
        target_time &= 0xffff;
    }
    D_8001C238[aidx].target = target_time;

    if (current_time >= D_8001C238[aidx].target) {
    }

    return aidx;
}
#endif

// ReleaseAlarm
int func_800025B0(int id)
{
    u_int cur_time, alarm_time;
    int i;

    if (!((D_8001C228 >> id) & 1)) {
        return -1;
    }

    D_8001C230--;
    D_8001C228 &= ~(1ull << id);
    if (!D_8001C230) {
        *T3_MODE = 0x83;
    }

    // ?? how does this make sense
    // i thought this was a queue of active alarm id's
    for (i = 0; i < D_8001C230; i++) {
        D_8001C738[i] = D_8001C738[i + 1];
    }

    cur_time = *T3_COUNT;
    alarm_time = D_8001C238[id].time;
    if (cur_time >= alarm_time) {
        return cur_time - alarm_time;
    }

    return cur_time + (0x10000 - alarm_time);
}

// Seems to not match with assembler from ee-gcc2.9-990721
// matches with g0 on ee-gcc2.9-991111-01, but that breaks other
// things
#if 1
INCLUDE_ASM("asm/kernel/nonmatchings/alarm", func_80002690);
#else
// timer 3 irq handler
void func_80002690()
{
    int i, aidx;
    u_int target;
    u_int gp;

    if (D_8001C230 >= 2) {
        *T3_MODE = 0x583;
        *T3_COMP = D_8001C238[D_8001C738[1]].target;
    } else {
        *T3_MODE = 0x483;
    }

    do {
        aidx = D_8001C738[0];

        D_8001C230--;

        for (i = 0; i < D_8001C230; i++) {
            D_8001C738[i] = D_8001C738[i + 1];
        }

        D_8001C228 &= ~(1ull << aidx);

        asm volatile("move %0, $gp \n" : "=r"(gp));
        asm volatile("move $gp, %0 \n" ::"r"(D_8001C238[aidx].gp));

        target = D_8001C238[aidx].target & 0xffff;
        func_800029C0(D_800174E4, D_8001C238[aidx].handler, aidx, target, D_8001C238[aidx].arg);

        asm volatile("move $gp, %0 \n" ::"r"(gp));
    } while (D_8001C230 > 0 && target == D_8001C238[aidx = D_8001C738[0]].target);
}
#endif

// AlarmCount
int func_80002828()
{
    return D_8001C230;
}

// InitAlarm
void func_80002838()
{
    int i;

    D_8001C230 = 0;
    D_8001C228 = 0;

    for (i = 0; i < 64; i++) {
        D_8001C738[i] = 0;
    }

    EnableIntc(INTC_TIM3);
}

INCLUDE_ASM("asm/kernel/nonmatchings/alarm", func_80002880);
