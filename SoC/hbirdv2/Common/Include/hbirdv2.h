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

#ifndef __HBIRDV2_H__
#define __HBIRDV2_H__

#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

/** @addtogroup HummingBird
  * @{
  */


/** @addtogroup hbirdv2
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
    PLIC_WDOGCMP_IRQn        = 1,                /*!< Device external Interrupt 1 Watchdog compare */
    PLIC_RTCCMP_IRQn         = 2,                /*!< Device external Interrupt 2 RTC compare */
    PLIC_UART0_IRQn          = 3,                /*!< Device external Interrupt 3 UART0 */
    PLIC_UART1_IRQn          = 4,                /*!< Device external Interrupt 4 UART1 */
    PLIC_UART2_IRQn          = 5,                /*!< Device external Interrupt 5 UART2 */
    PLIC_QSPI0_IRQn          = 6,                /*!< Device external Interrupt 6 QSPI0 */
    PLIC_QSPI1_IRQn          = 7,                /*!< Device external Interrupt 7 QSPI1 */
    PLIC_QSPI2_IRQn          = 8,                /*!< Device external Interrupt 8 QSPI2 */
    PLIC_PWM0_IRQn           = 9,                /*!< Device external Interrupt 9  PWM0 */
    PLIC_PWM1_IRQn           = 10,               /*!< Device external Interrupt 10 PWM1 */
    PLIC_PWM2_IRQn           = 11,               /*!< Device external Interrupt 11 PWM2 */
    PLIC_PWM3_IRQn           = 12,               /*!< Device external Interrupt 12 PWM3 */
    PLIC_I2C0_IRQn           = 13,               /*!< Device external Interrupt 13 I2C0 */
    PLIC_I2C1_IRQn           = 14,               /*!< Device external Interrupt 14 I2C1 */
    PLIC_GPIOA_IRQn          = 15,               /*!< Device external Interrupt 15 GPIOA */
    PLIC_GPIOB_IRQn          = 16,               /*!< Device external Interrupt 16 GPIOB */
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
#define __PLIC_INTNUM             17                    /*!< Set to 1 - 1024, total interrupt sources of PLIC Unit */

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
#include "system_hbirdv2.h"                    /*!< hbirdv2 System */


/* ========================================  Start of section using anonymous unions  ======================================== */
#if   defined (__GNUC__)
  /* anonymous unions are enabled by default */
#else
  #warning Not supported compiler type
#endif

#define RTC_FREQ                    32768
// The TIMER frequency is just the RTC frequency
#ifdef SIMULATION_RTL
  #define SOC_TIMER_FREQ            (1000000UL)
#else
  #define SOC_TIMER_FREQ            RTC_FREQ
#endif
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
#define IOF_PWM0_MASK              _AC(0x0000000F, UL)
#define IOF_PWM0_CH0_MASK          _AC(0x00000001, UL)
#define IOF_PWM0_CH1_MASK          _AC(0x00000002, UL)
#define IOF_PWM0_CH2_MASK          _AC(0x00000004, UL)
#define IOF_PWM0_CH3_MASK          _AC(0x00000008, UL)
#define IOF_PWM1_MASK              _AC(0x000000F0, UL)
#define IOF_PWM1_CH0_MASK          _AC(0x00000010, UL)
#define IOF_PWM1_CH1_MASK          _AC(0x00000020, UL)
#define IOF_PWM1_CH2_MASK          _AC(0x00000040, UL)
#define IOF_PWM1_CH3_MASK          _AC(0x00000080, UL)
#define IOF_PWM2_MASK              _AC(0x0000000F, UL)
#define IOF_PWM2_CH0_MASK          _AC(0x00000001, UL)
#define IOF_PWM2_CH1_MASK          _AC(0x00000002, UL)
#define IOF_PWM2_CH2_MASK          _AC(0x00000004, UL)
#define IOF_PWM2_CH3_MASK          _AC(0x00000008, UL)
#define IOF_PWM3_MASK              _AC(0x000000F0, UL)
#define IOF_PWM3_CH0_MASK          _AC(0x00000010, UL)
#define IOF_PWM3_CH1_MASK          _AC(0x00000020, UL)
#define IOF_PWM3_CH2_MASK          _AC(0x00000040, UL)
#define IOF_PWM3_CH3_MASK          _AC(0x00000080, UL)

#define IOF_SPI_MASK              _AC(0x00000F00,UL)
#define IOF_QSPI_MASK             _AC(0x00003F00,UL)
#define IOF_SPI_SCK               (8u)
#define IOF_SPI_SS0               (9u)
#define IOF_SPI_MOSI              (10u)
#define IOF_SPI_MISO              (11u)
#define IOF_SPI_DQ0               (10u)
#define IOF_SPI_DQ1               (11u)
#define IOF_SPI_DQ2               (12u)
#define IOF_SPI_DQ3               (13u)

