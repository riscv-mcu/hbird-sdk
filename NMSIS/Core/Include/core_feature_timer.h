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
#ifndef __CORE_FEATURE_TIMER_H__
#define __CORE_FEATURE_TIMER_H__
/*!
 * @file     core_feature_timer.h
 * @brief    CLINT Timer feature API header file for RISC-V Core
 */
/*
 * CLINT Timer Feature Configuration Macro:
 * 1. __SYSTIMER_PRESENT:  Define whether Private CLINT Timer is present or not.
 *   * 0: Not present
 *   * 1: Present
 * 2. __SYSTIMER_BASEADDR:  Define the base address of the CLINT Timer.
 */
#ifdef __cplusplus
 extern "C" {
#endif

#if defined(__SYSTIMER_PRESENT) && (__SYSTIMER_PRESENT == 1)
/**
 * \defgroup NMSIS_Core_SysTimer_Registers     Register Define and Type Definitions Of System Timer
 * \ingroup NMSIS_Core_Registers
 * \brief   Type definitions and defines for system timer registers.
 *
 * @{
 */
/**
 * \brief  Structure type to access the System Timer (SysTimer).
 * \details
 * Structure definition to access the system timer(SysTimer).
 * \remarks
 */
typedef struct {
    __IOM uint32_t MSIP;                    /*!< Offset: 0x000 (R/W)  System Timer SW interrupt Register */
    __IOM uint32_t RESERVED0[0xFFF];        /*!< Offset: 0x008 - 0x3FFC Reserved */
    __IOM uint64_t MTIMECMP;                /*!< Offset: 0x4000 (R/W)  System Timer compare Value 64bits Register */
    __IOM uint32_t RESERVED1[0x1FFC];       /*!< Offset: 0x4008 - 0xBFF4 Reserved */
    __IOM uint64_t MTIME;                   /*!< Offset: 0xBFF8 (R/W)  System Timer load Value 64bits Register */
} SysTimer_Type;


/* Timer Control / Status Register Definitions */
#define SysTimer_MSIP_MSIP_Pos              0U                                          /*!< SysTick Timer MSIP: MSIP bit Position */
#define SysTimer_MSIP_MSIP_Msk              (1UL << SysTimer_MSIP_MSIP_Pos)             /*!< SysTick Timer MSIP: MSIP Mask */

#define SysTimer_MTIMER_Msk                 (0xFFFFFFFFFFFFFFFFULL)                     /*!< SysTick Timer MTIMER value Mask */
#define SysTimer_MTIMERCMP_Msk              (0xFFFFFFFFFFFFFFFFULL)                     /*!< SysTick Timer MTIMERCMP value Mask */
#define SysTimer_MSIP_Msk                   (0xFFFFFFFFUL)                              /*!< SysTick Timer MSIP   value Mask */

#ifndef __SYSTIMER_BASEADDR
/* Base address of SYSTIMER(__SYSTIMER_BASEADDR) should be defined in <Device.h> */
#error "__SYSTIMER_BASEADDR is not defined, please check!"
#endif
/* System Timer Memory mapping of Device  */
#define SysTimer_BASE                       __SYSTIMER_BASEADDR                         /*!< SysTick Base Address */
#define SysTimer                            ((SysTimer_Type *) SysTimer_BASE)           /*!< SysTick configuration struct */
/** @} */ /* end of group NMSIS_Core_SysTimer_Registers */

/* ##################################    SysTimer function  ############################################ */
/**
 * \defgroup NMSIS_Core_SysTimer SysTimer Functions
 * \brief    Functions that configure the Core System Timer.
 * @{
 */
/**
 * \brief  Set system timer load value
 * \details
 * This function set the system timer load value in MTIMER register.
 * \param [in]  value   value to set system timer MTIMER register.
 * \remarks
 * - Load value is 64bits wide.
 * - \ref SysTimer_GetLoadValue
 */
__STATIC_FORCEINLINE void SysTimer_SetLoadValue(uint64_t value)
{
    SysTimer->MTIME = value;
}

/**
 * \brief  Get system timer load value
 * \details
 * This function get the system timer current value in MTIMER register.
 * \return  current value(64bit) of system timer MTIMER register.
 * \remarks
 * - Load value is 64bits wide.
 * - \ref SysTimer_SetLoadValue
 */
__STATIC_FORCEINLINE uint64_t SysTimer_GetLoadValue(void)
{
    return SysTimer->MTIME;
}

/**
 * \brief  Set system timer compare value
 * \details
 * This function set the system Timer compare value in MTIMERCMP register.
 * \param [in]  value   compare value to set system timer MTIMERCMP register.
 * \remarks
 * - Compare value is 64bits wide.
 * - If compare value is larger than current value timer interrupt generate.
 * - Modify the load value or compare value less to clear the interrupt.
 * - \ref SysTimer_GetCompareValue
 */
__STATIC_FORCEINLINE void SysTimer_SetCompareValue(uint64_t value)
{
    SysTimer->MTIMECMP = value;
}

/**
 * \brief  Get system timer compare value
 * \details
 * This function get the system timer compare value in MTIMERCMP register.
 * \return  compare value of system timer MTIMERCMP register.
 * \remarks
 * - Compare value is 64bits wide.
 * - \ref SysTimer_SetCompareValue
 */
__STATIC_FORCEINLINE uint64_t SysTimer_GetCompareValue(void)
{
    return SysTimer->MTIMECMP;
}

/**
 * \brief  Trigger or set software interrupt via system timer
 * \details
 * This function set the system timer MSIP bit in MSIP register.
 * \remarks
 * - Set system timer MSIP bit and generate a SW interrupt.
 * - \ref SysTimer_ClearSWIRQ
 * - \ref SysTimer_GetMsipValue
 */
__STATIC_FORCEINLINE void SysTimer_SetSWIRQ(void)
{
    SysTimer->MSIP |= SysTimer_MSIP_MSIP_Msk;
}

/**
 * \brief  Clear system timer software interrupt pending request
 * \details
 * This function clear the system timer MSIP bit in MSIP register.
 * \remarks
 * - Clear system timer MSIP bit in MSIP register to clear the software interrupt pending.
 * - \ref SysTimer_SetSWIRQ
 * - \ref SysTimer_GetMsipValue
 */
__STATIC_FORCEINLINE void SysTimer_ClearSWIRQ(void)
{
    SysTimer->MSIP &= ~SysTimer_MSIP_MSIP_Msk;
}

/**
 * \brief  Get system timer MSIP register value
 * \details
 * This function get the system timer MSIP register value.
 * \return    Value of Timer MSIP register.
 * \remarks
 * - Bit0 is SW interrupt flag.
 *   Bit0 is 1 then SW interrupt set. Bit0 is 0 then SW interrupt clear.
 * - \ref SysTimer_SetSWIRQ
 * - \ref SysTimer_ClearSWIRQ
 */
__STATIC_FORCEINLINE uint32_t SysTimer_GetMsipValue(void)
{
    return (uint32_t)(SysTimer->MSIP & SysTimer_MSIP_Msk);
}

/**
 * \brief  Set system timer MSIP register value
 * \details
 * This function set the system timer MSIP register value.
 * \param [in]  msip   value to set MSIP register
 */
__STATIC_FORCEINLINE void SysTimer_SetMsipValue(uint32_t msip)
{
    SysTimer->MSIP = (msip & SysTimer_MSIP_Msk);
}

#if defined (__Vendor_SysTickConfig) && (__Vendor_SysTickConfig == 0U)
/**
 * \brief   System Tick Configuration
 * \details Initializes the System Timer and its non-vector interrupt, and starts the System Tick Timer.
 *
 *  In our default implementation, the timer counter will be set to zero, and it will start a timer compare non-vector interrupt
 *  when it matchs the ticks user set, during the timer interrupt user should reload the system tick using \ref SysTick_Reload function
 *  or similar function written by user, so it can produce period timer interrupt.
 * \param [in]  ticks  Number of ticks between two interrupts.
 * \return          0  Function succeeded.
 * \return          1  Function failed.
 * \sa
 * - \ref SysTimer_SetCompareValue; SysTimer_SetLoadValue
 */
__STATIC_INLINE uint32_t SysTick_Config(uint64_t ticks)
{
    SysTimer_SetLoadValue(0);
    SysTimer_SetCompareValue(ticks);
    __enable_timer_irq();
    return (0UL);
}

/**
 * \brief   System Tick Reload
 * \details Reload the System Timer Tick when the MTIMECMP reached TIME value
 *
 * \param [in]  ticks  Number of ticks between two interrupts.
 * \return          0  Function succeeded.
 * \return          1  Function failed.
 * \sa
 * - \ref SysTimer_SetCompareValue
 * - \ref SysTimer_SetLoadValue
 */
__STATIC_FORCEINLINE uint32_t SysTick_Reload(uint64_t ticks)
{
    uint64_t cur_ticks = SysTimer->MTIME;
    uint64_t reload_ticks = ticks + cur_ticks;

    if (__USUALLY(reload_ticks > cur_ticks)) {
        SysTimer->MTIMECMP = reload_ticks;
    } else {
        /* When added the ticks value, then the MTIMERCMP < TIMER,
         * which means the MTIMERCMP is overflowed,
         * so we need to reset the counter to zero */
        SysTimer->MTIME = 0;
        SysTimer->MTIMECMP = ticks;
    }

    return (0UL);
}

#endif /* defined(__Vendor_SysTickConfig) && (__Vendor_SysTickConfig == 0U) */
/** @} */ /* End of Doxygen Group NMSIS_Core_SysTimer */

#endif /* defined(__SYSTIMER_PRESENT) && (__SYSTIMER_PRESENT == 1) */

#ifdef __cplusplus
}
#endif
#endif /** __CORE_FEATURE_TIMER_H__  */

