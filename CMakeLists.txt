cmake_minimum_required(VERSION 3.13)
project(pinmux_tool LANGUAGES CXX)

# Set default build type
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release)
endif()

# QNX-specific settings
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Detect QNX toolchain
if(DEFINED ENV{QNX_HOST} AND DEFINED ENV{QNX_TARGET})
    set(QNX_SYSROOT "$ENV{QNX_TARGET}")
    set(CMAKE_SYSTEM_NAME QNX)
    set(CMAKE_SYSTEM_VERSION 7.1.0)  # Adjust to match your installed QNX SDP version
    set(CMAKE_FIND_ROOT_PATH "${QNX_SYSROOT}")
    set(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)
    set(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
    set(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)
else()
    message(FATAL_ERROR "QNX environment variables (QNX_HOST and QNX_TARGET) not set.")
endif()

# Source and output
set(SRC src/pinmux_tool.cpp)

add_executable(pinmux_tool ${SRC})
