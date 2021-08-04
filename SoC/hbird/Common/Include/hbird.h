/******************************************************************************
 * @file     hbird.h
 * @brief    NMSIS Core Peripheral Access Layer Header File for
 *           HummingBird RISC-V evaluation SoC which support HummingBird RISC-V cores
 * @version  V1.00
 * @date     14. Jul 2020
 ******************************************************************************/
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

#ifndef __HBIRD_H__
#define __HBIRD_H__

#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

/** @addtogroup HummingBird
  * @{
  */


/** @addtogroup hbird
  * @{
  */


/** @addtogroup Configuration_of_NMSIS
  * @{
  */

/** \brief SoC Download mode definition */
typedef enum {
    DOWNLOAD_MODE_FLASHXIP = 0,         /*!< Flashxip download mode */
    DOWNLOAD_MODE_FLASH = 1,            /*!< Flash download mode */
    DOWNLOAD_MODE_ILM = 2,              /*!< ilm download mode */
    DOWNLOAD_MODE_DDR = 3,              /*!< ddr download mode */
    DOWNLOAD_MODE_MAX,
} DownloadMode_Type;


/* =========================================================================================================================== */
/* ================                                Interrupt Number Definition                                ================ */
/* =========================================================================================================================== */

typedef enum IRQn
{
/* =======================================  RISC-V Core Specific Interrupt Numbers  ======================================== */

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

/* ===========================================  PLIC Interrupt Numbers  ========================================= */
/* ToDo: add here your plic device specific external interrupt numbers.
         eg.: Interrupt for Timer#1      plic_tim1_handler   ->   TIM1_IRQn */
    PLIC_INT0_IRQn           = 0,                /*!< Device external Interrupt 0 */
    PLIC_WDOGCMP_IRQn        = 1,                /*!< Device external Interrupt 1, Watchdog compare */
    PLIC_RTCCMP_IRQn         = 2,                /*!< Device external Interrupt 2 RTC compare */
    PLIC_UART0_IRQn          = 3,                /*!< Device external Interrupt 3  UART0 */
    PLIC_UART1_IRQn          = 4,                /*!< Device external Interrupt 4 UART1 */
    PLIC_QSPI0_IRQn          = 5,                /*!< Device external Interrupt 5 Queued SPI0 */
    PLIC_QSPI1_IRQn          = 6,                /*!< Device external Interrupt 6 Queued SPI1 */
    PLIC_QSPI2_IRQn          = 7,                /*!< Device external Interrupt 7 Queued SPI2 */
    PLIC_GPIO0_IRQn          = 8,                /*!< Device external Interrupt 8 GPIO0 */
    PLIC_GPIO1_IRQn          = 9,                /*!< Device external Interrupt 9 GPIO1 */
    PLIC_GPIO2_IRQn          = 10,               /*!< Device external Interrupt 10 GPIO2 */
    PLIC_GPIO3_IRQn          = 11,               /*!< Device external Interrupt 11 GPIO3 */
    PLIC_GPIO4_IRQn          = 12,               /*!< Device external Interrupt 12 GPIO4 */
    PLIC_GPIO5_IRQn          = 13,               /*!< Device external Interrupt 13 GPIO5 */
    PLIC_GPIO6_IRQn          = 14,               /*!< Device external Interrupt 14 GPIO6 */
    PLIC_GPIO7_IRQn          = 15,               /*!< Device external Interrupt 15 GPIO7 */
    PLIC_GPIO8_IRQn          = 16,               /*!< Device external Interrupt 16 GPIO8 */
    PLIC_GPIO9_IRQn          = 17,               /*!< Device external Interrupt 17 GPIO9 */
    PLIC_GPIO10_IRQn         = 18,               /*!< Device external Interrupt 18 GPIO10 */
    PLIC_GPIO11_IRQn         = 19,               /*!< Device external Interrupt 19 GPIO11 */
    PLIC_GPIO12_IRQn         = 20,               /*!< Device external Interrupt 20 GPIO12 */
    PLIC_GPIO13_IRQn         = 21,               /*!< Device external Interrupt 21 GPIO13 */
    PLIC_GPIO14_IRQn         = 22,               /*!< Device external Interrupt 22 GPIO14 */
    PLIC_GPIO15_IRQn         = 23,               /*!< Device external Interrupt 23 GPIO15 */
    PLIC_GPIO16_IRQn         = 24,               /*!< Device external Interrupt 24 GPIO16 */
    PLIC_GPIO17_IRQn         = 25,               /*!< Device external Interrupt 25 GPIO17 */
    PLIC_GPIO18_IRQn         = 26,               /*!< Device external Interrupt 26 GPIO18 */
    PLIC_GPIO19_IRQn         = 27,               /*!< Device external Interrupt 27 GPIO19 */
    PLIC_GPIO20_IRQn         = 28,               /*!< Device external Interrupt 28 GPIO20 */
    PLIC_GPIO21_IRQn         = 29,               /*!< Device external Interrupt 29 GPIO21 */
    PLIC_GPIO22_IRQn         = 30,               /*!< Device external Interrupt 30 GPIO22 */
    PLIC_GPIO23_IRQn         = 31,               /*!< Device external Interrupt 31 GPIO23 */
    PLIC_GPIO24_IRQn         = 32,               /*!< Device external Interrupt 32 GPIO24 */
    PLIC_GPIO25_IRQn         = 33,               /*!< Device external Interrupt 33 GPIO25 */
    PLIC_GPIO26_IRQn         = 34,               /*!< Device external Interrupt 34 GPIO26 */
    PLIC_GPIO27_IRQn         = 35,               /*!< Device external Interrupt 35 GPIO27 */
    PLIC_GPIO28_IRQn         = 36,               /*!< Device external Interrupt 36 GPIO28 */
    PLIC_GPIO29_IRQn         = 37,               /*!< Device external Interrupt 37 GPIO29 */
    PLIC_GPIO30_IRQn         = 38,               /*!< Device external Interrupt 38 GPIO30 */
    PLIC_GPIO31_IRQn         = 39,               /*!< Device external Interrupt 39 GPIO31 */
    PLIC_PWM0CMP0_IRQn       = 40,               /*!< Device external Interrupt 40 PWM0 compare0 */
    PLIC_PWM0CMP1_IRQn       = 41,               /*!< Device external Interrupt 41 PWM0 compare1 */
    PLIC_PWM0CMP2_IRQn       = 42,               /*!< Device external Interrupt 42 PWM0 compare2 */
    PLIC_PWM0CMP3_IRQn       = 43,               /*!< Device external Interrupt 43 PWM0 compare3 */
    PLIC_PWM1CMP0_IRQn       = 44,               /*!< Device external Interrupt 44 PWM1 compare0 */
    PLIC_PWM1CMP1_IRQn       = 45,               /*!< Device external Interrupt 45 PWM1 compare1 */
    PLIC_PWM1CMP2_IRQn       = 46,               /*!< Device external Interrupt 46 PWM1 compare2 */
    PLIC_PWM1CMP3_IRQn       = 47,               /*!< Device external Interrupt 47 PWM1 compare3 */
    PLIC_PWM2CMP0_IRQn       = 48,               /*!< Device external Interrupt 48 PWM2 compare0 */
    PLIC_PWM2CMP1_IRQn       = 49,               /*!< Device external Interrupt 49 PWM2 compare1 */
    PLIC_PWM2CMP2_IRQn       = 50,               /*!< Device external Interrupt 50 PWM2 compare2 */
    PLIC_PWM2CMP3_IRQn       = 51,               /*!< Device external Interrupt 51 PWM2 compare3 */
    PLIC_I2C_IRQn            = 52,               /*!< Device external Interrupt 52 I2C */
    PLIC_INT_MAX,
} IRQn_Type;

