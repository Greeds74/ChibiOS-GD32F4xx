/*
    ChibiOS HAL port for GigaDevice GD32F4xx
    Copyright (C) 2024 Mikhail (Greeds74)
    github.com/Greeds74/ChibiOS-GD32F4xx

    Licensed under the Apache License, Version 2.0 (the "License");
    you may not use this file except in compliance with the License.
    You may obtain a copy of the License at

        http://www.apache.org/licenses/LICENSE-2.0
*/

/**
 * @file    GD32F4/hal_lld.h
 * @brief   GD32F4xx HAL subsystem low level driver header.
 * @note    GD32F450 is register-compatible with STM32F407 with differences
 *          documented in docs/differences.md
 */

#ifndef HAL_LLD_H
#define HAL_LLD_H

#include "gd32f4xx.h"
#include "nvic.h"

/*===========================================================================*/
/* Driver constants.                                                         */
/*===========================================================================*/

/**
 * @name    Platform identification macros
 */
#if defined(GD32F450) || defined(__DOXYGEN__)
#define PLATFORM_NAME           "GD32F450"
#define GD32F4XX
#endif

/**
 * @name    Absolute Maximum Ratings
 */
#define GD32_SYSCLK_MAX         200000000UL   /**< Max system clock: 200 MHz  */
#define GD32_HSECLK_MAX         25000000UL    /**< Max HSE: 25 MHz            */
#define GD32_HSECLK_MIN         4000000UL     /**< Min HSE: 4 MHz             */
#define GD32_LSECLK             32768UL       /**< LSE: 32.768 kHz            */
#define GD32_HSECLK             12000000UL    /**< HSE: 12 MHz (board crystal)*/

/**
 * @name    Flash wait states for 200 MHz operation (3.3V supply)
 *          GD32F450 datasheet Table 2: 6 wait states required at 168-200 MHz
 */
#define GD32_FLASH_WS_200MHZ    6U

/**
 * @name    PLL configuration for 12 MHz HSE -> 200 MHz SYSCLK
 *          PLLM=6, PLLN=200, PLLP=2 -> VCO=400 MHz, SYSCLK=200 MHz
 *          USB/SDIO PLL48CK: PLLQ=8 -> 50 MHz (not 48 MHz, USB requires separate config)
 */
#define GD32_PLLM_VALUE         6U
#define GD32_PLLN_VALUE         200U
#define GD32_PLLP_VALUE         2U
#define GD32_PLLQ_VALUE         8U

/**
 * @name    Backup SRAM
 *          4 KB battery-backed SRAM at 0x40024000
 *          Survives power loss when VBAT is connected
 */
#define GD32_BACKUP_SRAM_BASE   0x40024000UL
#define GD32_BACKUP_SRAM_SIZE   4096U

/*===========================================================================*/
/* Driver pre-compile time settings.                                         */
/*===========================================================================*/

/**
 * @name    GD32F4xx configuration settings
 */

/**
 * @brief   Disables the RCU initialization in the HAL.
 */
#if !defined(GD32_NO_INIT) || defined(__DOXYGEN__)
#define GD32_NO_INIT            FALSE
#endif

/**
 * @brief   SYSCLK source selection (HSE+PLL recommended for industrial use).
 */
#if !defined(GD32_SW) || defined(__DOXYGEN__)
#define GD32_SW                 GD32_SW_PLL
#endif

/*===========================================================================*/
/* Derived constants and error checks.                                       */
/*===========================================================================*/

#if GD32_SW == GD32_SW_PLL
  #define GD32_SYSCLK   (GD32_HSECLK / GD32_PLLM_VALUE * GD32_PLLN_VALUE / GD32_PLLP_VALUE)
  #if GD32_SYSCLK > GD32_SYSCLK_MAX
    #error "GD32_SYSCLK exceeds maximum rated frequency (200 MHz)"
  #endif
#endif

/*===========================================================================*/
/* Driver data structures and types.                                         */
/*===========================================================================*/

/*===========================================================================*/
/* Driver macros.                                                             */
/*===========================================================================*/

/**
 * @brief   Enable write access to Backup SRAM.
 * @note    Call once at startup before writing to 0x40024000.
 */
#define GD32_BACKUP_SRAM_ENABLE() do {                    \
  rcu_periph_clock_enable(RCU_PMU);                       \
  pmu_backup_write_enable();                              \
  rcu_periph_clock_enable(RCU_BKPSRAM);                   \
} while(0)

/*===========================================================================*/
/* External declarations.                                                    */
/*===========================================================================*/

#ifdef __cplusplus
extern "C" {
#endif
  void hal_lld_init(void);
  void gd32_clock_init(void);
#ifdef __cplusplus
}
#endif

#endif /* HAL_LLD_H */
