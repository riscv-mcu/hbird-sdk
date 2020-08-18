/*
 * Copyright (c) 2019 Nuclei Limited. All rights reserved.
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Licensed under the Apache License, Version 2.0 (the License); you may
 * not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an AS IS BASIS, WITHOUT
 * WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
/******************************************************************************
 * \file     startup_hbird.S
 * \brief    Modified NMSIS HummingBird RISC-V Core based Core Device Startup File for
 *  HummingBird RISC-V evaluation SoC which support HummingBird RISC-V cores
 * \version  V1.00
 * \date     14. Jul 2020
 *
 ******************************************************************************/

#include "riscv_encoding.h"

    .section .init

    .globl _start
    .type _start,@function

/**
 * Reset Handler called on controller reset
 */
_start:
    /* ===== Startup Stage 1 ===== */
    /* Disable Global Interrupt */
    csrc CSR_MSTATUS, MSTATUS_MIE
    /* Disable all interrupts controlled by CSR MIE */
    csrw CSR_MIE, 0x0

    /* Initialize GP and Stack Pointer SP */
    .option push
    .option norelax
    la gp, __global_pointer$
    .option pop
    la sp, _sp

    /*
     * Set Trap Entry MTVEC to trap_entry
     */
    la t0, trap_entry
    csrw CSR_MTVEC, t0

    /* Direct Mode: All exceptions set pc to BASE. */
    csrc CSR_MTVEC, 0x3

    /* ===== Startup Stage 2 ===== */

#ifdef __riscv_flen
    /* Enable FPU */
    li t0, MSTATUS_FS
    csrs mstatus, t0
    csrw fcsr, x0
#endif

    /* ===== Startup Stage 3 ===== */
    /*
     * Load code section frm FLASH to ILM
     * when code LMA is different with VMA
     */
    la a0, _ilm_lma
    la a1, _ilm
    /* If the ILM phy-address same as the logic-address, then quit */
    beq a0, a1, 2f
    la a2, _eilm
    bgeu a1, a2, 2f

1:
    /* Load code section if necessary */
    lw t0, (a0)
    sw t0, (a1)
    addi a0, a0, 4
    addi a1, a1, 4
    bltu a1, a2, 1b
2:
    /* Load data section */
    la a0, _data_lma
    la a1, _data
    la a2, _edata
    bgeu a1, a2, 2f
1:
    lw t0, (a0)
    sw t0, (a1)
    addi a0, a0, 4
    addi a1, a1, 4
    bltu a1, a2, 1b
2:
    /* Clear bss section */
    la a0, __bss_start
    la a1, _end
    bgeu a0, a1, 2f
1:
    sw zero, (a0)
    addi a0, a0, 4
    bltu a0, a1, 1b
2:

    /*
     * Call vendor defined SystemInit to
     * initialize the micro-controller system
     */
    call SystemInit

    /* Call global constructors */
    la a0, __libc_fini_array
    call atexit
    /* Call C/C++ constructor start up code */
    call __libc_init_array

    /* do pre-init steps before main */
    call _premain_init
    /* ===== Call Main Function  ===== */
    /* argc = argv = 0 */
    li a0, 0
    li a1, 0

#ifdef RTOS_RTTHREAD
    // Call entry function when using RT-Thread
    call entry
#else
    call main
#endif
    /* do post-main steps after main */
    call _postmain_fini

1:
    j 1b