/* =========================================================================================================================== */
/* ================                                  Exception Code Definition                                ================ */
/* =========================================================================================================================== */

typedef enum EXCn {
/* =======================================  RISC-V Core Specific Exception Code  ======================================== */
    InsUnalign_EXCn          =   0,              /*!<  Instruction address misaligned */
    InsAccFault_EXCn         =   1,              /*!<  Instruction access fault */
    IlleIns_EXCn             =   2,              /*!<  Illegal instruction */
    Break_EXCn               =   3,              /*!<  Beakpoint */
    LdAddrUnalign_EXCn       =   4,              /*!<  Load address misaligned */
    LdFault_EXCn             =   5,              /*!<  Load access fault */
    StAddrUnalign_EXCn       =   6,              /*!<  Store or AMO address misaligned */
    StAccessFault_EXCn       =   7,              /*!<  Store or AMO access fault */
    UmodeEcall_EXCn          =   8,              /*!<  Environment call from User mode */
    MmodeEcall_EXCn          =  11,              /*!<  Environment call from Machine mode */
} EXCn_Type;

/* =========================================================================================================================== */
/* ================                           Processor and Core Peripheral Section                           ================ */
/* =========================================================================================================================== */

/* ToDo: set the defines according your Device */
/* ToDo: define the correct core revision */
#if __riscv_xlen == 32

