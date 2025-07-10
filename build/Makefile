# Makefile for Raspberry Pi Pinmux Tool
CXX       = g++
CXXFLAGS  = -Wall -std=c++17
SRC       = src/pinmux_tool.cpp
OUT_DIR   = bin
TARGET    = $(OUT_DIR)/pinmux_tool

.PHONY: all clean

all: $(TARGET)

$(TARGET): $(SRC)
    @mkdir -p $(OUT_DIR)
    $(CXX) $(CXXFLAGS) $< -o $@

clean:
    @rm -rf $(OUT_DIR)
