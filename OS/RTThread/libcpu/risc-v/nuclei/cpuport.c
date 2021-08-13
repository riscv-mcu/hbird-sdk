/*
 * Copyright (c) 2006-2018, RT-Thread Development Team
 * Copyright (c) 2019-Present Nuclei Limited. All rights reserved.
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2020/03/26     Huaqi        Nuclei RISC-V Core porting code.
 * 2020/07/13     Huaqi        Adapt port for HummingBird E203.
 */

#include <rthw.h>
#include <rtthread.h>
#include <sys/types.h>
#include <unistd.h>

#include "cpuport.h"

#define SYSTICK_TICK_CONST          (SOC_TIMER_FREQ / RT_TICK_PER_SECOND)

#define portINITIAL_MSTATUS         ( MSTATUS_MPP | MSTATUS_MPIE | MSTATUS_FS_INITIAL)

#define SysTick_Handler             core_mtip_handler

void SysTick_Handler(void);

volatile rt_ubase_t  rt_interrupt_from_thread = 0;
volatile rt_ubase_t  rt_interrupt_to_thread   = 0;
volatile rt_ubase_t rt_thread_switch_interrupt_flag = 0;

struct rt_hw_stack_frame
{
    rt_ubase_t epc;        /* epc - epc    - program counter                     */
    rt_ubase_t ra;         /* x1  - ra     - return address for jumps            */
    rt_ubase_t t0;         /* x5  - t0     - temporary register 0                */
    rt_ubase_t t1;         /* x6  - t1     - temporary register 1                */
    rt_ubase_t t2;         /* x7  - t2     - temporary register 2                */
    rt_ubase_t s0_fp;      /* x8  - s0/fp  - saved register 0 or frame pointer   */
    rt_ubase_t s1;         /* x9  - s1     - saved register 1                    */
    rt_ubase_t a0;         /* x10 - a0     - return value or function argument 0 */
    rt_ubase_t a1;         /* x11 - a1     - return value or function argument 1 */
    rt_ubase_t a2;         /* x12 - a2     - function argument 2                 */
    rt_ubase_t a3;         /* x13 - a3     - function argument 3                 */
    rt_ubase_t a4;         /* x14 - a4     - function argument 4                 */
    rt_ubase_t a5;         /* x15 - a5     - function argument 5                 */
#ifndef __riscv_32e
    rt_ubase_t a6;         /* x16 - a6     - function argument 6                 */
    rt_ubase_t a7;         /* x17 - s7     - function argument 7                 */
    rt_ubase_t s2;         /* x18 - s2     - saved register 2                    */
    rt_ubase_t s3;         /* x19 - s3     - saved register 3                    */
    rt_ubase_t s4;         /* x20 - s4     - saved register 4                    */
    rt_ubase_t s5;         /* x21 - s5     - saved register 5                    */
    rt_ubase_t s6;         /* x22 - s6     - saved register 6                    */
    rt_ubase_t s7;         /* x23 - s7     - saved register 7                    */
    rt_ubase_t s8;         /* x24 - s8     - saved register 8                    */
    rt_ubase_t s9;         /* x25 - s9     - saved register 9                    */
    rt_ubase_t s10;        /* x26 - s10    - saved register 10                   */
    rt_ubase_t s11;        /* x27 - s11    - saved register 11                   */
    rt_ubase_t t3;         /* x28 - t3     - temporary register 3                */
    rt_ubase_t t4;         /* x29 - t4     - temporary register 4                */
    rt_ubase_t t5;         /* x30 - t5     - temporary register 5                */
    rt_ubase_t t6;         /* x31 - t6     - temporary register 6                */
#endif
    rt_ubase_t mstatus;    /*              - machine status register             */
};

/**
 * This function will initialize thread stack
 *
 * @param tentry the entry of thread
 * @param parameter the parameter of entry
 * @param stack_addr the beginning stack address
 * @param texit the function will be called when thread exit
 *
 * @return stack address
 */
