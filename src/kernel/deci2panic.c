#include "common.h"

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
