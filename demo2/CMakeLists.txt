cmake_minimum_required(VERSION 3.16)

project(demo2 LANGUAGES C ASM)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)

add_executable(demo2
    src/main.c
    startup/startup_stm32g474xx.S
)

set_target_properties(demo2 PROPERTIES SUFFIX ".elf")

target_compile_options(demo2 PRIVATE
    -mcpu=cortex-m4
    -mthumb
    -ffreestanding
    -fdata-sections
    -ffunction-sections
    -Wall
    -Wextra
)

target_link_options(demo2 PRIVATE
    -mcpu=cortex-m4
    -mthumb
    -nostdlib
    -Wl,--gc-sections
    -Wl,-Map=${CMAKE_CURRENT_BINARY_DIR}/demo2.map
    -T${CMAKE_CURRENT_SOURCE_DIR}/linker/STM32G474RETx_FLASH.ld
)

add_custom_command(TARGET demo2 POST_BUILD
    COMMAND ${CMAKE_OBJCOPY} -O binary $<TARGET_FILE:demo2>
            ${CMAKE_CURRENT_BINARY_DIR}/demo2.bin
    BYPRODUCTS ${CMAKE_CURRENT_BINARY_DIR}/demo2.bin
    COMMENT "Creating demo2.bin for the Nucleo board"
)
