/*
 * Copyright (c) 2009-2018 Arm Limited. All rights reserved.
 * Copyright (c) 2019 HBIRD Limited. All rights reserved.
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
 * @file     system_hbird.c
 * @brief    NMSIS HummingBird RISC-V Core Device Peripheral Access Layer Source File for
 *           HummingBird RISC-V evaluation SoC which support HummingBird RISC-V cores
 * @version  V1.00
 * @date     14. Jul 2020
 ******************************************************************************/
#include <stdint.h>
#include <stdio.h>
#include "hbird_sdk_hal.h"

/*----------------------------------------------------------------------------
  Define clocks
 *----------------------------------------------------------------------------*/
/* ToDo: add here your necessary defines for device initialization
         following is an example for different system frequencies */
#ifndef SYSTEM_CLOCK
#define SYSTEM_CLOCK    (80000000UL)
#endif

/**
 * \defgroup  NMSIS_Core_SystemConfig       System Device Configuration
 * \brief Functions for system and clock setup available in system_<device>.c.
 * \details
 * HummingBird provides a template file **system_Device.c** that must be adapted by
 * the silicon vendor to match their actual device. As a <b>minimum requirement</b>,
 * this file must provide:
 *  -  A device-specific system configuration function, \ref SystemInit.
 *  -  A global variable that contains the system frequency, \ref SystemCoreClock.
 *  -  Global c library \ref _premain_init and \ref _postmain_fini functions called right before and after calling main function.
 *  -  Vendor customized interrupt, exception handling code, see \ref NMSIS_Core_IntExcNMI_Handling
 *
 * The file configures the device and, typically, initializes the oscillator (PLL) that is part
 * of the microcontroller device. This file might export other functions or variables that provide
 * a more flexible configuration of the microcontroller system.
 *
 * And this file also provided common interrupt, exception exception handling framework template,
 * Silicon vendor can customize these template code as they want.
 *
 * \note Please pay special attention to the static variable \c SystemCoreClock. This variable might be
 * used throughout the whole system initialization and runtime to calculate frequency/time related values.
 * Thus one must assure that the variable always reflects the actual system clock speed.
 *
 * \attention
 * Be aware that a value stored to \c SystemCoreClock during low level initializaton (i.e. \c SystemInit()) might get
 * overwritten by C libray startup code and/or .bss section initialization.
 * Thus its highly recommended to call \ref SystemCoreClockUpdate at the beginning of the user \c main() routine.
 *
 * @{
 */

/*----------------------------------------------------------------------------
  System Core Clock Variable
 *----------------------------------------------------------------------------*/
/* ToDo: initialize SystemCoreClock with the system core clock frequency value
         achieved after system intitialization.
         This means system core clock frequency after call to SystemInit() */
/**
 * \brief      Variable to hold the system core clock value
 * \details
 * Holds the system core clock, which is the system clock frequency supplied to the SysTick
 * timer and the processor core clock. This variable can be used by debuggers to query the
 * frequency of the debug timer or to configure the trace clock speed.
 *
 * \attention
 * Compilers must be configured to avoid removing this variable in case the application
 * program is not using it. Debugging systems require the variable to be physically
 * present in memory so that it can be examined to configure the debugger.
 */
uint32_t SystemCoreClock = SYSTEM_CLOCK;  /* System Clock Frequency (Core Clock) */

/*----------------------------------------------------------------------------
  Clock functions
 *----------------------------------------------------------------------------*/

/**
 * \brief      Function to update the variable \ref SystemCoreClock
 * \details
 * Updates the variable \ref SystemCoreClock and must be called whenever the core clock is changed
 * during program execution. The function evaluates the clock register settings and calculates
 * the current core clock.
 */
void SystemCoreClockUpdate (void)            /* Get Core Clock Frequency */
{
    /* ToDo: add code to calculate the system frequency based upon the current
     *    register settings.
     * Note: This function can be used to retrieve the system core clock frequeny
     *    after user changed register settings.
     */
    SystemCoreClock = SYSTEM_CLOCK;
}

