cmake_minimum_required(VERSION 3.19.0)
file(GLOB_RECURSE XMCU_SOC_SRC "${CMAKE_CURRENT_LIST_DIR}/*.cpp" "${CMAKE_CURRENT_LIST_DIR}/*.c" "${CMAKE_CURRENT_LIST_DIR}/*.asm")

if (XMCU_SOC_MODEL STREQUAL "XMCU_SOC_MODEL_STM32L010F4P6")
    add_compile_definitions("XMCU_SOC_MODEL_STM32L010F4P6" "STM32L010x4")
endif()

add_compile_options(-mcpu=cortex-m0plus)

add_library(XMCU_SOC OBJECT ${XMCU_SOC_SRC})
target_include_directories(XMCU_SOC PRIVATE
                                    ${XMCU_PATH}
                                    ${CMAKE_CURRENT_LIST_DIR}
                                    ${XMCU_PATH}/soc/ST/arm/CMSIS/Include ${XMCU_PATH}/soc/ST/arm/CMSIS/Device/ST/STM32L0xx/Include)