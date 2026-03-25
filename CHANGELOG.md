# Changelog

All notable changes to this project will be documented in this file.

## [Unreleased]

### Added
- Initial HAL port skeleton for GD32F450
- System clock configuration: HSE 12 MHz → PLL 200 MHz
- GPIO driver (all ports, alternate function mapping)
- SPI driver with DMA support (SPI1 for measurement, SPI2 for memory)
- UART driver (USART0–USART5)
- I2C driver (I2C0, I2C1)
- Timer input capture (PPS signal, microsecond timestamping)
- Backup SRAM enable macro and documentation
- IWDG (hardware watchdog) integration
- Demo project for InLogic PLC3 board (GD32F450VIT6)
- J-Link flash script (compatible with HLINK V9.45 clone)
- Differences documentation vs STM32F407
- GD32E230 sub-port (work in progress)

### Notes
- Validated on real industrial substation controller hardware
- IEC 60870-5-101 + IEC 61557-12 class 0.5 application context