/**
 * \brief      Function to Initialize the system.
 * \details
 * Initializes the microcontroller system. Typically, this function configures the
 * oscillator (PLL) that is part of the microcontroller device. For systems
 * with a variable clock speed, it updates the variable \ref SystemCoreClock.
 * SystemInit is called from the file <b>startup<i>_device</i></b>.
 */
void SystemInit (void)
{
    /* ToDo: add code to initialize the system
     * Warn: do not use global variables because this function is called before
     * reaching pre-main. RW section maybe overwritten afterwards.
     */
    SystemCoreClock = SYSTEM_CLOCK;
}

/**
 * \defgroup  NMSIS_Core_IntExcNMI_Handling   Interrupt and Exception Handling
 * \brief Functions for interrupt, exception handle available in system_<device>.c.
 * \details
 * HBIRD provide a template for interrupt, exception handling. Silicon Vendor could adapat according
 * to their requirement. Silicon vendor could implement interface for different exception code and
 * replace current implementation.
 *
 * @{
 */
/** \brief Max exception handler number */
#define MAX_SYSTEM_EXCEPTION_NUM        11
/**
 * \brief      Store the exception handlers for each exception ID
 * \note
 * - This SystemExceptionHandlers are used to store all the handlers for all the exception codes RISC-V core provided.
 * - Exception code 0 - 11, totally 12 exceptions are mapped to SystemExceptionHandlers[0:11]
 */
static unsigned long SystemExceptionHandlers[MAX_SYSTEM_EXCEPTION_NUM];
static unsigned long SystemExtInterruptHandlers[__PLIC_INTNUM];
static unsigned long SystemCoreInterruptHandlers[10];

/**
 * \brief      Exception Handler Function Typedef
 * \note
 * This typedef is only used internal in this system_<Device>.c file.
 * It is used to do type conversion for registered exception handler before calling it.
 */
typedef void (*EXC_HANDLER) (unsigned long mcause, unsigned long sp);
typedef void (*INT_HANDLER) (unsigned long mcause, unsigned long sp);

static uint32_t core_exception_handler(unsigned long mcause, unsigned long sp);

/**
 * \brief      System Default Exception Handler
 * \details
 * This function provided a default exception handling code for all exception ids.
 * By default, It will just print some information for debug, Vendor can customize it according to its requirements.
 */
static void system_default_exception_handler(unsigned long mcause, unsigned long sp)
{
    /* TODO: Uncomment this if you have implement printf function */
    printf("Trap in Exception\r\n");
    printf("MCAUSE: 0x%lx\r\n", mcause);
    printf("MEPC  : 0x%lx\r\n", __RV_CSR_READ(CSR_MEPC));
    printf("MTVAL : 0x%lx\r\n", __RV_CSR_READ(CSR_MBADADDR));
    while(1);
}

/**
 * \brief      System Default Interrupt Handler
 * \details
 * This function provided a default interrupt handling code for all interrupt ids.
 */
static void system_default_interrupt_handler(unsigned long mcause, unsigned long sp)
{
    /* TODO: Uncomment this if you have implement printf function */
    printf("Trap in Interrupt\r\n");
    printf("MCAUSE: 0x%lx\r\n", mcause);
    printf("MEPC  : 0x%lx\r\n", __RV_CSR_READ(CSR_MEPC));
    printf("MTVAL : 0x%lx\r\n", __RV_CSR_READ(CSR_MBADADDR));
}

/**
 * \brief      Initialize all the default core exception handlers
 * \details
 * The core exception handler for each exception id will be initialized to \ref system_default_exception_handler.
 * \note
 * Called in \ref _init function, used to initialize default exception handlers for all exception IDs
 */
static void Exception_Init(void)
{
    for (int i = 0; i < MAX_SYSTEM_EXCEPTION_NUM; i++) {
        SystemExceptionHandlers[i] = (unsigned long)system_default_exception_handler;
    }
}