#ifndef __HBIRD_CORE_REV
#define __HBIRD_RISCV_REV         0x0100    /*!< Core Revision r1p0 */
#else
#define __HBIRD_RISCV_REV         __HBIRD_CORE_REV
#endif

#elif __riscv_xlen == 64

#ifndef __HBIRD_CORE_REV
#define __HBIRD_RISCV_REV         0x0100    /*!< Core Revision r1p0 */
#else
#define __HBIRD_RISCV_REV         __HBIRD_CORE_REV
#endif

#endif /* __riscv_xlen == 64 */

/* ToDo: define the correct core features for the hbird */
#ifndef SIMULATION_SPIKE
#define __PLIC_PRESENT            1                     /*!< Set to 1 if PLIC is present */
#else
#define __PLIC_PRESENT            0                     /*!< Set to 1 if PLIC is present */
#endif
#ifdef SIMULATION_XLSPIKE
#define __PLIC_BASEADDR           0x08000000UL          /*!< Set to PLIC baseaddr of your device */
#else
#define __PLIC_BASEADDR           0x0C000000UL          /*!< Set to PLIC baseaddr of your device */
#endif
#define __PLIC_INTNUM             53                    /*!< Set to 1 - 1024, total interrupt sources of PLIC Unit */

#define __SYSTIMER_PRESENT        1                     /*!< Set to 1 if System CLINT Timer is present */
#ifdef SIMULATION_XLSPIKE
#define __SYSTIMER_BASEADDR       0x02001000UL          /*!< Set to CLINT Timer baseaddr of your device */
#else
#define __SYSTIMER_BASEADDR       0x02000000UL          /*!< Set to CLINT Timer baseaddr of your device */
#endif

/*!< Set to 0, 1, or 2, 0 not present, 1 single floating point unit present, 2 double floating point unit present */
#if !defined(__riscv_flen)
#define __FPU_PRESENT             0
#elif __riscv_flen == 32
#define __FPU_PRESENT             1
#else
#define __FPU_PRESENT             2
#endif

#define __Vendor_SysTickConfig    0                     /*!< Set to 1 if different SysTick Config is used */

/** @} */ /* End of group Configuration_of_CMSIS */


#include <nmsis_core.h>                      /*!< HummingBird RISC-V processor and core peripherals */
/* ToDo: include your system_hbird.h file
         replace 'Device' with your device name */
#include "system_hbird.h"                    /*!< hbird System */


/* ========================================  Start of section using anonymous unions  ======================================== */
#if   defined (__GNUC__)
  /* anonymous unions are enabled by default */
#else
  #warning Not supported compiler type
#endif

#define RTC_FREQ                    32768
// The TIMER frequency is just the RTC frequency
#define SOC_TIMER_FREQ              RTC_FREQ
/* =========================================================================================================================== */
/* ================                            Device Specific Peripheral Section                             ================ */
/* =========================================================================================================================== */


/** @addtogroup Device_Peripheral_peripherals
  * @{
  */

/****************************************************************************
 * Platform definitions
 *****************************************************************************/
// IOF Mappings
#define IOF0_SPI1_MASK              _AC(0x000007FC,UL)
#define SPI11_NUM_SS                (4)
#define IOF_SPI1_SS0                (2u)
#define IOF_SPI1_SS1                (8u)
#define IOF_SPI1_SS2                (9u)
#define IOF_SPI1_SS3                (10u)
#define IOF_SPI1_MOSI               (3u)
#define IOF_SPI1_MISO               (4u)
#define IOF_SPI1_SCK                (5u)
#define IOF_SPI1_DQ0                (3u)
#define IOF_SPI1_DQ1                (4u)
#define IOF_SPI1_DQ2                (6u)
#define IOF_SPI1_DQ3                (7u)

