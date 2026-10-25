set(CMAKE_SYSTEM_NAME Generic)
set(CMAKE_SYSTEM_PROCESSOR arm)
set(CMAKE_TRY_COMPILE_TARGET_TYPE STATIC_LIBRARY)

find_program(ARM_NONE_EABI_GCC arm-none-eabi-gcc)
find_program(ARM_NONE_EABI_OBJCOPY arm-none-eabi-objcopy)

if(NOT ARM_NONE_EABI_GCC OR NOT ARM_NONE_EABI_OBJCOPY)
    message(FATAL_ERROR
        "ARM GNU Toolchain not found. Install it and ensure arm-none-eabi-gcc "
        "and arm-none-eabi-objcopy are on PATH.")
endif()

set(CMAKE_C_COMPILER "${ARM_NONE_EABI_GCC}")
set(CMAKE_ASM_COMPILER "${ARM_NONE_EABI_GCC}")
set(CMAKE_OBJCOPY "${ARM_NONE_EABI_OBJCOPY}")
