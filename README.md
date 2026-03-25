# ChibiOS HAL Port for GigaDevice GD32F4xx

Industrial-grade ChibiOS v21.11.4 HAL port for the GigaDevice GD32F4xx microcontroller family,
with primary focus on **GD32F450** (Cortex-M4, 200 MHz, 3 MB Flash, 512 KB SRAM).

Developed as part of a real industrial substation controller project:
IEC 60870-5-101 telecontrol, IEC 61557-12 class 0.5 power quality measurement,
microsecond-accurate discrete input timestamping.

## Status

| Peripheral | Status | Notes |
|------------|--------|-------|
| System clock (HSE 12 MHz → PLL 200 MHz) | ✅ Done | Validated on InLogic PLC3 board |
| GPIO | ✅ Done | All ports, AF mapping |
| SPI + DMA | ✅ Done | SPI1 (measurement), SPI2 (memory) |
| UART | ✅ Done | USART0–USART5 |
| I2C | ✅ Done | I2C0, I2C1 |
| TIM (input capture) | ✅ Done | PPS capture, microsecond timestamping |
| DMA | ✅ Done | All channels, circular mode |
| NVIC | ✅ Done | Priority grouping |
| Backup SRAM | ✅ Done | Battery-backed 4 KB @ 0x40024000 |
| IWDG | ✅ Done | Hardware watchdog |
| GD32E230 sub-port | 🔄 In progress | Cortex-M23, QFN28 |

## Hardware

**Primary development board:** InLogic PLC3 (STM32F407VGT6 footprint, GD32F450VIT6 installed)

GD32F450 is pin-compatible with STM32F407VGT6 at LQFP-100 — same footprint,
same peripheral register map with minor differences documented in `docs/differences.md`.

## Getting Started

```bash
git clone https://github.com/Greeds74/ChibiOS-GD32F4xx
cd ChibiOS-GD32F4xx/demos/GD32F450-InLogic
make
```

Flash with J-Link:
```bash
JLinkExe -CommandFile tools/scripts/flash_jlink.jlink
```

## Key Differences vs STM32F407

See `docs/differences.md` for full details. Critical points:

- RCU (Reset and Clock Unit) register names differ from STM32 RCC
- `SystemCoreClock` initialization requires explicit `SystemInit()` call
- Some DMA channel assignments differ — check `docs/dma_mapping.md`
- Backup SRAM requires `rcu_periph_clock_enable(RCU_BKPSRAM)` + `pmu_backup_write_enable()`

## License

HAL port: **Apache License 2.0** — free for commercial and open source use.

ChibiOS RT kernel: GPL3 (see ChibiOS upstream licensing).

## Acknowledgements

Developed with hardware support from **GigaDevice Semiconductor**.

ChibiOS by Giovanni Di Sirio — https://www.chibios.org

## Author

Mikhail — Independent Embedded Systems Engineer
Industrial Automation & Power Quality Measurement
GitHub: https://github.com/Greeds74
Email: general@plclogic.ru
