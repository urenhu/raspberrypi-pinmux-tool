# Raspberry Pi Pinmux Tool 🧰

A CLI utility to interactively configure UART, SPI, I2C, and GPIO pins on Raspberry Pi 4 (and Compute Module). Helps developers using QNX or Linux to map pins intuitively with device tree overlays.

## Features
- List available pins per peripheral (UART4, UART5, SPI0/1, I2C0/1)
- Choose alternate functions (ALT0, ALT3, ALT4)
- Apply overlays dynamically (via `dtoverlay`)
- Expandable peripheral database

## Build
```bash
make