#define IOF_I2C_MASK              _AC(0x0000C000, UL)
#define IOF_I2C_SCL               (14u)
#define IOF_I2C_SDA               (15u)

#define IOF_UART_MASK             _AC(0x00030000, UL)
#define IOF_UART_RX               (16u)
#define IOF_UART_TX               (17u)

#define IOF_UART2_MASK             _AC(0x000C0000, UL)
#define IOF_UART2_RX               (18u)
#define IOF_UART2_TX               (19u)

// Interrupt Handler Definitions
#define SOC_MTIMER_HANDLER          core_mtip_handler
#define SOC_SOFTINT_HANDLER         core_msip_handler

#define GPIO_BIT_ALL_ZERO           (0x0)
#define GPIO_BIT_ALL_ONE            (0xFFFFFFFF)

/**
  * @brief GPIO
  */
typedef struct {  /*!< GPIO Structure */
    __IOM uint32_t PADDIR;
    __IOM uint32_t PADIN;
    __IOM uint32_t PADOUT;
    __IOM uint32_t INTEN;
    __IOM uint32_t INTTYPE0;
    __IOM uint32_t INTTYPE1;
    __IOM uint32_t INTSTATUS;
    __IOM uint32_t IOFCFG;
} GPIO_TypeDef;

/**
  * @brief UART
  */
typedef struct {
    union {
        __IOM uint32_t RBR;
        __IOM uint32_t DLL;
        __IOM uint32_t THR;
    };
    union {
        __IOM uint32_t DLM;
        __IOM uint32_t IER;
    };
    union {
        __IOM uint32_t IIR;
        __IOM uint32_t FCR;
    };
    __IOM uint32_t LCR;
    __IOM uint32_t MCR;
    __IOM uint32_t LSR;
    __IOM uint32_t MSR;
    __IOM uint32_t SCR;
} UART_TypeDef;

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
  * @brief SPI
  */
typedef struct {
    __IOM uint32_t STATUS;
    __IOM uint32_t CLKDIV;
    __IOM uint32_t SPICMD;
    __IOM uint32_t SPIADR;
    __IOM uint32_t SPILEN;
    __IOM uint32_t SPIDUM;
    __IOM uint32_t TXFIFO;
    __IOM uint32_t Pad;
    __IOM uint32_t RXFIFO;
    __IOM uint32_t INTCFG;
    __IOM uint32_t INTSTA;
} SPI_TypeDef;

/**
  * @brief I2C
  */
typedef struct {
    __IOM uint32_t PRE;
    __IOM uint32_t CTR;
    __IOM uint32_t RX;
    __IOM uint32_t STATUS;
    __IOM uint32_t TX;
    __IOM uint32_t CMD;
} I2C_TypeDef;

/**
  * @brief PWM
  */
typedef enum {
    PWM_TIMER0 = 0,
    PWM_TIMER1 = 1,
    PWM_TIMER2 = 2,
    PWM_TIMER3 = 3,
} PwmTimerNum;

typedef enum {
    PWM_TIMER_TH_CHANNEL0 = 0,
    PWM_TIMER_TH_CHANNEL1 = 1,
    PWM_TIMER_TH_CHANNEL2 = 2,
    PWM_TIMER_TH_CHANNEL3 = 3,
} PwmTimerThChannel;

enum{
    pwm_timer_event0 = 0,
    pwm_timer_event1 ,
    pwm_timer_event2 ,
    pwm_timer_event3 ,
};

typedef enum {
    PWM_TIMER_CMD_START = 0x01,         /* Start counting */
    PWM_TIMER_CMD_STOP  = 0x02,         /* Stop counting */
    PWM_TIMER_CMD_UPD   = 0x04,         /* Update timer params */
    PWM_TIMER_CMD_RST   = 0x08,         /* Reset counter value */
} PwmCounterCmd;

typedef struct {
    unsigned int SelectInputSource:8;    /* Select counting condition */
    unsigned int InputEnableIn:3;        /* Define enable rules:
                                           000, always count (use clock)
                                           001 count when external input is 0
                                           010 count when external input is 1
                                           011 count on rising edge of external
                                           100 count on falling edge of external
                                           101 count on falling and on rising edge of external
                                           */
    unsigned int FllOrRTC:1;        /* Clock input of counter is Fll or RTC */
    unsigned int IncThenDec:1;      /* When counter reaches threshold count down if IncThenDec else return to 0 and ocunt up again */
    unsigned int Pad:3;
    unsigned int PreScaler:8;       /* */
    unsigned int Pad2:8;
} PwmCounterConfig;