rt_uint8_t *rt_hw_stack_init(void       *tentry,
                             void       *parameter,
                             rt_uint8_t *stack_addr,
                             void       *texit)
{
    struct rt_hw_stack_frame *frame;
    rt_uint8_t         *stk;
    int                i;

    stk  = stack_addr + sizeof(rt_ubase_t);
    stk  = (rt_uint8_t *)RT_ALIGN_DOWN((rt_ubase_t)stk, REGBYTES);
    stk -= sizeof(struct rt_hw_stack_frame);

    frame = (struct rt_hw_stack_frame *)stk;

    for (i = 0; i < sizeof(struct rt_hw_stack_frame) / sizeof(rt_ubase_t); i++)
    {
        ((rt_ubase_t *)frame)[i] = 0xdeadbeef;
    }

    frame->ra      = (rt_ubase_t)texit;
    frame->a0      = (rt_ubase_t)parameter;
    frame->epc     = (rt_ubase_t)tentry;

    frame->mstatus = portINITIAL_MSTATUS;

    return stk;
}

/*
 * void rt_hw_context_switch_interrupt(rt_ubase_t from, rt_ubase_t to);
 */
void rt_hw_context_switch_interrupt(rt_ubase_t from, rt_ubase_t to)
{
    if (rt_thread_switch_interrupt_flag == 0)
        rt_interrupt_from_thread = from;

    rt_interrupt_to_thread = to;
    rt_thread_switch_interrupt_flag = 1;
    portYIELD();
}

void rt_hw_context_switch(rt_ubase_t from, rt_ubase_t to)
{
    rt_hw_context_switch_interrupt(from, to);
}

/** shutdown CPU */
void rt_hw_cpu_shutdown()
{
    rt_uint32_t level;
    rt_kprintf("shutdown...\n");

    level = rt_hw_interrupt_disable();
    while (level)
    {
        RT_ASSERT(0);
    }
}

void xPortTaskSwitch( void )
{
    /* Clear Software IRQ, A MUST */
    SysTimer_ClearSWIRQ();
    rt_thread_switch_interrupt_flag = 0;
}

void vPortSetupTimerInterrupt( void )
{
    uint64_t ticks = SYSTICK_TICK_CONST;

    /* Initialize clint timer as OS tick interrupt, and enable timer interrupt */
    SysTick_Config(ticks);
    Interrupt_Register_CoreIRQ(SysTimer_IRQn, (unsigned long)SysTick_Handler);
    __enable_timer_irq();

    __enable_sw_irq();
}


#if defined(RT_USING_USER_MAIN) && defined(RT_USING_HEAP)
#define RT_HEAP_SIZE 1024
static uint32_t rt_heap[RT_HEAP_SIZE];  // heap default size: 4K(1024 * 4)
RT_WEAK void *rt_heap_begin_get(void)
{
    return rt_heap;
}

RT_WEAK void *rt_heap_end_get(void)
{
    return rt_heap + RT_HEAP_SIZE;
}
#endif

/**
 * This function will initial your board.
 */
void rt_hw_board_init()
{
    /* OS Tick Configuration */
    vPortSetupTimerInterrupt();

    /* Call components board initial (use INIT_BOARD_EXPORT()) */
#ifdef RT_USING_COMPONENTS_INIT
    rt_components_board_init();
#endif

#if defined(RT_USING_USER_MAIN) && defined(RT_USING_HEAP)
    rt_system_heap_init(rt_heap_begin_get(), rt_heap_end_get());
#endif

    __disable_irq();
}


/* This is the timer interrupt service routine. */
void SysTick_Handler(void)
{
    // Reload timer
    SysTick_Reload(SYSTICK_TICK_CONST);

    /* enter interrupt */
    rt_interrupt_enter();

    /* tick increase */
    rt_tick_increase();

    /* leave interrupt */
    rt_interrupt_leave();
}

extern ssize_t _write(int fd, const void* ptr, size_t len);

void rt_hw_console_output(const char *str)
{
    rt_size_t size = 0;

    size = rt_strlen(str);
    _write(STDOUT_FILENO, str, size);
}

extern ssize_t _read(int fd, void* ptr, size_t len);
char rt_hw_console_getchar(void)
{
    int ch = -1;
    _read(STDIN_FILENO, &ch, 1);
    return ch;
}

rt_base_t rt_hw_interrupt_disable(void)
{
    return __RV_CSR_READ_CLEAR(CSR_MSTATUS, MSTATUS_MIE);
}

void rt_hw_interrupt_enable(rt_base_t level)
{
    __RV_CSR_WRITE(CSR_MSTATUS, level);
}
