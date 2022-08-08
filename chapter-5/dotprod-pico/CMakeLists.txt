cmake_minimum_required(VERSION 3.18)

include($ENV{PICO_SDK_PATH}/external/pico_sdk_import.cmake)

project(dotprod C CXX ASM)
set(CMAKE_C_STANDARD 11)

#set(PICO_COMPILER_CC  "pico_arm_clang_arm")

pico_sdk_init()

add_executable(${PROJECT_NAME}
            ${PROJECT_NAME}.c systick.c 
            arm_mult_f32.c arm_add_f32.c arm_dot_prod_f32.c
        )

target_include_directories(${PROJECT_NAME} PRIVATE $ENV{HOME}/CMSIS_5/CMSIS/DSP/Include 
                                                  $ENV{HOME}/CMSIS_5/CMSIS/Core/Include
                                                  ) 
set(CMAKE_C_FLAGS_RELEASE "-O3 -DNDEBUG -DARM_MATH_LOOPUNROLL")

# pull in common dependencies
target_link_libraries(${PROJECT_NAME} pico_stdlib)

# enable usb or uart output
pico_enable_stdio_usb(${PROJECT_NAME} 0)
pico_enable_stdio_uart(${PROJECT_NAME} 1)

# create map/bin/hex/uf2 file etc.
pico_add_extra_outputs(${PROJECT_NAME})

