#ifndef EEREGS_H_
#define EEREGS_H_

// clang-format off
/** EE SIO Line Control Register */
#define R_EE_SIO_LCR    ((volatile u_int *)0xB000F100)
/** EE SIO Line Status Register */
#define R_EE_SIO_LSR    ((volatile u_int *)0xB000F110)
/** EE SIO Interrupt Enable Register */
#define R_EE_SIO_IER    ((volatile u_int *)0xB000F120)
/** EE SIO Interrupt Status Register */
#define R_EE_SIO_ISR    ((volatile u_int *)0xB000F130)
/** EE SIO FIFO Control Register */
#define R_EE_SIO_FCR    ((volatile u_int *)0xB000F140)
/** EE SIO Baud Rate Control Register */
#define R_EE_SIO_BRC    ((volatile u_int *)0xB000F150)
/** Unknown SIO Register 0x60 */
#define R_EE_SIO_REG60  ((volatile u_char *)0xB000F160)
/** Unknown SIO Register 0x70 */
#define R_EE_SIO_REG70  ((volatile u_char *)0xB000F170)
/** Transfer Holding Register */
#define R_EE_SIO_TXFIFO ((volatile u_char *)0xB000F180)
/** Unknown SIO Register 0x90 */
#define R_EE_SIO_REG90  ((volatile u_char *)0xB000F190)
/** Unknown SIO Register 0xA0 */
#define R_EE_SIO_REGA0  ((volatile u_char *)0xB000F1A0)
/** Unknown SIO Register 0xB0 */
#define R_EE_SIO_REGB0  ((volatile u_char *)0xB000F1B0)
/** Recieve Buffer Register */
#define R_EE_SIO_RXFIFO ((volatile u_char *)0xB000F1C0)

#define R_EE_SBUS_MSFLAG ((volatile u_int *)0xB000F220)
#define R_EE_SBUS_SMFLAG ((volatile u_int *)0xB000F230)
#define R_EE_SBUS_STAT   ((volatile u_int *)0xB000F240)

#define wmb() do {asm volatile("":::"memory");} while(0)
// clang-format on

#endif // EEREGS_H_
