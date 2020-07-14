/*
 * FreeRTOS Kernel V10.2.1
 * Copyright (C) 2019 Amazon.com, Inc. or its affiliates.  All Rights Reserved.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy of
 * this software and associated documentation files (the "Software"), to deal in
 * the Software without restriction, including without limitation the rights to
 * use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of
 * the Software, and to permit persons to whom the Software is furnished to do so,
 * subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
 * FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
 * COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
 * IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 *
 * http://www.FreeRTOS.org
 * http://aws.amazon.com/freertos
 *
 * 1 tab == 4 spaces!
 */

/*-----------------------------------------------------------
 * Implementation of functions defined in portable.h for the HummingBird E200x port.
 *----------------------------------------------------------*/

/* Scheduler includes. */
#include <stdio.h>
#include "FreeRTOS.h"
#include "task.h"

#ifndef configSYSTICK_CLOCK_HZ
    #define configSYSTICK_CLOCK_HZ                  SOC_TIMER_FREQ
#endif

#define SYSTICK_TICK_CONST          (configSYSTICK_CLOCK_HZ / configTICK_RATE_HZ)

/* Constants required to set up the initial stack. */
#define portINITIAL_MSTATUS         ( MSTATUS_MPP | MSTATUS_MPIE | MSTATUS_FS_INITIAL)
#define portINITIAL_EXC_RETURN      ( 0xfffffffd )

/* Let the user override the pre-loading of the initial LR with the address of
prvTaskExitError() in case it messes up unwinding of the stack in the
debugger. */
#ifdef configTASK_RETURN_ADDRESS
    #define portTASK_RETURN_ADDRESS configTASK_RETURN_ADDRESS
#else
    #define portTASK_RETURN_ADDRESS prvTaskExitError
#endif

/*
 * Setup the timer to generate the tick interrupts.  The implementation in this
 * file is weak to allow application writers to change the timer used to
 * generate the tick interrupt.
 */
void vPortSetupTimerInterrupt( void );

/*
 * Exception handlers.
 */
void xPortSysTickHandler( void );

/*
 * Start first task is a separate function so it can be tested in isolation.
 */
extern void prvPortStartFirstTask( void ) __attribute__ (( naked ));

/*
 * Used to catch tasks that attempt to return from their implementing function.
 */
static void prvTaskExitError( void );

#define xPortSysTickHandler     core_mtip_handler

/*-----------------------------------------------------------*/

/* Each task maintains its own interrupt status in the critical nesting
variable. */
static UBaseType_t uxCriticalNesting = 0xaaaaaaaa;

/*-----------------------------------------------------------*/

/*
 * See header file for description.
 * As per the standard RISC-V ABI pxTopcOfStack is passed in in a0, pxCode in
 * a1, and pvParameters in a2.  The new top of stack is passed out in a0.
 *
 * RISC-V maps registers to ABI names as follows (X1 to X31 integer registers
 * for the 'I' profile, X1 to X15 for the 'E' profile, currently I assumed).
 *
 * Register        ABI Name    Description                         Saver
 * x0              zero        Hard-wired zero                     -
 * x1              ra          Return address                      Caller
 * x2              sp          Stack pointer                       Callee
 * x3              gp          Global pointer                      -
 * x4              tp          Thread pointer                      -
 * x5-7            t0-2        Temporaries                         Caller
 * x8              s0/fp       Saved register/Frame pointer        Callee
 * x9              s1          Saved register                      Callee
 * x10-11          a0-1        Function Arguments/return values    Caller
 * x12-17          a2-7        Function arguments                  Caller
 * x18-27          s2-11       Saved registers                     Callee
 * x28-31          t3-6        Temporaries                         Caller
 *
 * The RISC-V context is saved RTOS tasks in the following stack frame,
 * where the global and thread pointers are currently assumed to be constant so
 * are not saved:
 *
 * mstatus
 * #ifndef __riscv_32e
 * x31
 * x30
 * x29
 * x28
 * x27
 * x26
 * x25
 * x24
 * x23
 * x22
 * x21
 * x20
 * x19
 * x18
 * x17
 * x16
 * #endif
 * x15
 * x14
 * x13
 * x12
 * x11
 * pvParameters
 * x9
 * x8
 * x7
 * x6
 * x5
 * portTASK_RETURN_ADDRESS
 * pxCode
 */
StackType_t *pxPortInitialiseStack( StackType_t *pxTopOfStack, TaskFunction_t pxCode, void *pvParameters )
{
    /* Simulate the stack frame as it would be created by a context switch
    interrupt. */

    /* Offset added to account for the way the MCU uses the stack on entry/exit
    of interrupts, and to ensure alignment. */
    pxTopOfStack--;
    *pxTopOfStack = portINITIAL_MSTATUS;    /* MSTATUS */

    /* Save code space by skipping register initialisation. */
#ifndef __riscv_32e
    pxTopOfStack -= 22;    /* X11 - X31. */
#else
    pxTopOfStack -= 6;    /* X11 - X15. */
#endif
    *pxTopOfStack = ( StackType_t ) pvParameters;    /* X10/A0 */
    pxTopOfStack -= 6; /* X5 - X9 */
    *pxTopOfStack = ( StackType_t ) portTASK_RETURN_ADDRESS;    /* RA, X1 */

    pxTopOfStack --;
    *pxTopOfStack = ( ( StackType_t ) pxCode ) ;    /* PC */

    return pxTopOfStack;
}
/*-----------------------------------------------------------*/

