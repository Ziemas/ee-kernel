#include "common.h"

struct deci2_socket {
    u_short proto;
    u_short unk;
    void* opt;
    void* handler;
};

struct d2_cause_string {
    int id;
    const char* string;
};

const struct d2_cause_string deci2_err_cause[6] = {
    { 1, "MAN" },
    { 2, "SIF" },
    { 3, "DCMP" },
    { 4, "RLY" },
    { 5, "KTTY" },
    { 6, "DBG" },
};

extern struct deci2_socket D_80028BB0[16];

void func_80015838(const char* s);

// deci2_panic
void func_8000FE18(int cause, char* msg)
{
    u_int i;

    for (i = 0; i < 6; i++) {
        if (cause == deci2_err_cause[i].id) {
            break;
        }
    }
    func_80015838("\n# EE DECI2 Panic!!!\n\t");
    func_80015838(deci2_err_cause[i].string);
    func_80015838(": ");
    func_80015838(msg);
    func_80015838("\n");

    while (1)
        ;
}

int func_8000FEC8(int sock)
{
    if (sock <= 0 || sock > 16) {
        return 0;
    }

    if (D_80028BB0[sock].proto) {
        return 1;
    }

    return 0;
}

INCLUDE_ASM("asm/kernel/nonmatchings/deci2", func_8000FF00);

INCLUDE_ASM("asm/kernel/nonmatchings/deci2", func_8000FF08);

INCLUDE_ASM("asm/kernel/nonmatchings/deci2", func_8000FF50);

INCLUDE_ASM("asm/kernel/nonmatchings/deci2", func_80010048);

INCLUDE_ASM("asm/kernel/nonmatchings/deci2", func_80010160);

INCLUDE_ASM("asm/kernel/nonmatchings/deci2", func_80010218);

INCLUDE_ASM("asm/kernel/nonmatchings/deci2", func_80010268);

INCLUDE_ASM("asm/kernel/nonmatchings/deci2", func_800102E0);

INCLUDE_ASM("asm/kernel/nonmatchings/deci2", func_80010330);

INCLUDE_ASM("asm/kernel/nonmatchings/deci2", func_800104B0);

INCLUDE_ASM("asm/kernel/nonmatchings/deci2", func_80010530);

INCLUDE_ASM("asm/kernel/nonmatchings/deci2", func_800105B8);

INCLUDE_ASM("asm/kernel/nonmatchings/deci2", func_800106A8);

INCLUDE_ASM("asm/kernel/nonmatchings/deci2", func_80010800);

INCLUDE_ASM("asm/kernel/nonmatchings/deci2", func_80010860);

INCLUDE_ASM("asm/kernel/nonmatchings/deci2", func_800108B8);

INCLUDE_ASM("asm/kernel/nonmatchings/deci2", func_80010960);

INCLUDE_ASM("asm/kernel/nonmatchings/deci2", func_80010A50);

INCLUDE_ASM("asm/kernel/nonmatchings/deci2", func_80010AB8);

INCLUDE_ASM("asm/kernel/nonmatchings/deci2", func_80010B40);

INCLUDE_RODATA("asm/kernel/nonmatchings/deci2", D_80018AD0);

INCLUDE_RODATA("asm/kernel/nonmatchings/deci2", D_80018AE0);

INCLUDE_ASM("asm/kernel/nonmatchings/deci2", func_80010B48);

INCLUDE_ASM("asm/kernel/nonmatchings/deci2", func_80010E28);

INCLUDE_ASM("asm/kernel/nonmatchings/deci2", func_80010E48);

INCLUDE_ASM("asm/kernel/nonmatchings/deci2", func_80010ED0);

INCLUDE_ASM("asm/kernel/nonmatchings/deci2", func_80010F40);

INCLUDE_ASM("asm/kernel/nonmatchings/deci2", func_80011108);

INCLUDE_ASM("asm/kernel/nonmatchings/deci2", func_800111E8);

INCLUDE_RODATA("asm/kernel/nonmatchings/deci2", D_80018BD8);

INCLUDE_RODATA("asm/kernel/nonmatchings/deci2", D_80018BF8);

INCLUDE_RODATA("asm/kernel/nonmatchings/deci2", D_80018C08);

INCLUDE_RODATA("asm/kernel/nonmatchings/deci2", D_80018C18);

INCLUDE_RODATA("asm/kernel/nonmatchings/deci2", D_80018C28);

INCLUDE_RODATA("asm/kernel/nonmatchings/deci2", D_80018C40);

INCLUDE_RODATA("asm/kernel/nonmatchings/deci2", D_80018C58);
