#ifndef COMMON_H_
#define COMMON_H_

#include "include_asm.h"

typedef unsigned char		u_char;
typedef unsigned short		u_short;
typedef unsigned int		u_int;
typedef unsigned long		u_long;

#define PIFREG ((volatile struct pif_reg *)0xbf803800)

struct pif_reg {
	/* 0x00 */ u_short board_id;
	/* 0x02 */ u_short unk2;
	/* 0x04 */ u_short rcv_state;
	/* 0x06 */ u_short unk6;
	/* 0x08 */ u_short cpr;
	/* 0x0a */ u_short unkA;
	/* 0x0c */ u_short com_send;
	/* 0x0e */ u_short unkE;
	/* 0x10 */ u_short fifo_stat;
	/* 0x12 */ u_short unk12;
	/* 0x14 */ u_short tx_count;
	/* 0x16 */ u_short unk16;
	/* 0x18 */ u_short rx_count;
	/* 0x1a */ u_short unk1A;
	/* 0x1c */ u_short unk1C;
	/* 0x1e */ u_short unk1E;
	/* 0x20 */ u_short unk20;
	/* 0x22 */ u_short unk22;
	/* 0x24 */ u_short unk24;
	/* 0x26 */ u_short unk26;
	/* 0x28 */ u_short unk28;
	/* 0x2a */ u_short unk2A;
	/* 0x2c */ u_short unk2C;
	/* 0x2e */ u_short unk2E;
	/* 0x30 */ u_short unk30;
	/* 0x32 */ u_short unk32;
	/* 0x34 */ u_short dmactrl;
	/* 0x36 */ u_short unk36;
	/* 0x38 */ u_short unk38;
	/* 0x3a */ u_short unk3A;
	/* 0x3c */ u_short dma_slice_count;
	/* 0x3e */ u_short unk3E;
	/* 0x40 */ u_int fifo;
};

#endif // COMMON_H_
