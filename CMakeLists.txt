# SPDX-License-Identifier: MIT

cmake_minimum_required(VERSION 3.13)

set(CMAKE_EXPORT_COMPILE_COMMANDS TRUE)
set(CMAKE_BUILD_TYPE Debug)

project(vhdl-fuzz LANGUAGES CXX)

# Add interface library "main" to propagate dependencies and compiler settings.
add_library(main INTERFACE)
target_compile_options(main INTERFACE
    -W -Wall -Wextra -Wpedantic -Werror -Wno-unused-variable
)

add_subdirectory(proto)
add_subdirectory(src)