#define IOF0_SPI2_MASK              _AC(0xFC000000,UL)
#define SPI2_NUM_SS                 (1)
#define IOF_SPI2_SS0                (26u)
#define IOF_SPI2_MOSI               (27u)
#define IOF_SPI2_MISO               (28u)
#define IOF_SPI2_SCK                (29u)
#define IOF_SPI2_DQ0                (27u)
#define IOF_SPI2_DQ1                (28u)
#define IOF_SPI2_DQ2                (30u)
#define IOF_SPI2_DQ3                (31u)

#define IOF0_UART0_MASK             _AC(0x00030000, UL)
#define IOF_UART0_RX                (16u)
#define IOF_UART0_TX                (17u)

#define IOF0_UART1_MASK             _AC(0x03000000, UL)
#define IOF_UART1_RX                (24u)
#define IOF_UART1_TX                (25u)

#define IOF0_I2C_MASK               _AC(0x00003000, UL)
#define IOF_I2C_SDA                 (12u)
#define IOF_I2C_SCL                 (13u)

#define IOF1_PWM0_MASK              _AC(0x0000000F, UL)
#define IOF1_PWM1_MASK              _AC(0x00780000, UL)
#define IOF1_PWM2_MASK              _AC(0x00003C00, UL)

// Interrupt Numbers
#define SOC_PLIC_NUM_INTERRUPTS    32
#define SOC_PLIC_INT_GPIO_BASE     19

// Interrupt Handler Definitions
#define SOC_MTIMER_HANDLER          core_mtip_handler
#define SOC_SOFTINT_HANDLER         core_msip_handler

#define GPIO_BIT_ALL_ZERO           (0x0)
#define GPIO_BIT_ALL_ONE            (0xFFFFFFFF)

/**
  * @brief GPIO
  */
typedef struct {  /*!< GPIO Structure */
    __IOM uint32_t INPUT_VAL;
    __IOM uint32_t INPUT_EN;
    __IOM uint32_t OUTPUT_EN;
    __IOM uint32_t OUTPUT_VAL;
    __IOM uint32_t PULLUP_EN;
    __IOM uint32_t DRIVE;
    __IOM uint32_t RISE_IE;
    __IOM uint32_t RISE_IP;
    __IOM uint32_t FALL_IE;
    __IOM uint32_t FALL_IP;
    __IOM uint32_t HIGH_IE;
    __IOM uint32_t HIGH_IP;
    __IOM uint32_t LOW_IE;
    __IOM uint32_t LOW_IP;
    __IOM uint32_t IOF_EN;
    __IOM uint32_t IOF_SEL;
    __IOM uint32_t OUTPUT_XOR;
} GPIO_TypeDef;

/**
  * @brief UART
  */
typedef struct {
    __IOM uint32_t TXFIFO;
    __IOM uint32_t RXFIFO;
    __IOM uint32_t TXCTRL;
    __IOM uint32_t RXCTRL;
    __IOM uint32_t IE;
    __IOM uint32_t IP;
    __IOM uint32_t DIV;
} UART_TypeDef;

/**
  * @brief PWM
  */
typedef struct {
    __IOM uint32_t CFG;
          uint32_t RESERVED0;
    __IOM uint32_t COUNT;
          uint32_t RESERVED1;
    __IOM uint32_t S;
          uint32_t RESERVED2[3];
    __IOM uint32_t CMP0;
    __IOM uint32_t CMP1;
    __IOM uint32_t CMP2;
    __IOM uint32_t CMP3;
} PWM_TypeDef;

/**
  * @brief QSPI
  */
typedef struct {
    __IOM uint32_t SCKDIV;
    __IOM uint32_t SCKMODE;
    __IOM uint32_t RESERVED0[2];
    __IOM uint32_t CSID;
    __IOM uint32_t CSDEF;
    __IOM uint32_t CSMODE;
    __IOM uint32_t RESERVED1[3];
    __IOM uint32_t DELAY0;
    __IOM uint32_t DELAY1;
    __IOM uint32_t RESERVED2[4];
    __IOM uint32_t FMT;
    __IOM uint32_t RESERVED3;
    __IOM uint32_t TXDATA;
    __IOM uint32_t RXDATA;
    __IOM uint32_t TXMARK;
    __IOM uint32_t RXMARK;
    __IOM uint32_t RESERVED4[2];
    __IOM uint32_t FCTRL;
    __IOM uint32_t FFMT;
    __IOM uint32_t RESERVED5[2];
    __IOM uint32_t IE;
    __IOM uint32_t IP;
} QSPI_TypeDef;

