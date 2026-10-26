cmake_minimum_required(VERSION 3.13)

# Board: plain Pico. Change to pico_w / pico2 / pico2_w if the hardware differs.
set(PICO_BOARD pico)

include($ENV{PICO_SDK_PATH}/external/pico_sdk_import.cmake)

project(desk_pico C CXX ASM)
set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)
pico_sdk_init()

add_executable(desk_pico src/main.c)
target_link_libraries(desk_pico pico_stdlib)
pico_enable_stdio_usb(desk_pico 1)
pico_enable_stdio_uart(desk_pico 0)
pico_add_extra_outputs(desk_pico)
