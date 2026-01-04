cmake_minimum_required(VERSION 3.13)

# Load Pico SDK
include(pico_sdk_import.cmake)

project(scout_spine C CXX ASM)
set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

pico_sdk_init()

# --- TARGET 1: SCOUT SPINE (Main Rover Code) ---
add_executable(scout_spine 
    main.cpp
    proto_crc.cpp
    lib/pico-ssd1306/ssd1306.c
)

target_include_directories(scout_spine PRIVATE 
    ${CMAKE_CURRENT_LIST_DIR}
    ${CMAKE_CURRENT_LIST_DIR}/lib/pico-ssd1306
)

target_link_libraries(scout_spine 
    pico_stdlib 
    hardware_i2c
)

pico_enable_stdio_usb(scout_spine 1)
pico_add_extra_outputs(scout_spine)


# --- TARGET 2: BUS SCANNER (Diagnostic Tool) ---
add_executable(bus_scan scanner.cpp)

target_link_libraries(bus_scan 
    pico_stdlib 
    hardware_i2c
)

pico_enable_stdio_usb(bus_scan 1)
pico_add_extra_outputs(bus_scan)