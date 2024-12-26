#
# Copyright (c) xEmbeddedTools team and contributors.
# Licensed under the Apache License, Version 2.0. See LICENSE file in the project root for details.
#

cmake_minimum_required(VERSION 3.19.0)

if (XMCU_SOC_MODEL STREQUAL "XMCU_SOC_MODEL_STM32L010F4P6")
    file(GLOB_RECURSE XMCU_SOC_SRC 
            "${CMAKE_CURRENT_LIST_DIR}/rm0451/*.cpp" 
            "${CMAKE_CURRENT_LIST_DIR}/rm0451/*.c" 
            "${CMAKE_CURRENT_LIST_DIR}/rm0451/*.asm" 
            "${CMAKE_CURRENT_LIST_DIR}/rm0451/*.hpp"
            "${CMAKE_CURRENT_LIST_DIR}/rm0451/*.h"
            "${XMCU_PATH}/soc/ST/arm/CMSIS/Device/ST/STM32L0xx/Source/Templates/gcc/startup_stm32l010x4.s.s"
            "${XMCU_PATH}/soc/ST/arm/CMSIS/Device/ST/STM32L0xx/Source/Templates/system_stm32l0xx.c")
    set(XMCU_LD_SCRIPT "${XMCU_PATH}/soc/ST/arm/CMSIS/Device/ST/STM32L0xx/Source/Templates/gcc/linker/STM32L010F4Px_FLASH.ld")
    add_library(XMCU_SOC OBJECT ${XMCU_SOC_SRC})
    add_compile_definitions(XMCU_SOC PUBLIC "XMCU_SOC_MODEL_STM32L010F4P6" "STM32L010x4")
endif()

set(CMAKE_C_FLAGS ${CMAKE_C_FLAGS} -mcpu=cortex-m0plus -mthumb)
set(CMAKE_STATIC_LINKER_FLAGS ${CMAKE_STATIC_LINKER_FLAGS} -mcpu=cortex-m0plus -mthumb)

include_directories(XMCU_SOC PRIVATE
                    ${XMCU_PATH}
                    ${CMAKE_CURRENT_LIST_DIR}
                    ${XMCU_PATH}/soc/ST/arm/CMSIS/Include ${XMCU_PATH}/soc/ST/arm/CMSIS/Device/ST/STM32L0xx/Include)