# GD32F450 vs STM32F407 — Key Differences

This document covers register-level and HAL-level differences discovered
during ChibiOS port development.

## Clock System (RCU vs RCC)

| STM32F407 | GD32F450 | Notes |
|-----------|----------|-------|
| `RCC->CR` | `RCU_CTL` | Clock control register |
| `RCC->CFGR` | `RCU_CFG0` | Clock configuration |
| `RCC->AHB1ENR` | `RCU_AHB1EN` | AHB1 peripheral clock enable |
| `RCC->APB1ENR` | `RCU_APB1EN` | APB1 peripheral clock enable |
| `RCC->APB2ENR` | `RCU_APB2EN` | APB2 peripheral clock enable |

PLL configuration differs — see `os/hal/ports/GD32F4/hal_lld.c` for details.

## Backup SRAM

GD32F450 Backup SRAM (4 KB at 0x40024000) requires explicit enable sequence:

```c
/* Enable PWR clock */
rcu_periph_clock_enable(RCU_PMU);
/* Enable Backup domain write access */
pmu_backup_write_enable();
/* Enable Backup SRAM clock */
rcu_periph_clock_enable(RCU_BKPSRAM);
```

STM32F407 uses identical mechanism but different register names (PWR_CR vs PMU_CTL).

## DMA Channel Mapping

Some DMA channel/stream assignments differ between GD32F450 and STM32F407.
Full mapping table: see `docs/dma_mapping.md`.

## SPI

SPI peripheral register layout is identical. DMA trigger sources differ slightly —
see `os/hal/ports/GD32F4/hal_spi_lld.c`.

## Timers

TIM register layout is identical to STM32F407. Input capture for PPS signal
works without modification on TIM2 CH1.

## USART

Identical register layout. Baud rate calculation formula is the same.

## Known Issues

- GD32F450 errata: avoid consecutive write operations to flash option bytes
  without reset between them.
- At 200 MHz, flash wait states must be set to 6 before PLL switch.
