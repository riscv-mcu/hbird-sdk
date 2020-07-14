#include <stdio.h>
#include "ucos_ii.h"
#include "hbird_sdk_soc.h"
#include "os_cpu_port.h"

#ifndef configASSERT
	#define configASSERT( x )
	#define configASSERT_DEFINED 0
#else
	#define configASSERT_DEFINED 1
#endif

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
#define xPortSysTickHandler     core_mtip_handler

void xPortSysTickHandler( void );

/*
 * Start first task is a separate function so it can be tested in isolation.
 */
extern void prvPortStartFirstTask( void ) __attribute__ (( naked ));

/*
 * Used to catch tasks that attempt to return from their implementing function.
 */
static void prvTaskExitError( void );

/*-----------------------------------------------------------*/

/* Each task maintains its own interrupt status in the critical nesting
variable. */
static UBaseType_t uxCriticalNesting = 0xaaaaaaaa;


/*-----------------------------------------------------------*/
/*
 *********************************************************************************************************
 *                                        INITIALIZE A TASK'S STACK
 *
 * Description: This function is called by either OSTaskCreate() or OSTaskCreateExt() to initialize the
 *              stack frame of the task being created.  This function is highly processor specific.
 *
 * Arguments  : task          is a pointer to the task code
 *
 *              p_arg         is a pointer to a user supplied data area that will be passed to the task
 *                            when the task first executes.
 *
 *              p_tos         is a pointer to the top of stack.  It is assumed that 'ptos' points to
 *                            a 'free' entry on the task stack.  If OS_STK_GROWTH is set to 1 then
 *                            'ptos' will contain the HIGHEST valid address of the stack.  Similarly, if
 *                            OS_STK_GROWTH is set to 0, the 'ptos' will contains the LOWEST valid address
 *                            of the stack.
 *
 *              opt           specifies options that can be used to alter the behavior of OSTaskStkInit().
 *                            (see uCOS_II.H for OS_TASK_OPT_xxx).
 *
 * Returns    : Always returns the location of the new top-of-stack once the processor registers have
 *              been placed on the stack in the proper order.
 *
 * Note(s)    : (1) Interrupts are enabled when task starts executing.
 *
 *              (2) There is no need to save register x0 since it is a hard-wired zero.
 *
 *              (3) RISC-V calling convention register usage:
 *
 *                    +-------------+-------------+----------------------------------+
 *                    |  Register   |   ABI Name  | Description                      |
 *                    +-------------+-------------+----------------------------------+
 *                    |  x31 - x28  |   t6 - t3   | Temporaries                      |
 *                    +-------------+-------------+----------------------------------+
 *                    |  x27 - x18  |  s11 - s2   | Saved registers                  |
 *                    +-------------+-------------+----------------------------------+
 *                    |  x17 - x12  |   a7 - a2   | Function arguments               |
 *                    +-------------+-------------+----------------------------------+
 *                    |  x11 - x10  |   a1 - a0   | Function arguments/return values |
 *                    +-------------+-------------+----------------------------------+
 *                    |     x9      |     s1      | Saved register                   |
 *                    +-------------+-------------+----------------------------------+
 *                    |     x8      |    s0/fp    | Saved register/frame pointer     |
 *                    +-------------+-------------+----------------------------------+
 *                    |   x7 - x5   |   t2 - t0   | Temporaries                      |
 *                    +-------------+-------------+----------------------------------+
 *                    |     x4      |     tp      | Thread pointer                   |
 *                    +-------------+-------------+----------------------------------+
 *                    |     x3      |     gp      | Global pointer                   |
 *                    +-------------+-------------+----------------------------------+
 *                    |     x2      |     sp      | Stack pointer                    |
 *                    +-------------+-------------+----------------------------------+
 *                    |     x1      |     ra      | return address                   |
 *                    +-------------+-------------+----------------------------------+
 *                    |     x0      |    zero     | Hard-wired zero                  |
 *                    +-------------+-------------+----------------------------------+
 *
 * As per the standard RISC-V ABI pxTopcOfStack is passed in in a0, pxCode in
 * a1, and pvParameters in a2. The new top of stack is passed out in a0.
 *
 * The RISC-V context is saved rtos tasks in the following stack frame,
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
OS_STK *OSTaskStkInit (void (*task)(void *pd), void *pdata, OS_STK *ptos, INT16U opt)
{
    /* Simulate the stack frame as it would be created by a context switch
    interrupt. */
    // Force stack 8byte align for double floating point case
    OS_STK * pxTopOfStack = (OS_STK *)(((unsigned long)ptos) & (~(unsigned long)(portBYTE_ALIGNMENT-1)));

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
    *pxTopOfStack = ( StackType_t ) pdata;    /* X10/A0 */
    pxTopOfStack -= 6; /* X5 - X9 */
    *pxTopOfStack = ( StackType_t ) portTASK_RETURN_ADDRESS;    /* RA, X1 */

    pxTopOfStack --;
    *pxTopOfStack = ( ( StackType_t ) task ) ;    /* PC */

    return pxTopOfStack;
}

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

