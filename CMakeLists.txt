cmake_minimum_required(VERSION 3.13)

set(PICO_BOARD CACHE STRING pico_w)
set(sdkVersion 2.3.1)
set(toolchainVersion 15_2_Rel1)
set(picotoolVersion 2.3.1)
set(picoVscode ${USERHOME}/.pico-sdk/cmake/pico-vscode.cmake)


include($ENV{PICO_SDK_PATH}/external/pico_sdk_import.cmake)

project(desk_pico C CXX ASM)
set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)
pico_sdk_init()

# TODO - Make sure the file is properly defined and configured with what's needed
add_executable(desk_pico src/main.cpp src/wifi-connector.cpp)
target_link_libraries(desk_pico pico_stdlib)
pico_enable_stdio_usb(desk_pico 1)
pico_enable_stdio_uart(desk_pico 0)
pico_add_extra_outputs(desk_pico)

target_link_libraries(desk_pico
        PRIVATE    
        pico_stdlib
        pico_cyw43_arch_lwip_threadsafe_background 
        pico_lwip_http
        pico_multicore
        pico_status_led
)

pico_add_extra_outputs(desk_pico)