cmake_minimum_required(VERSION 3.17)
# include(ARMClang_Cortex-M4.cmake)
# CMSIS_EnableFPU(FALSE)

project(gd32f450zgt6 LANGUAGES C ASM
)
# set(CMAKE_CXX_STANDARD 17)
# set(CMAKE_C_STANDARD 11)
set(CMAKE_DEBUG_POSTFIX d)
add_definitions(-DGD32F450 -DUSE_STDPERIPH_DRIVER)
set(C_TARGET_FLAG --target=arm-arm-none-eabi)
# set(ASM_TARGET_FLAG --target=arm-arm-none-eabi )
# set(LINKER_TARGET_FLAG --cpu=Cortex-M4.fp.sp)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_C_STANDARD 99)
 
set(CROSS_COMPILE_PREFIX arm-none-eabi)
set(CMAKE_C_COMPILER ${CROSS_COMPILE_PREFIX}-gcc)
set(CMAKE_CXX_COMPILER ${CROSS_COMPILE_PREFIX}-g++)
set(CMAKE_ASM_COMPILER ${CROSS_COMPILE_PREFIX}-gcc)
set(CMAKE_OBJCOPY ${CROSS_COMPILE_PREFIX}-objcopy)
set(CMAKE_OBJDUMP ${CROSS_COMPILE_PREFIX}-objdump)
set(CMAKE_SIZE ${CROSS_COMPILE_PREFIX}-size)
set(CMAKE_AR ${CROSS_COMPILE_PREFIX}-ar)

set(CPU "-mcpu=cortex-m4")
set(FLOAT-ABI "")
#NONE for Cortex-M0/M0+/M3
set(FPU "")
set(MCU_FLAGS "${CPU} -mthumb ${FPU} ${FLOAT-ABI}")
set(CMAKE_C_FLAGS "${MCU_FLAGS} -std=gnu99 -Wall -fstack-usage -Wstack-usage=512 -fdata-sections -ffunction-sections -fno-common -fmessage-length=0 ${DBG_FLAGS} " CACHE INTERNAL "C compiler flags")
#CPP 
set(CMAKE_CXX_FLAGS "${MCU_FLAGS} -fno-rtti -fno-exceptions -fno-builtin -Wall -fdata-sections -ffunction-sections ${DBG_FLAGS} " CACHE INTERNAL "Cxx compiler flags")
#ASFLAGS
set(CMAKE_ASM_FLAGS "${MCU_FLAGS} -x assembler-with-cpp ${DBG_FLAGS} ")
set(CMAKE_EXE_LINKER_FLAGS "${MCU_FLAGS} -specs=nosys.specs -specs=nano.specs -Wl,--print-memory-usage,-Map=${PROJECT_NAME}.map,--cref -Wl,--gc-sections" CACHE INTERNAL "Exe linker flags")
set(CMAKE_SHARED_LIBRARY_LINK_C_FLAGS "-lc -lm -lnosys" CACHE INTERNAL "Shared linker flags")
# for use printf & scanf with float
set(COMMON_FLAGS "-specs=nosys.specs -specs=nano.specs -u _printf_float -u _scanf_float")

#Uncomment for hardware floating point
# add_compile_definitions(ARM_MATH_CM4;ARM_MATH_MATRIX_CHECK;ARM_MATH_ROUNDING)
# add_compile_options(-mfloat-abi=hard -mfpu=fpv4-sp-d16)
# add_link_options(-mfloat-abi=hard -mfpu=fpv4-sp-d16)

#Uncomment for software floating point
#add_compile_options(-mfloat-abi=soft)
# add_compile_options(-mcpu=cortex-m4 -mthumb -mthumb-interwork)
# add_compile_options(-ffunction-sections -fdata-sections -fno-common -fmessage-length=0)

# uncomment to mitigate c++17 absolute addresses warnings
#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-register")
if ("${CMAKE_BUILD_TYPE}" STREQUAL "Release")
    message(STATUS "Maximum optimization for speed")
    add_compile_options(-Ofast)
elseif ("${CMAKE_BUILD_TYPE}" STREQUAL "RelWithDebInfo")
    message(STATUS "Maximum optimization for speed, debug info included")
    add_compile_options(-Ofast -g)
elseif ("${CMAKE_BUILD_TYPE}" STREQUAL "MinSizeRel")
    message(STATUS "Maximum optimization for size")
    add_compile_options(-Os)
else ()
    message(STATUS "Minimal optimization, debug info included")
    add_compile_options(-Og -g)
endif ()

add_compile_options(-Og)
set(ASM_SOURCES ${PROJECT_SOURCE_DIR}/../Firmware/CMSIS/GD/GD32F4xx/Source/GCC/startup_gd32f450_470.S)