/**
 * \brief      Initialize all the default interrupt handlers
 * \details
 * The interrupt handler for each exception id will be initialized to \ref system_default_interrupt_handler.
 * \note
 * Called in \ref _init function, used to initialize default interrupt handlers for all interrupt IDs
 */
static void Interrupt_Init(void)
{
    int i;
    for (i = 0; i < __PLIC_INTNUM; i++) {
        SystemExtInterruptHandlers[i] = (unsigned long)system_default_interrupt_handler;
    }
    for (i = 0; i < 10; i++) {
        SystemCoreInterruptHandlers[i] = (unsigned long)system_default_interrupt_handler;
    }
}

/**
 * \brief       Register an exception handler for exception code EXCn
 * \details
 * * For EXCn < \ref MAX_SYSTEM_EXCEPTION_NUM, it will be registered into SystemExceptionHandlers[EXCn-1].
 * \param   EXCn    See \ref EXCn_Type
 * \param   exc_handler     The exception handler for this exception code EXCn
 */
void Exception_Register_EXC(uint32_t EXCn, unsigned long exc_handler)
{
    if ((EXCn < MAX_SYSTEM_EXCEPTION_NUM) && (EXCn >= 0)) {
        SystemExceptionHandlers[EXCn] = exc_handler;
    }
}

/**
 * \brief       Register an core interrupt handler for core interrupt number
 * \details
 * * For irqn <=  10, it will be registered into SystemCoreInterruptHandlers[irqn-1].
 * \param   irqn    See \ref IRQn
 * \param   int_handler     The core interrupt handler for this interrupt code irqn
 */
void Interrupt_Register_CoreIRQ(uint32_t irqn, unsigned long int_handler)
{
    if ((irqn <= 10) && (irqn >= 0)) {
        SystemCoreInterruptHandlers[irqn] = int_handler;
    }
}

/**
 * \brief       Register an external interrupt handler for plic external interrupt number
 * \details
 * * For irqn <= \ref __PLIC_INTNUM, it will be registered into SystemExtInterruptHandlers[irqn-1].
 * \param   irqn    See \ref IRQn
 * \param   int_handler     The external interrupt handler for this interrupt code irqn
 */
void Interrupt_Register_ExtIRQ(uint32_t irqn, unsigned long int_handler)
{
    if ((irqn <= __PLIC_INTNUM) && (irqn >= 0)) {
        SystemExtInterruptHandlers[irqn] = int_handler;
    }
}

/**
 * \brief       Get an core interrupt handler for core interrupt number
 * \param   irqn    See \ref IRQn
 * \return
 * The core interrupt handler for this interrupt code irqn
 */
unsigned long Interrupt_Get_CoreIRQ(uint32_t irqn)
{
    if ((irqn <= 10) && (irqn >= 0)) {
        return SystemCoreInterruptHandlers[irqn];
    }
    return 0;
}

/**
 * \brief       Get an external interrupt handler for external interrupt number
 * \param   irqn    See \ref IRQn
 * \return
 * The external interrupt handler for this interrupt code irqn
 */
unsigned long Interrupt_Get_ExtIRQ(uint32_t irqn)
{
    if ((irqn <= __PLIC_INTNUM) && (irqn >= 0)) {
        return SystemExtInterruptHandlers[irqn];
    }
    return 0;
}

/**
 * \brief       Get current exception handler for exception code EXCn
 * \details
 * * For EXCn < \ref MAX_SYSTEM_EXCEPTION_NUM, it will return SystemExceptionHandlers[EXCn-1].
 * \param   EXCn    See \ref EXCn_Type
 * \return  Current exception handler for exception code EXCn, if not found, return 0.
 */
unsigned long Exception_Get_EXC(uint32_t EXCn)
{
    if ((EXCn < MAX_SYSTEM_EXCEPTION_NUM) && (EXCn >= 0)) {
        return SystemExceptionHandlers[EXCn];
    } else {
        return 0;
    }
}