/**
  * @brief I2C
  */
typedef struct {
    __IOM uint8_t PRERlo;
    __IOM uint8_t PRERhi;
    __IOM uint8_t CTR;
    __IOM uint8_t TXRXR; /* TXR and RXR in same address */
    __IOM uint8_t CSR; /* CR and SR in same address */
} I2C_TypeDef;

/*@}*/ /* end of group hbird_Peripherals */


/* =========================================  End of section using anonymous unions  ========================================= */
#if defined (__GNUC__)
  /* anonymous unions are enabled by default */
#else
  #warning Not supported compiler type
#endif

/* Macros for memory access operations */
#define _REG8P(p, i)                        ((volatile uint8_t *) ((uintptr_t)((p) + (i))))
#define _REG16P(p, i)                       ((volatile uint16_t *) ((uintptr_t)((p) + (i))))
#define _REG32P(p, i)                       ((volatile uint32_t *) ((uintptr_t)((p) + (i))))
#define _REG64P(p, i)                       ((volatile uint64_t *) ((uintptr_t)((p) + (i))))
#define _REG8(p, i)                         (*(_REG8P(p, i)))
#define _REG16(p, i)                        (*(_REG16P(p, i)))
#define _REG32(p, i)                        (*(_REG32P(p, i)))
#define _REG64(p, i)                        (*(_REG64P(p, i)))
#define REG8(addr)                          _REG8((addr), 0)
#define REG16(addr)                         _REG16((addr), 0)
#define REG32(addr)                         _REG32((addr), 0)
#define REG64(addr)                         _REG64((addr), 0)

/* Macros for Bit Operations */
#if __riscv_xlen == 32
#define BITMASK_MAX                         0xFFFFFFFFUL
#define BITOFS_MAX                          31
#else
#define BITMASK_MAX                         0xFFFFFFFFFFFFFFFFULL
#define BITOFS_MAX                          63
#endif

// BIT/BITS only support bit mask for __riscv_xlen
// For RISC-V 32 bit, it support mask 32 bit wide
// For RISC-V 64 bit, it support mask 64 bit wide
#define BIT(ofs)                            (0x1UL << (ofs))
#define BITS(start, end)                    ((BITMASK_MAX) << (start) & (BITMASK_MAX) >> (BITOFS_MAX - (end)))
#define GET_BIT(regval, bitofs)             (((regval) >> (bitofs)) & 0x1)
#define SET_BIT(regval, bitofs)             ((regval) |= BIT(bitofs))
#define CLR_BIT(regval, bitofs)             ((regval) &= (~BIT(bitofs)))
#define FLIP_BIT(regval, bitofs)            ((regval) ^= BIT(bitofs))
#define CHECK_BIT(regval, bitofs)           (!!((regval) & (0x1UL<<(bitofs))))
#define GET_BITS(regval, start, end)        (((regval) & BITS((start), (end))) >> (start))
#define SET_BITS(regval, start, end)        ((regval) |= BITS((start), (end)))
#define CLR_BITS(regval, start, end)        ((regval) &= (~BITS((start), (end))))
#define FLIP_BITS(regval, start, end)       ((regval) ^= BITS((start), (end)))
#define CHECK_BITS_ALL(regval, start, end)  (!((~(regval)) & BITS((start), (end))))
#define CHECK_BITS_ANY(regval, start, end)  ((regval) & BITS((start), (end)))

#define BITMASK_SET(regval, mask)           ((regval) |= (mask))
#define BITMASK_CLR(regval, mask)           ((regval) &= (~(mask)))
#define BITMASK_FLIP(regval, mask)          ((regval) ^= (mask))
#define BITMASK_CHECK_ALL(regval, mask)     (!((~(regval)) & (mask)))
#define BITMASK_CHECK_ANY(regval, mask)     ((regval) & (mask))

/* =========================================================================================================================== */
/* ================                          Device Specific Peripheral Address Map                           ================ */
/* =========================================================================================================================== */


/* ToDo: add here your device peripherals base addresses
         following is an example for timer */