static void prvTaskExitError( void )
{
    volatile uint32_t ulDummy = 0;

    /* A function that implements a task must not exit or attempt to return to
    its caller as there is nothing to return to.  If a task wants to exit it
    should instead call vTaskDelete( NULL ).

    Artificially force an assert() to be triggered if configASSERT() is
    defined, then stop here so application writers can catch the error. */
    configASSERT( uxCriticalNesting == ~0UL );
    portDISABLE_INTERRUPTS();
    while( ulDummy == 0 )
    {
        /* This file calls prvTaskExitError() after the scheduler has been
        started to remove a compiler warning about the function being defined
        but never called.  ulDummy is used purely to quieten other warnings
        about code appearing after this function is called - making ulDummy
        volatile makes the compiler think the function could return and
        therefore not output an 'unreachable code' warning for code that appears
        after it. */
        /* Sleep and wait for interrupt */
        __WFI();
    }
}
/*-----------------------------------------------------------*/

/*
 * See header file for description.
 */
BaseType_t xPortStartScheduler( void )
{
    __disable_irq();
    /* Start the timer that generates the tick ISR.  Interrupts are disabled
    here already. */
    vPortSetupTimerInterrupt();

    /* Initialise the critical nesting count ready for the first task. */
    uxCriticalNesting = 0;

    /* Start the first task. */
    prvPortStartFirstTask();

    /* Should never get here as the tasks will now be executing!  Call the task
    exit error function to prevent compiler warnings about a static function
    not being called in the case that the application writer overrides this
    functionality by defining configTASK_RETURN_ADDRESS.  Call
    vTaskSwitchContext() so link time optimisation does not remove the
    symbol. */
    vTaskSwitchContext();
    prvTaskExitError();

    /* Should not get here! */
    return 0;
}
/*-----------------------------------------------------------*/

void vPortEndScheduler( void )
{
    /* Not implemented in ports where there is nothing to return to.
    Artificially force an assert. */
    configASSERT( uxCriticalNesting == 1000UL );
}
/*-----------------------------------------------------------*/

void vPortEnterCritical( void )
{
    portDISABLE_INTERRUPTS();
    uxCriticalNesting++;
}
/*-----------------------------------------------------------*/

void vPortExitCritical( void )
{
    configASSERT( uxCriticalNesting );
    uxCriticalNesting--;
    if( uxCriticalNesting == 0 )
    {
        portENABLE_INTERRUPTS();
    }
}
/*-----------------------------------------------------------*/

void vPortAssert( int32_t x )
{
    TaskHandle_t th;
    if ((x) == 0) {
        taskDISABLE_INTERRUPTS();
#if (INCLUDE_xTaskGetCurrentTaskHandle == 1)
        th = xTaskGetCurrentTaskHandle();
        if (th) {
            printf("Assert in task %s\n", pcTaskGetName(th));
        }
#endif
        while(1) {
            /* Sleep and wait for interrupt */
            __WFI();
        };
    }
}
/*-----------------------------------------------------------*/


void xPortTaskSwitch( void )
{
    portDISABLE_INTERRUPTS();
    /* Clear Software IRQ, A MUST */
    SysTimer_ClearSWIRQ();
    vTaskSwitchContext();
    portENABLE_INTERRUPTS();
}
/*-----------------------------------------------------------*/

void xPortSysTickHandler( void )
{
    portDISABLE_INTERRUPTS();
    {
        SysTick_Reload(SYSTICK_TICK_CONST);
        /* Increment the RTOS tick. */
        if( xTaskIncrementTick() != pdFALSE )
        {
            /* A context switch is required.  Context switching is performed in
            the SWI interrupt.  Pend the SWI interrupt. */
            portYIELD();
        }
    }
    portENABLE_INTERRUPTS();
}
/*-----------------------------------------------------------*/

/*
 * Setup the systick timer to generate the tick interrupts at the required
 * frequency.
 */
__attribute__(( weak )) void vPortSetupTimerInterrupt( void )
{
    TickType_t ticks = SYSTICK_TICK_CONST;

    /* Initialize clint timer as OS tick interrupt, and enable timer interrupt */
    SysTick_Config(ticks);
    Interrupt_Register_CoreIRQ(SysTimer_IRQn, (unsigned long)(xPortSysTickHandler));
    __enable_timer_irq();

    __enable_sw_irq();
}
/*-----------------------------------------------------------*/
