# 🧰 Raspberry Pi Pinmux Tool

A lightweight C++ command-line utility to configure UART, SPI, I2C, and GPIO pinmux settings interactively on Raspberry Pi 4 and Compute Module 4. Built for embedded developers working with QNX and Linux platforms.

---

## 🔧 Features

- Interactive CLI pinmux configuration for:
  - `uart4`, `uart5`
  - `spi0`, `spi1`
  - `i2c0`, `i2c1`
- Lists all available GPIO mappings and alternate function modes
- Automatically generates `dtoverlay` commands to apply settings
- Cross-platform compatibility: QNX, Raspberry Pi OS, Linux
- Clean C++17 codebase with support for Make and CMake

---

## 📂 Project Structure

