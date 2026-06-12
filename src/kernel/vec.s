#include "regnames.h"

    .set noat
    .set noreorder
    .section .text
    .global vectors
vectors:

    .org 0x000
    /* TLB REFILL */
    lui        k0, %hi(t9_backup)
    sd         t9, %lo(t9_backup)(k0)
    mfc0       t9, cause
    lui        k0, %hi(exc_handler)
    andi       t9, t9, 0x7C
    addu       k0, k0, t9
    lw         k0, %lo(exc_handler)(k0)
    lui        t9, %hi(t9_backup)
    jr         k0
    ld         t9, %lo(t9_backup)(t9)

    .org 0x080
    /* COUNTER */
    j          func_800161BC
    nop

    .org 0x100
    /* DEBUG */
    j          func_800161BC
    nop

    .org 0x180
    /* COMMON */
    lui        k0, %hi(t9_backup)
    sd         t9, %lo(t9_backup)(k0)
    mfc0       t9, cause
    lui        k0, %hi(exc_handler)
    andi       t9, t9, 0x7C
    addu       k0, k0, t9
    lw         k0, %lo(exc_handler)(k0)
    lui        t9, %hi(t9_backup)
    jr         k0
    ld         t9, %lo(t9_backup)(t9)

    .org 0x200
    /* INTERRUPT */
    lui        k0, %hi(func_80001100)
    sq         sp, %lo(func_80001100)(k0)
    sq         ra, %lo(D_80001110)(k0)
    sq         at, %lo(D_80001120)(k0)
    mfc0       at, cause
    mfc0       k0, status
    and        at, at, k0
    srl        at, at, 8
    andi       at, at, 0xFF
    plzcw      k0, at
    andi       k0, k0, 0xFF
    addiu      at, zero, 0x1E
    subu       at, at, k0
    sll        at, at, 2
    lui        k0, %hi(irq_handler)
    addu       k0, k0, at
    lw         k0, %lo(irq_handler)(k0)
    jr         k0
    nop

    .org 0x280
    /* SYSCALL */
    /* $v1 = syscall number */

    // negative syscalls
    bltzl      v1, 2f // if syscall negative
    negu       v1, v1 // negate it

    // syscall number 0x7c is deic2call
    addiu      k0, zero, 0x7C
    bne        k0, v1, 1f
    nop
    j          func_8001625C // deci2call
    nop
1:
    lui        k0, %hi(func_80001100)
    sq         sp, %lo(func_80001100)(k0)
    sq         ra, %lo(D_80001110)(k0)
    sq         at, %lo(D_80001120)(k0)
    mfc0       at, status
    addiu      k0, zero, -0x1C
    and        at, at, k0
    mtc0       at, status
    sync.p
    daddu      k0, sp, zero
    lui        sp, %hi(D_8001B400)
    addiu      sp, sp, %lo(D_8001B400)
    addiu      sp, sp, -0x10
    sw         ra, 0x0(sp)
    sw         k0, 0x4(sp)
    mfc0       k0, epc
    addiu      k0, k0, 0x4
    sw         k0, 0x8(sp)
    mtc0       k0, epc
    sync.p
    sll        v1, v1, 2
    lui        k0, %hi(syscall_handler)
    addu       k0, k0, v1
    lw         k0, %lo(syscall_handler)(k0)
    jalr       k0
     nop
    lw         k0, 0x8(sp)
    lw         ra, 0x0(sp)
    lw         sp, 0x4(sp)
    mtc0       k0, epc
    sync.p
    mfc0       k0, status
    ori        k0, k0, 0x13
    mtc0       k0, status
    sync.p
    eret
2:
    addiu      sp, sp, -0x10
    sw         ra, 0x0(sp)
    mfc0       k0, epc
    addiu      k0, k0, 0x4
    sw         k0, 0x4(sp)
    mtc0       k0, epc
    sync.p
    sll        v1, v1, 2
    lui        k0, %hi(syscall_handler)
    addu       k0, k0, v1
    lw         k0, %lo(syscall_handler)(k0)
    jalr       k0
     nop
    lw         k0, 0x4(sp)
    lw         ra, 0x0(sp)
    addiu      sp, sp, 0x10
    mtc0       k0, epc
    sync.p
    eret

    // hack for now
    .org 0x380
