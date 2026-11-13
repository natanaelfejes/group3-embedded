cmake_minimum_required(VERSION 3.13)

set(PICO_BOARD pico_w)
set(sdkVersion 2.3.1)
set(toolchainVersion 15_2_Rel1)
set(picotoolVersion 2.3.1)
set(picoVscode ${USERHOME}/.pico-sdk/cmake/pico-vscode.cmake)


include(pico_sdk_import.cmake)

if(WIN32)
    set(USERHOME $ENV{USERPROFILE})
else()
    set(USERHOME $ENV{HOME})
endif()

set(sdkVersion 2.3.1)
set(toolchainVersion 15_2_Rel1)
set(picotoolVersion 2.3.1)

set(picoVscode "${USERHOME}/.pico-sdk/cmake/pico-vscode.cmake")

if(EXISTS "${picoVscode}")
    include("${picoVscode}")
endif()

project(desk_pico C CXX ASM)
set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)
pico_sdk_init()

# TODO - Make sure the file is properly defined and configured with what's needed
add_executable(desk_pico src/main.cpp src/wifi-connector.cpp src/desk-height.cpp)

target_link_libraries(desk_pico
        PRIVATE    
        pico_stdlib
        hardware_adc
        pico_cyw43_arch_lwip_threadsafe_background 
        pico_lwip_http
        pico_multicore
        pico_status_led
)

target_include_directories(desk_pico PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}
)

pico_enable_stdio_usb(desk_pico 1)
pico_enable_stdio_uart(desk_pico 0)

pico_add_extra_outputs(desk_pico)