/**
 * \brief      Common trap entry
 * \details
 * This function provided a command entry for trap. Silicon Vendor could modify
 * this template implementation according to requirement.
 * \remarks
 * - RISCV provided common entry for all types of exception including exception and interrupt.
 *   This is proposed code template for exception entry function, Silicon Vendor could modify the implementation.
 * - If you want to register core exception handler, please use \ref Exception_Register_EXC
 * - If you want to register core interrupt handler, please use \ref Interrupt_Register_CoreIRQ
 * - If you want to register external interrupt handler, please use \ref Interrupt_Register_ExtIRQ
 */
uint32_t core_trap_handler(unsigned long mcause, unsigned long sp)
{
    if (mcause & MCAUSE_INTERRUPT) {
        INT_HANDLER int_handler = NULL;
        uint32_t irqn = (uint32_t)(mcause & 0X00000fff);
        if (irqn == IRQ_M_EXT) {
#if defined(__PLIC_PRESENT) && __PLIC_PRESENT == 1
            irqn = PLIC_ClaimInterrupt();
            if (irqn < __PLIC_INTNUM) {
                int_handler = (INT_HANDLER)(SystemExtInterruptHandlers[irqn]);
                if (int_handler != NULL) {
                    int_handler(mcause, sp);
                }
                PLIC_CompleteInterrupt(irqn);
            }
#endif
        } else {
            int_handler = (INT_HANDLER)(SystemCoreInterruptHandlers[irqn]);
            if (int_handler != NULL) {
                int_handler(mcause, sp);
            }
        }
        return 0;
    } else {
        return core_exception_handler(mcause, sp);
    }
}

/**
 * \brief      Common Exception handler entry
 * \details
 * This function provided a command entry for exception. Silicon Vendor could modify
 * this template implementation according to requirement.
 * \remarks
 * - RISCV provided common entry for all types of exception. This is proposed code template
 *   for exception entry function, Silicon Vendor could modify the implementation.
 * - For the core_exception_handler template, we provided exception register function \ref Exception_Register_EXC
 *   which can help developer to register your exception handler for specific exception number.
 */
static uint32_t core_exception_handler(unsigned long mcause, unsigned long sp)
{
    uint32_t EXCn = (uint32_t)(mcause & 0X00000fff);
    EXC_HANDLER exc_handler;

    if ((EXCn < MAX_SYSTEM_EXCEPTION_NUM) && (EXCn >= 0)) {
        exc_handler = (EXC_HANDLER)SystemExceptionHandlers[EXCn];
    } else {
        exc_handler = (EXC_HANDLER)system_default_exception_handler;
    }
    if (exc_handler != NULL) {
        exc_handler(mcause, sp);
    }
    return 0;
}
/** @} */ /* End of Doxygen Group NMSIS_Core_ExceptionAndNMI */

/** Banner Print for HummingBird SDK */
void SystemBannerPrint(void)
{
#if defined(HBIRD_BANNER) && (HBIRD_BANNER == 1)
    printf("HummingBird SDK Build Time: %s, %s\r\n", __DATE__, __TIME__);
#ifdef DOWNLOAD_MODE_STRING
    printf("Download Mode: %s\r\n", DOWNLOAD_MODE_STRING);
#endif
    printf("CPU Frequency %lu Hz\r\n", SystemCoreClock);
#endif
}

/**
 * \brief  Register a riscv core interrupt and register the handler
 * \details
 * This function set interrupt handler for core interrupt
 * \param [in]  irqn        interrupt number
 * \param [in]  handler     interrupt handler, if NULL, handler will not be installed
 * \return       -1 means invalid input parameter. 0 means successful.
 * \remarks
 * - This function use to configure riscv core interrupt and register its interrupt handler and enable its interrupt.
 */