/*
 * See header file for description.
 */
void OSStartHighRdy (void)
{
    __disable_irq();
    /* Start the timer that generates the tick ISR.  Interrupts are disabled
    here already. */
    vPortSetupTimerInterrupt();

    /* Initialise the critical nesting count ready for the first task. */
    uxCriticalNesting = 0;

    /* Mark OSRunning to True */
    OSRunning = OS_TRUE;

#if (OS_CPU_HOOKS_EN > 0) && (OS_TASK_SW_HOOK_EN > 0)
    /* Call OSTaskSwHook */
    OSTaskSwHook();
#endif

    /* Start the first task. */
    prvPortStartFirstTask();

    /* Should never get here as the tasks will now be executing!  Call the task
    exit error function to prevent compiler warnings about a static function
    not being called in the case that the application writer overrides this
    functionality by defining configTASK_RETURN_ADDRESS.  */
    prvTaskExitError();

    /* Should not get here! */
    return;
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
    if ((x) == 0) {
        portDISABLE_INTERRUPTS();

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
#if (OS_CPU_HOOKS_EN > 0) && (OS_TASK_SW_HOOK_EN > 0)
    /* Call OSTaskSwHook */
    OSTaskSwHook();
#endif
    OSPrioCur = OSPrioHighRdy;
    OSTCBCur  = OSTCBHighRdy;
    portENABLE_INTERRUPTS();
}
/*-----------------------------------------------------------*/

/*
*********************************************************************************************************
*                                          SYS TICK HANDLER
*
* Description: Handle the system tick (SysTick) interrupt, which is used to generate the uC/OS-II tick
*              interrupt.
*
* Arguments  : None.
*
* Note(s)    : This function is defined with weak linking in 'riscv_hal_stubs.c' so that it can be
*              overridden by the kernel port with same prototype
*********************************************************************************************************
*/
void xPortSysTickHandler( void )
{
#if OS_CRITICAL_METHOD == 3u                   /* Allocate storage for CPU status register             */
    OS_CPU_SR cpu_sr;
#endif
    /* The SysTick runs at the lowest interrupt priority, so when this interrupt
    executes all interrupts must be unmasked.  There is therefore no need to
    save and then restore the interrupt mask value as its value is already
    known. */
    OS_ENTER_CRITICAL();
    SysTick_Reload(SYSTICK_TICK_CONST);
    OSIntEnter();                              /* Tell uC/OS-II that we are starting an ISR            */
    OS_EXIT_CRITICAL();

    OSTimeTick();                              /* Call uC/OS-II's OSTimeTick()                         */

    OSIntExit();                               /* Tell uC/OS-II that we are leaving the ISR            */
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
    Interrupt_Register_CoreIRQ(SysTimer_IRQn, (unsigned long)xPortSysTickHandler);
    __enable_timer_irq();

    __enable_sw_irq();
}
/*-----------------------------------------------------------*/