/** @addtogroup Device_Peripheral_peripheralAddr
  * @{
  */
/* Peripheral and SRAM base address */
#define QSPI_FLASH_BASE         (0x20000000UL)      /*!< (FLASH     ) Base Address */
#define ONCHIP_ROM_BASE         (0x00001000UL)      /*!< (ROM       ) Base Address */
#define ONCHIP_ILM_BASE         (0x80000000UL)      /*!< (ILM       ) Base Address */
#define ONCHIP_DLM_BASE         (0x90000000UL)      /*!< (DLM       ) Base Address */
#define HBIRD_PERIPH_BASE       (0x10000000UL)      /*!< (Peripheral) Base Address */

/* Peripheral memory map */
/* Fast-IO Interfaced IP */
#define GPIO_BASE               (HBIRD_PERIPH_BASE + 0x12000)          /*!< (GPIO) Base Address */
/* PPI Interfaced IP */
#define UART0_BASE              (HBIRD_PERIPH_BASE + 0x13000)          /*!< (UART0) Base Address */
#define QSPI0_BASE              (HBIRD_PERIPH_BASE + 0x14000)          /*!< (QSPI0) Base Address */
#define PWM0_BASE               (HBIRD_PERIPH_BASE + 0x15000)          /*!< (PWM0) Base Address */
#define UART1_BASE              (HBIRD_PERIPH_BASE + 0x23000)          /*!< (UART1) Base Address */
#define QSPI1_BASE              (HBIRD_PERIPH_BASE + 0x24000)          /*!< (QSPI1) Base Address */
#define PWM1_BASE               (HBIRD_PERIPH_BASE + 0x25000)          /*!< (PWM1) Base Address */
#define QSPI2_BASE              (HBIRD_PERIPH_BASE + 0x34000)          /*!< (QSPI2) Base Address */
#define PWM2_BASE               (HBIRD_PERIPH_BASE + 0x35000)          /*!< (PWM2) Base Address */
#define I2C_BASE                (HBIRD_PERIPH_BASE + 0x42000)          /*!< (I2C Master) Base Address */

/** @} */ /* End of group Device_Peripheral_peripheralAddr */


/* =========================================================================================================================== */
/* ================                                  Peripheral declaration                                   ================ */
/* =========================================================================================================================== */


/* ToDo: add here your device peripherals pointer definitions
         following is an example for timer */
/** @addtogroup Device_Peripheral_declaration
  * @{
  */
#define GPIO                    ((GPIO_TypeDef *) GPIO_BASE)
#define UART0                   ((UART_TypeDef *) UART0_BASE)
#define QSPI0                   ((QSPI_TypeDef *) QSPI0_BASE)
#define PWM0                    ((PWM_TypeDef *) PWM0_BASE)
#define UART1                   ((UART_TypeDef *) UART1_BASE)
#define QSPI1                   ((QSPI_TypeDef *) QSPI1_BASE)
#define PWM1                    ((PWM_TypeDef *) PWM1_BASE)
#define QSPI2                   ((QSPI_TypeDef *) QSPI2_BASE)
#define PWM2                    ((PWM_TypeDef *) PWM2_BASE)
#define I2C                     ((I2C_TypeDef *) I2C_BASE)


#define GPIO_REG(offset)        _REG32(GPIO_BASE, offset)
#define PWM0_REG(offset)        _REG32(PWM0_BASE, offset)
#define PWM1_REG(offset)        _REG32(PWM1_BASE, offset)
#define PWM2_REG(offset)        _REG32(PWM2_BASE, offset)
#define SPI0_REG(offset)        _REG32(QSPI0_BASE, offset)
#define SPI1_REG(offset)        _REG32(QSPI1_BASE, offset)
#define SPI2_REG(offset)        _REG32(QSPI2_BASE, offset)
#define UART0_REG(offset)       _REG32(UART0_BASE, offset)
#define UART1_REG(offset)       _REG32(UART1_BASE, offset)
#define I2C_REG(offset)         _REG8(I2C_BASE, offset)

// Misc

#define NUM_GPIO 32

uint32_t get_cpu_freq();
void delay_1ms(uint32_t count);

/** @} */ /* End of group hbird */

/** @} */ /* End of group HummingBird */

#ifdef __cplusplus
}
#endif

#endif  /* __HBIRD_H__ */
