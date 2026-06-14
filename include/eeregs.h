#ifndef EEREGS_H_
#define EEREGS_H_

// clang-format off
/** EE SIO Line Control Register */
#define SIO_LCR    ((volatile u_int *)0xB000F100)
/** EE SIO Line Status Register */
#define SIO_LSR    ((volatile u_int *)0xB000F110)
/** EE SIO Interrupt Enable Register */
#define SIO_IER    ((volatile u_int *)0xB000F120)
/** EE SIO Interrupt Status Register */
#define SIO_ISR    ((volatile u_int *)0xB000F130)
/** EE SIO FIFO Control Register */
#define SIO_FCR    ((volatile u_int *)0xB000F140)
/** EE SIO Baud Rate Control Register */
#define SIO_BRC    ((volatile u_int *)0xB000F150)
/** Unknown SIO Register 0x60 */
#define SIO_REG60  ((volatile u_char *)0xB000F160)
/** Unknown SIO Register 0x70 */
#define SIO_REG70  ((volatile u_char *)0xB000F170)
/** Transfer Holding Register */
#define SIO_TXFIFO ((volatile u_char *)0xB000F180)
/** Unknown SIO Register 0x90 */
#define SIO_REG90  ((volatile u_char *)0xB000F190)
/** Unknown SIO Register 0xA0 */
#define SIO_REGA0  ((volatile u_char *)0xB000F1A0)
/** Unknown SIO Register 0xB0 */
#define SIO_REGB0  ((volatile u_char *)0xB000F1B0)
/** Recieve Buffer Register */
#define SIO_RXFIFO ((volatile u_char *)0xB000F1C0)

#define SBUS_MSFLAG ((volatile u_int *)0xB000F220)
#define SBUS_SMFLAG ((volatile u_int *)0xB000F230)
#define SBUS_STAT   ((volatile u_int *)0xB000F240)

#define T0_COUNT    ((volatile u_int *)(0xB0000000))
#define T0_MODE     ((volatile u_int *)(0xB0000010))
#define T0_COMP     ((volatile u_int *)(0xB0000020))
#define T0_HOLD     ((volatile u_int *)(0xB0000030))
#define T1_COUNT    ((volatile u_int *)(0xB0000800))
#define T1_MODE     ((volatile u_int *)(0xB0000810))
#define T1_COMP     ((volatile u_int *)(0xB0000820))
#define T1_HOLD     ((volatile u_int *)(0xB0000830))
#define T2_COUNT    ((volatile u_int *)(0xB0001000))
#define T2_MODE     ((volatile u_int *)(0xB0001010))
#define T2_COMP     ((volatile u_int *)(0xB0001020))
#define T3_COUNT    ((volatile u_int *)(0xB0001800))
#define T3_MODE     ((volatile u_int *)(0xB0001810))
#define T3_COMP     ((volatile u_int *)(0xB0001820))

#define wmb() do {asm volatile("":::"memory");} while(0)
// clang-format on

#endif // EEREGS_H_
