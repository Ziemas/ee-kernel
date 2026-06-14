#ifndef INTR_H_
#define INTR_H_

int func_80000700(int, void*);
int func_80000780(int, void*);
int EnableIntc(int);
int DisableIntc(int);
int EnableDmac(int);
int DisableDmac(int);

#endif // INTR_H_
