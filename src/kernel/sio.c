#include "common.h"
#include "eeregs.h"

// sio putc
char func_80015700(char c)
{
    while ((*SIO_ISR & 0xf000) == 0x8000)
        ;

    *SIO_TXFIFO = c;

    return c;
}

// sio status
void func_80015748()
{
    u_int isr = *SIO_ISR;
    u_int lsr;

    if (isr & 4) {
        lsr = *SIO_LSR;
        if (lsr & 8) {
            kprintf("UART: Frame error.");
        } else if (lsr & 4) {
            kprintf("UART: Parity error.");
        } else if (lsr & 2) {
            kprintf("UART: Overrun error.");
        }

        *SIO_LSR = 0xe;
    }

    while (*SIO_ISR & 0xf00) {
        *SIO_RXFIFO;
    }

    *SIO_ISR = 7;
}

// PIF puts
void func_80015838(char* s)
{
    volatile struct pif_reg* pif = PIFREG;
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
