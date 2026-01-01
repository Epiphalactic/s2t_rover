cmake_minimum_required(VERSION 3.13)

# Import the Pico SDK
include($ENV{PICO_SDK_PATH}/external/pico_sdk_import.cmake)

project(scout_spine C CXX ASM)
set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

pico_sdk_init()

add_executable(scout_spine main.cpp)

# Link the standard libraries
target_link_libraries(scout_spine pico_stdlib)

# Enable USB output, disable UART output
pico_enable_stdio_usb(scout_spine 1)
pico_enable_stdio_uart(scout_spine 0)

# Create the .uf2 file we need for flashing
pico_add_extra_outputs(scout_spine)