int32_t Core_Register_IRQ(uint32_t irqn, void *handler)
{
    if ((irqn > 10)) {
        return -1;
    }

    if (handler != NULL) {
        /* register interrupt handler entry to core handlers */
        Interrupt_Register_CoreIRQ(irqn, (unsigned long)handler);
    }
    switch (irqn) {
        case SysTimerSW_IRQn:
            __enable_sw_irq();
            break;
        case SysTimer_IRQn:
            __enable_timer_irq();
            break;
        default:
            break;
    }

    return 0;
}

#if defined(__PLIC_PRESENT) && __PLIC_PRESENT == 1
/**
 * \brief  Register a specific plic interrupt and register the handler
 * \details
 * This function set priority and handler for plic interrupt
 * \param [in]  source      interrupt source
 * \param [in]  priority    interrupt priority
 * \param [in]  handler     interrupt handler, if NULL, handler will not be installed
 * \return       -1 means invalid input parameter. 0 means successful.
 * \remarks
 * - This function use to configure specific plic interrupt and register its interrupt handler and enable its interrupt.
 */
int32_t PLIC_Register_IRQ(uint32_t source, uint8_t priority, void *handler)
{
    if ((source >= __PLIC_INTNUM)) {
        return -1;
    }

    /* set interrupt priority */
    PLIC_SetPriority(source, priority);
    if (handler != NULL) {
        /* register interrupt handler entry to external handlers */
        Interrupt_Register_ExtIRQ(source, (unsigned long)handler);
    }
    /* enable interrupt */
    PLIC_EnableInterrupt(source);
    __enable_ext_irq();
    return 0;
}
#endif
/** @} */ /* End of Doxygen Group NMSIS_Core_ExceptionAndNMI */

/**
 * \brief early init function before main
 * \details
 * This function is executed right before main function.
 * For RISC-V gnu toolchain, _init function might not be called
 * by __libc_init_array function, so we defined a new function
 * to do initialization
 */
void _premain_init(void)
{
    /* TODO: Add your own initialization code here, called before main */
    SystemCoreClock = get_cpu_freq();
#if ! defined(SIMULATION_SPIKE) && ! defined(SIMULATION_XLSPIKE)
    gpio_iof_config(GPIO, IOF0_UART0_MASK, IOF_SEL_0);
    uart_init(SOC_DEBUG_UART, 115200);
#endif
    /* Display banner after UART initialized */
    SystemBannerPrint();
    /* Initialize exception default handlers */
    Exception_Init();
    /* Initialize Interrupt default handlers */
    Interrupt_Init();
#if defined(__PLIC_PRESENT) && __PLIC_PRESENT == 1
    /* PLIC initilization */
    PLIC_Init(__PLIC_INTNUM);
#endif
}

/**
 * \brief finish function after main
 * \details
 * This function is executed right after main function.
 * For RISC-V gnu toolchain, _fini function might not be called
 * by __libc_fini_array function, so we defined a new function
 * to do initialization
 */
void _postmain_fini(int status)
{
    /* TODO: Add your own finishing code here, called after main */
#ifdef SIMULATION_XLSPIKE
extern void xlspike_exit(int status);
    xlspike_exit(status);
#endif
#ifdef SIMULATION_SPIKE
extern void spike_exit(int status);
    spike_exit(status);
#endif
}

/**
 * \brief _init function used in __libc_init_array()
 * \details
 * This __libc_init_array() function is called during startup code,
 * user need to implement this function, otherwise when link it will
 * error init.c:(.text.__libc_init_array+0x26): undefined reference to `_init'
 * \note
 * Please use \ref _premain_init function now
 */
void _init(void)
{
    /* Don't put any code here, please use _premain_init now */
}

/**
 * \brief _fini function used in __libc_fini_array()
 * \details
 * This __libc_fini_array() function is called when exit main.
 * user need to implement this function, otherwise when link it will
 * error fini.c:(.text.__libc_fini_array+0x28): undefined reference to `_fini'
 * \note
 * Please use \ref _postmain_fini function now
 */
void _fini(void)
{
    /* Don't put any code here, please use _postmain_fini now */

}

/** @} */ /* End of Doxygen Group NMSIS_Core_SystemAndClock */
