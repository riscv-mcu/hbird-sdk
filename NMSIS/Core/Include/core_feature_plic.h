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
#ifndef __CORE_FEATURE_PLIC__
#define __CORE_FEATURE_PLIC__
/*!
 * @file     core_feature_plic.h
 * @brief    PLIC feature API header file for RISC-V Core
 */
/*
 * PLIC Feature Configuration Macro:
 * 1. __PLIC_PRESENT:  Define whether Platform Level Interrupt Controller (PLIC) Unit is present or not
 *   * 0: Not present
 *   * 1: Present
 * 2. __PLIC_BASEADDR:  Base address of the PLIC unit.
 * 3. __PLIC_INTNUM  : Define the external interrupt number of PLIC Unit
 *
 */
#ifdef __cplusplus
 extern "C" {
#endif

#if defined(__PLIC_PRESENT) && (__PLIC_PRESENT == 1)
/**
 * \defgroup NMSIS_Core_PLIC_Registers     Register Define and Type Definitions Of PLIC
 * \ingroup NMSIS_Core_Registers
 * \brief   Type definitions and defines for plic registers.
 *
 * @{
 */

/* 32 bits per source */
#define PLIC_PRIORITY_OFFSET                _AC(0x0000,UL)      /*!< PLIC Priority register offset */
#define PLIC_PRIORITY_SHIFT_PER_SOURCE      2                   /*!< PLIC Priority register offset shift per source */
/* 1 bit per source (1 address) */
#define PLIC_PENDING_OFFSET                 _AC(0x1000,UL)      /*!< PLIC Pending register offset */
#define PLIC_PENDING_SHIFT_PER_SOURCE       0                   /*!< PLIC Pending register offset shift per source */

/* 0x80 per target */
#define PLIC_ENABLE_OFFSET                  _AC(0x2000,UL)      /*!< PLIC Enable register offset */
#define PLIC_ENABLE_SHIFT_PER_TARGET        7                   /*!< PLIC Enable register offset shift per target */

#define PLIC_THRESHOLD_OFFSET               _AC(0x200000,UL)    /*!< PLIC Threshold register offset */
#define PLIC_CLAIM_OFFSET                   _AC(0x200004,UL)    /*!< PLIC Claim register offset */
#define PLIC_THRESHOLD_SHIFT_PER_TARGET     12                  /*!< PLIC Threshold register offset shift per target */
#define PLIC_CLAIM_SHIFT_PER_TARGET         12                  /*!< PLIC Claim register offset shift per target */

#ifndef __PLIC_BASEADDR
/* Base address of PLIC(__PLIC_BASEADDR) should be defined in <Device.h> */
#error "__PLIC_BASEADDR is not defined, please check!"
#endif

/* PLIC Memory mapping of Device */
#define PLIC_BASE                           __PLIC_BASEADDR                            /*!< PLIC Base Address */

/** @} */ /* end of group NMSIS_Core_PLIC_Registers */

/* ##########################   PLIC functions  #################################### */
/**
 * \defgroup   NMSIS_Core_IntExc        Interrupts and Exceptions
 * \brief Functions that manage interrupts and exceptions via the PLIC.
 *
 * @{
 */

/**
 * \brief  Definition of IRQn numbers
 * \details
 * The core interrupt enumeration names for IRQn values are defined in the file <b><Device>.h</b>.
 * - Interrupt ID(IRQn) from 0 to 18 are reserved for core internal interrupts.
 * - Interrupt ID(IRQn) start from 19 represent device-specific external interrupts.
 * - The first device-specific interrupt has the IRQn value 19.
 *
 * The table below describes the core interrupt names and their availability in various Nuclei Cores.
 */
/* The following enum IRQn definition in this file
 * is only used for doxygen documentation generation,
 * The <Device>.h is the real file to define it by vendor
 */
#if defined(__ONLY_FOR_DOXYGEN_DOCUMENT_GENERATION__)
typedef enum IRQn {
    /* ========= RISC-V Core Specific Interrupt Numbers  =========== */
    /* Core Internal Interrupt IRQn definitions */
    Reserved0_IRQn            =   0,              /*!<  Internal reserved */
    Reserved1_IRQn            =   1,              /*!<  Internal reserved */
    Reserved2_IRQn            =   2,              /*!<  Internal reserved */
    SysTimerSW_IRQn           =   3,              /*!<  System Timer SW interrupt */
    Reserved4_IRQn            =   4,              /*!<  Internal reserved */
    Reserved5_IRQn            =   5,              /*!<  Internal reserved */
    Reserved6_IRQn            =   6,              /*!<  Internal reserved */
    SysTimer_IRQn             =   7,              /*!<  System Timer Interrupt */
    Reserved8_IRQn            =   8,              /*!<  Internal reserved */
    Reserved9_IRQn            =   9,              /*!<  Internal reserved */
    Reserved10_IRQn           =  10,              /*!<  Internal reserved */
    Reserved11_IRQn           =  11,              /*!<  Internal reserved */
    Reserved12_IRQn           =  12,              /*!<  Internal reserved */
    Reserved13_IRQn           =  13,              /*!<  Internal reserved */
    Reserved14_IRQn           =  14,              /*!<  Internal reserved */
    Reserved15_IRQn           =  15,              /*!<  Internal reserved */


    /* ========= PLIC Interrupt Numbers  =================== */
    /* Plic interrupt number also started from 0 */
    PLIC_INT0_IRQn            = 0,    /*!< 0 plic interrupt, means no interrupt */
    PLIC_INT1_IRQn            = 1,    /*!< 1st plic interrupt */
    PLIC_INT_MAX,                     /*!< Number of total plic interrupts */
} IRQn_Type;
#endif /* __ONLY_FOR_DOXYGEN_DOCUMENT_GENERATION__ */

/**
 * \brief  Set priority threshold value of plic
 * \details
 * This function set priority threshold value of plic for current hart.
 * \param [in]    thresh    threshold value
 * \remarks
 * \sa
 * - \ref PLIC_GetThreshold
 */
__STATIC_FORCEINLINE void PLIC_SetThreshold(uint32_t thresh)
{
    uint32_t hartid = __RV_CSR_READ(CSR_MHARTID);
    volatile uint32_t *thresh_reg = (uint32_t *)((PLIC_BASE) + \
                    PLIC_THRESHOLD_OFFSET + (hartid << PLIC_THRESHOLD_SHIFT_PER_TARGET));

    *thresh_reg = thresh;
}

/**
 * \brief  Get priority threshold value of plic
 * \details
 * This function get priority threshold value of plic.
 * \return priority threshold value for current hart
 * \remarks
 * \sa
 * - \ref PLIC_SetThreshold
 */
__STATIC_FORCEINLINE uint32_t PLIC_GetThreshold(void)
{
    uint32_t hartid = __RV_CSR_READ(CSR_MHARTID);
    volatile uint32_t *thresh_reg = (uint32_t *)((PLIC_BASE) + \
                    PLIC_THRESHOLD_OFFSET + (hartid << PLIC_THRESHOLD_SHIFT_PER_TARGET));

    return (*thresh_reg);
}

/**
 * \brief  Enable interrupt for selected source plic
 * \details
 * This function enable interrupt for selected source plic of current hart.
 * \param [in]    source    interrupt source
 * \remarks
 * \sa
 * - \ref PLIC_DisableInterrupt
 */
__STATIC_FORCEINLINE void PLIC_EnableInterrupt(uint32_t source)
{
    uint32_t hartid = __RV_CSR_READ(CSR_MHARTID);
    volatile uint32_t *enable_reg = (uint32_t *)((PLIC_BASE) + PLIC_ENABLE_OFFSET + \
                    (hartid << PLIC_ENABLE_SHIFT_PER_TARGET) + (source >> 5) * 4);

    uint32_t current = *enable_reg;
    current = current | (1<<(source&0x1F));
    *enable_reg = current;
}

/**
 * \brief  Disable interrupt for selected source plic
 * \details
 * This function disable interrupt for selected source plic of current hart.
 * \param [in]    source    interrupt source
 * \remarks
 * \sa
 * - \ref PLIC_EnableInterrupt
 */
__STATIC_FORCEINLINE void PLIC_DisableInterrupt(uint32_t source)
{
    uint32_t hartid = __RV_CSR_READ(CSR_MHARTID);
    volatile uint32_t *enable_reg = (uint32_t *)((PLIC_BASE) + PLIC_ENABLE_OFFSET + \
                    (hartid << PLIC_ENABLE_SHIFT_PER_TARGET) + (source >> 5) * 4);

    uint32_t current = *enable_reg;
    current = current & (~(1<<(source&0x1F)));
    *enable_reg = current;
}

/**
 * \brief  Get interrupt enable status for selected source plic
 * \details
 * This function get interrupt enable for selected source plic of current hart.
 * \param [in]    source    interrupt source
 * \return enable status for selected interrupt source for current hart
 * \remarks
 * \sa
 * - \ref PLIC_EnableInterrupt
 * - \ref PLIC_DisableInterrupt
 */
__STATIC_FORCEINLINE uint32_t PLIC_GetInterruptEnable(uint32_t source)
{
    uint32_t hartid = __RV_CSR_READ(CSR_MHARTID);
    volatile uint32_t *enable_reg = (uint32_t *)((PLIC_BASE) + PLIC_ENABLE_OFFSET + \
                    (hartid << PLIC_ENABLE_SHIFT_PER_TARGET) + (source >> 5) * 4);

    uint32_t current = *enable_reg;
    current = current >> (source&0x1F);
    return current;
}

/**
 * \brief  Set interrupt priority for selected source plic
 * \details
 * This function set interrupt priority for selected source plic of current hart.
 * \param [in]    source    interrupt source
 * \param [in]    priority  interrupt priority
 * \remarks
 * \sa
 * - \ref PLIC_GetPriority
 */
__STATIC_FORCEINLINE void PLIC_SetPriority(uint32_t source, uint32_t priority)
{
    volatile uint32_t *priority_reg = (uint32_t *)((PLIC_BASE) + PLIC_PRIORITY_OFFSET + \
                    + (source << PLIC_PRIORITY_SHIFT_PER_SOURCE));

    *priority_reg = priority;
}

/**
 * \brief  Get interrupt priority for selected source plic
 * \details
 * This function get interrupt priority for selected source plic of current hart.
 * \param [in]    source    interrupt source
 * \param [in]    priority  interrupt priority
 * \remarks
 * \sa
 * - \ref PLIC_SetPriority
 */
__STATIC_FORCEINLINE uint32_t PLIC_GetPriority(uint32_t source, uint32_t priority)
{
    volatile uint32_t *priority_reg = (uint32_t *)((PLIC_BASE) + PLIC_PRIORITY_OFFSET + \
                    + (source << PLIC_PRIORITY_SHIFT_PER_SOURCE));

    return (*priority_reg);
}

/**
 * \brief  Claim interrupt for plic of current hart
 * \details
 * This function claim interrupt for plic of current hart.
 * \return  the ID of the highest priority pending interrupt or
 *      zero if there is no pending interrupt
 * \remarks
 * A successful claim will also atomically clear the corresponding pending bit
 * on the interrupt source. The PLIC can perform a claim at any time and the
 * claim operation is not affected by the setting of the priority threshold register.
 * \sa
 * - \ref PLIC_CompleteInterrupt
 */
__STATIC_FORCEINLINE uint32_t PLIC_ClaimInterrupt(void)
{
    uint32_t hartid = __RV_CSR_READ(CSR_MHARTID);
    volatile uint32_t *claim_reg = (uint32_t *)((PLIC_BASE) + PLIC_CLAIM_OFFSET + \
                    + (hartid << PLIC_CLAIM_SHIFT_PER_TARGET));

    return (*claim_reg);
}

/**
 * \brief  Complete interrupt for plic of current hart
 * \details
 * This function complete interrupt for plic of current hart.
 * \return  the ID of the highest priority pending interrupt or
 *      zero if there is no pending interrupt
 * \remarks
 * The PLIC signals it has completed executing an interrupt handler by writing
 * the interrupt ID it received from the claim to the claim/complete register.
 * The PLIC does not check whether the completion ID is the same as the last
 * claim ID for that target.
 * If the completion ID does not match an interrupt source that is currently
 * enabled for the target, the completion is silently ignored.
 * \sa
 * - \ref PLIC_ClaimInterrupt
 */
__STATIC_FORCEINLINE void PLIC_CompleteInterrupt(uint32_t source)
{
    uint32_t hartid = __RV_CSR_READ(CSR_MHARTID);
    volatile uint32_t *complete_reg = (uint32_t *)((PLIC_BASE) + PLIC_CLAIM_OFFSET + \
                    + (hartid << PLIC_CLAIM_SHIFT_PER_TARGET));

    *complete_reg = source;
}

/**
 * \brief  Perform init for plic of current hart
 * \details
 * This function perform initialization steps for plic of current hart.
 * \remarks
 * * Disable all interrupts
 * * Set all priorities to zero
 * * Set priority threshold to zero
 */
__STATIC_FORCEINLINE void PLIC_Init(uint32_t num_sources)
{
    uint32_t i;

    for (i = 0; i < num_sources; i ++) {
        PLIC_DisableInterrupt(i);
        PLIC_SetPriority(i, 0);
    }
    PLIC_SetThreshold(0);
}

/**
 * \brief  Set Trap entry address
 * \details
 * This function set trap entry address to 'CSR_MTVEC'.
 * \param [in]      addr  trap entry address
 * \remarks
 * - This function use to set trap entry address to 'CSR_MTVEC'.
 * \sa
 * - \ref __get_trap_entry
 */
__STATIC_FORCEINLINE void __set_trap_entry(rv_csr_t addr)
{
    addr &= (rv_csr_t)(~0x7);
    __RV_CSR_WRITE(CSR_MTVEC, addr);
}

/**
 * \brief  Get trap entry address
 * \details
 * This function get trap entry address from 'CSR_MTVEC'.
 * \return       trap entry address
 * \remarks
 * - This function use to get trap entry address from 'CSR_MTVEC'.
 * \sa
 * - \ref __set_trap_entry
 */
__STATIC_FORCEINLINE rv_csr_t __get_trap_entry(void)
{
    unsigned long addr = __RV_CSR_READ(CSR_MTVEC);
    return (addr);
}

/** @} */ /* End of Doxygen Group NMSIS_Core_IntExc */

#endif /* defined(__PLIC_PRESENT) && (__PLIC_PRESENT == 1) */

#ifdef __cplusplus
}
#endif
#endif /** __CORE_FEATURE_PLIC__ */