file(GLOB   SOURCES 
    ${PROJECT_SOURCE_DIR}/../Firmware/CMSIS/GD/GD32F4xx/Source/system_gd32f4xx.c
    ${PROJECT_SOURCE_DIR}/../Firmware/GD32F4xx_standard_peripheral/Source/gd32f4xx_gpio.c
    ${PROJECT_SOURCE_DIR}/../Firmware/GD32F4xx_standard_peripheral/Source/gd32f4xx_timer.c
    ${PROJECT_SOURCE_DIR}/../Firmware/GD32F4xx_standard_peripheral/Source/gd32f4xx_rcu.c
    ${PROJECT_SOURCE_DIR}/../Firmware/GD32F4xx_standard_peripheral/Source/gd32f4xx_usart.c
    ${PROJECT_SOURCE_DIR}/../Firmware/GD32F4xx_standard_peripheral/Source/gd32f4xx_spi.c
    ${PROJECT_SOURCE_DIR}/../Firmware/GD32F4xx_standard_peripheral/Source/gd32f4xx_adc.c
    ${PROJECT_SOURCE_DIR}/../Firmware/GD32F4xx_standard_peripheral/Source/gd32f4xx_exti.c
    ${PROJECT_SOURCE_DIR}/../Firmware/GD32F4xx_standard_peripheral/Source/gd32f4xx_misc.c
    ${PROJECT_SOURCE_DIR}/../Firmware/GD32F4xx_standard_peripheral/Source/gd32f4xx_crc.c
    ${PROJECT_SOURCE_DIR}/../Firmware/GD32F4xx_standard_peripheral/Source/gd32f4xx_dac.c
    ${PROJECT_SOURCE_DIR}/../Firmware/GD32F4xx_standard_peripheral/Source/gd32f4xx_tli.c
    ${PROJECT_SOURCE_DIR}/../Firmware/GD32F4xx_standard_peripheral/Source/gd32f4xx_exmc.c
    ${PROJECT_SOURCE_DIR}/Hardware/key/key.c
    ${PROJECT_SOURCE_DIR}/Hardware/LED/led.c
    ${PROJECT_SOURCE_DIR}/Hardware/LCD/lcd.c
    ${PROJECT_SOURCE_DIR}/Hardware/LCD/pic_480800.c
    ${PROJECT_SOURCE_DIR}/Hardware/touch/touch.c
    ${PROJECT_SOURCE_DIR}/Hardware/usart0/usart0.c
    ${PROJECT_SOURCE_DIR}/User/gd32f4xx_it.c
    ${PROJECT_SOURCE_DIR}/User/systick.c
    ${PROJECT_SOURCE_DIR}/User/main.c
    ${PROJECT_SOURCE_DIR}/../Firmware/CMSIS/GD/GD32F4xx/Source/GCC/startup_gd32f450_470.S
    )
include_directories(
    ${PROJECT_SOURCE_DIR}/../Firmware/GD32F4xx_standard_peripheral/Include 
    ${PROJECT_SOURCE_DIR}/../Firmware/CMSIS/Include 
    ${PROJECT_SOURCE_DIR}/../Firmware/CMSIS/GD/GD32F4xx/Include
    ${PROJECT_SOURCE_DIR}/../Firmware/CMSIS 
    ${PROJECT_SOURCE_DIR}/../Firmware/GD32F4xx_usb_library/device/class/audio/Include
    ${PROJECT_SOURCE_DIR}/Hardware/usart0 
    ${PROJECT_SOURCE_DIR}/Hardware/LCD 
    ${PROJECT_SOURCE_DIR}/Hardware/touch 
    ${PROJECT_SOURCE_DIR}/Hardware/LED 
    ${PROJECT_SOURCE_DIR}/Hardware/SDRAM 
    ${PROJECT_SOURCE_DIR}/Hardware/key 
    ${PROJECT_SOURCE_DIR}/Hardware/RGB 
    ${PROJECT_SOURCE_DIR}/User
    )
set(LINKER_SCRIPT ${CMAKE_SOURCE_DIR}/../Firmware/Ld/Link.ld)

add_executable(
    ${PROJECT_NAME}.elf 
    ${SOURCES} 
)
add_link_options(-Wl,-gc-sections,--print-memory-usage,-Map=${PROJECT_BINARY_DIR}/${PROJECT_NAME}.map)
# add_link_options(-mcpu=cortex-m4 -mthumb -mthumb-interwork)
add_link_options(-T ${LINKER_SCRIPT})

set_target_properties(${PROJECT_NAME}.elf PROPERTIES LINK_FLAGS "-T ${LINKER_SCRIPT}")
# set_property(SOURCE ${ASM_SOURCES} PROPERTY LANGUAGE ASM)
add_custom_command(TARGET ${PROJECT_NAME}.elf  POST_BUILD COMMAND scp -P 613 ${PROJECT_NAME}.elf proxy:/mnt/z/)