typedef struct {
    unsigned int chThreshold:16;        /* Threshold value for the channel of a counter */
    unsigned int chAction:3;
                        /* When counter reaches threshold:
                            000: Set
                            001: Toggle then next is Clear
                            010: Set then Clear
                            011: Toggle
                            100: Clear
                            101: Toggle then next is Set
                            110: Clear then Set
                        */
    unsigned int Pad:13;
} PwmChannelThConfig;

typedef struct{
    unsigned int evt0_sel:4;
    unsigned int evt1_sel:4;
    unsigned int evt2_sel:4;
    unsigned int evt3_sel:4;
    unsigned int evt_en:4;
    unsigned int pad:12;
} PwmTimerEvt;

typedef union{
    PwmCounterConfig       timerConf;
    unsigned int           timerTh;    /* Threshold value for the counter */
    PwmChannelThConfig     ch_ThConfig;
    PwmTimerEvt            timerEvt;
    unsigned int           Raw;
} pwm_timer;

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
#define GPIOA_BASE              (HBIRD_PERIPH_BASE + 0x12000)          /*!< (GPIOA) Base Address */
#define UART0_BASE              (HBIRD_PERIPH_BASE + 0x13000)          /*!< (UART0) Base Address */
#define QSPI0_BASE              (HBIRD_PERIPH_BASE + 0x14000)          /*!< (QSPI0) Base Address */
#define PWM_BASE                (HBIRD_PERIPH_BASE + 0x15000)          /*!< (PWM0) Base Address */
#define UART1_BASE              (HBIRD_PERIPH_BASE + 0x23000)          /*!< (UART1) Base Address */
#define SPI1_BASE               (HBIRD_PERIPH_BASE + 0x24000)          /*!< (QSPI1) Base Address */
#define I2C0_BASE               (HBIRD_PERIPH_BASE + 0x25000)          /*!< (I2C0 Master) Base Address */
#define UART2_BASE              (HBIRD_PERIPH_BASE + 0x33000)          /*!< (UART2) Base Address */
#define SPI2_BASE               (HBIRD_PERIPH_BASE + 0x34000)          /*!< (QSPI2) Base Address */
#define I2C1_BASE               (HBIRD_PERIPH_BASE + 0x35000)          /*!< (I2C1 Master) Base Address */
#define GPIOB_BASE              (HBIRD_PERIPH_BASE + 0x40000)          /*!< (GPIOB) Base Address */

/** @} */ /* End of group Device_Peripheral_peripheralAddr */


/* =========================================================================================================================== */
/* ================                                  Peripheral declaration                                   ================ */
/* =========================================================================================================================== */


/* ToDo: add here your device peripherals pointer definitions
         following is an example for timer */
/** @addtogroup Device_Peripheral_declaration
  * @{
  */
#define GPIOA                   ((GPIO_TypeDef *) GPIOA_BASE)
#define UART0                   ((UART_TypeDef *) UART0_BASE)
#define QSPI0                   ((QSPI_TypeDef *) QSPI0_BASE)
#define PWM                     ((PWM_TypeDef *)  PWM_BASE)
#define UART1                   ((UART_TypeDef *) UART1_BASE)
#define SPI1                    ((SPI_TypeDef *)  SPI1_BASE)
#define I2C0                    ((I2C_TypeDef *)  I2C0_BASE)
#define UART2                   ((UART_TypeDef *) UART2_BASE)
#define SPI2                    ((SPI_TypeDef *)  SPI2_BASE)
#define I2C1                    ((I2C_TypeDef *)  I2C1_BASE)
#define GPIOB                   ((GPIO_TypeDef *) GPIOB_BASE)

#define GPIOA_REG(offset)       _REG32(GPIOA_BASE, offset)
#define UART0_REG(offset)       _REG32(UART0_BASE, offset)
#define QSPI0_REG(offset)       _REG32(QSPI0_BASE, offset)
#define PWM_REG(offset)         _REG32(PWM_BASE,   offset)
#define UART1_REG(offset)       _REG32(UART1_BASE, offset)
#define SPI1_REG(offset)        _REG32(SPI1_BASE,  offset)
#define I2C0_REG(offset)        _REG32(I2C0_BASE,  offset)
#define UART2_REG(offset)       _REG32(UART2_BASE, offset)
#define SPI2_REG(offset)        _REG32(SPI2_BASE,  offset)
#define I2C1_REG(offset)        _REG32(I2C1_BASE,  offset)
#define GPIOB_REG(offset)       _REG32(GPIOB_BASE, offset)

// Misc

#define NUM_GPIO 32

uint32_t get_cpu_freq();
void delay_1ms(uint32_t count);

/** @} */ /* End of group hbirdv2 */

/** @} */ /* End of group HummingBird */

#ifdef __cplusplus
}
#endif

#endif  /* __HBIRDV2_H__ */
