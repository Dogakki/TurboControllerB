cmake_minimum_required(VERSION 3.22)
enable_language(C ASM)

set(MX_Defines_Syms
	USE_HAL_DRIVER
	STM32F412Cx
    $<$<CONFIG:Debug>:DEBUG>
)

set(MX_Include_Dirs
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Core/Inc
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Config
    ${CMAKE_CURRENT_SOURCE_DIR}/../../BSP
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Components/drv8311
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Components/max6675
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Components/ina199
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Modules/motor
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Modules/valve
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Modules/ignition
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Modules/sensor
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Modules/safety
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Modules/sub_enable
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Services
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Protocol
    ${CMAKE_CURRENT_SOURCE_DIR}/../../RTOS
    ${CMAKE_CURRENT_SOURCE_DIR}/../../App
    C:/Users/97846/STM32Cube/Repository/STM32Cube_FW_F4_V1.28.3/Drivers/STM32F4xx_HAL_Driver/Inc
    C:/Users/97846/STM32Cube/Repository/STM32Cube_FW_F4_V1.28.3/Drivers/STM32F4xx_HAL_Driver/Inc/Legacy
    C:/Users/97846/STM32Cube/Repository/STM32Cube_FW_F4_V1.28.3/Middlewares/Third_Party/FreeRTOS/Source/include
    C:/Users/97846/STM32Cube/Repository/STM32Cube_FW_F4_V1.28.3/Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2
    C:/Users/97846/STM32Cube/Repository/STM32Cube_FW_F4_V1.28.3/Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F
    C:/Users/97846/STM32Cube/Repository/STM32Cube_FW_F4_V1.28.3/Drivers/CMSIS/Device/ST/STM32F4xx/Include
    C:/Users/97846/STM32Cube/Repository/STM32Cube_FW_F4_V1.28.3/Drivers/CMSIS/Include
)

# CubeMX-generated application sources
set(MX_Application_Src
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Core/Src/main.c
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Core/Src/gpio.c
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Core/Src/freertos.c
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Core/Src/adc.c
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Core/Src/can.c
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Core/Src/spi.c
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Core/Src/tim.c
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Core/Src/usart.c
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Core/Src/stm32f4xx_it.c
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Core/Src/stm32f4xx_hal_msp.c
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Core/Src/sysmem.c
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Core/Src/syscalls.c
    ${CMAKE_CURRENT_SOURCE_DIR}/../../startup_stm32f412cx.s
    # BSP
    ${CMAKE_CURRENT_SOURCE_DIR}/../../BSP/bsp.c
    ${CMAKE_CURRENT_SOURCE_DIR}/../../BSP/bsp_gpio.c
    ${CMAKE_CURRENT_SOURCE_DIR}/../../BSP/bsp_can.c
    ${CMAKE_CURRENT_SOURCE_DIR}/../../BSP/bsp_uart.c
    ${CMAKE_CURRENT_SOURCE_DIR}/../../BSP/bsp_adc.c
    ${CMAKE_CURRENT_SOURCE_DIR}/../../BSP/bsp_pwm.c
    ${CMAKE_CURRENT_SOURCE_DIR}/../../BSP/bsp_spi.c
    ${CMAKE_CURRENT_SOURCE_DIR}/../../BSP/bsp_tim.c
    ${CMAKE_CURRENT_SOURCE_DIR}/../../BSP/bsp_power.c
    # Components
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Components/drv8311/drv8311.c
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Components/max6675/max6675.c
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Components/ina199/ina199.c
    # Modules
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Modules/motor/motor.c
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Modules/valve/valve.c
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Modules/ignition/ignition.c
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Modules/sensor/sensor.c
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Modules/sensor/rpm.c
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Modules/safety/safety.c
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Modules/sub_enable/sub_enable.c
    # Services
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Services/service_log.c
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Services/service_fault.c
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Services/service_param.c
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Services/service_watchdog.c
    # Protocol
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Protocol/protocol_can.c
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Protocol/protocol_debug.c
    # RTOS
    ${CMAKE_CURRENT_SOURCE_DIR}/../../RTOS/rtos.c
    ${CMAKE_CURRENT_SOURCE_DIR}/../../RTOS/rtos_mutex.c
    ${CMAKE_CURRENT_SOURCE_DIR}/../../RTOS/rtos_queues.c
    ${CMAKE_CURRENT_SOURCE_DIR}/../../RTOS/rtos_events.c
    ${CMAKE_CURRENT_SOURCE_DIR}/../../RTOS/rtos_tasks.c
    ${CMAKE_CURRENT_SOURCE_DIR}/../../RTOS/rtos_timer.c
    # App
    ${CMAKE_CURRENT_SOURCE_DIR}/../../App/app_init.c
    ${CMAKE_CURRENT_SOURCE_DIR}/../../App/app_main.c
    ${CMAKE_CURRENT_SOURCE_DIR}/../../App/app_tasks.c
)

# STM32 HAL/LL Drivers
set(STM32_Drivers_Src
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Core/Src/system_stm32f4xx.c
    C:/Users/97846/STM32Cube/Repository/STM32Cube_FW_F4_V1.28.3/Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_adc.c
    C:/Users/97846/STM32Cube/Repository/STM32Cube_FW_F4_V1.28.3/Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_adc_ex.c
    C:/Users/97846/STM32Cube/Repository/STM32Cube_FW_F4_V1.28.3/Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_rcc.c
    C:/Users/97846/STM32Cube/Repository/STM32Cube_FW_F4_V1.28.3/Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_rcc_ex.c
    C:/Users/97846/STM32Cube/Repository/STM32Cube_FW_F4_V1.28.3/Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_flash.c
    C:/Users/97846/STM32Cube/Repository/STM32Cube_FW_F4_V1.28.3/Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_flash_ex.c
    C:/Users/97846/STM32Cube/Repository/STM32Cube_FW_F4_V1.28.3/Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_flash_ramfunc.c
    C:/Users/97846/STM32Cube/Repository/STM32Cube_FW_F4_V1.28.3/Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_gpio.c
    C:/Users/97846/STM32Cube/Repository/STM32Cube_FW_F4_V1.28.3/Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_dma_ex.c
    C:/Users/97846/STM32Cube/Repository/STM32Cube_FW_F4_V1.28.3/Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_dma.c
    C:/Users/97846/STM32Cube/Repository/STM32Cube_FW_F4_V1.28.3/Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_pwr.c
    C:/Users/97846/STM32Cube/Repository/STM32Cube_FW_F4_V1.28.3/Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_pwr_ex.c
    C:/Users/97846/STM32Cube/Repository/STM32Cube_FW_F4_V1.28.3/Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_cortex.c
    C:/Users/97846/STM32Cube/Repository/STM32Cube_FW_F4_V1.28.3/Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal.c
    C:/Users/97846/STM32Cube/Repository/STM32Cube_FW_F4_V1.28.3/Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_exti.c
    C:/Users/97846/STM32Cube/Repository/STM32Cube_FW_F4_V1.28.3/Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_can.c
    C:/Users/97846/STM32Cube/Repository/STM32Cube_FW_F4_V1.28.3/Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_spi.c
    C:/Users/97846/STM32Cube/Repository/STM32Cube_FW_F4_V1.28.3/Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_tim.c
    C:/Users/97846/STM32Cube/Repository/STM32Cube_FW_F4_V1.28.3/Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_tim_ex.c
    C:/Users/97846/STM32Cube/Repository/STM32Cube_FW_F4_V1.28.3/Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_uart.c
)

set(FreeRTOS_Src
    C:/Users/97846/STM32Cube/Repository/STM32Cube_FW_F4_V1.28.3/Middlewares/Third_Party/FreeRTOS/Source/croutine.c
    C:/Users/97846/STM32Cube/Repository/STM32Cube_FW_F4_V1.28.3/Middlewares/Third_Party/FreeRTOS/Source/event_groups.c
    C:/Users/97846/STM32Cube/Repository/STM32Cube_FW_F4_V1.28.3/Middlewares/Third_Party/FreeRTOS/Source/list.c
    C:/Users/97846/STM32Cube/Repository/STM32Cube_FW_F4_V1.28.3/Middlewares/Third_Party/FreeRTOS/Source/queue.c
    C:/Users/97846/STM32Cube/Repository/STM32Cube_FW_F4_V1.28.3/Middlewares/Third_Party/FreeRTOS/Source/stream_buffer.c
    C:/Users/97846/STM32Cube/Repository/STM32Cube_FW_F4_V1.28.3/Middlewares/Third_Party/FreeRTOS/Source/tasks.c
    C:/Users/97846/STM32Cube/Repository/STM32Cube_FW_F4_V1.28.3/Middlewares/Third_Party/FreeRTOS/Source/timers.c
    C:/Users/97846/STM32Cube/Repository/STM32Cube_FW_F4_V1.28.3/Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2/cmsis_os2.c
    C:/Users/97846/STM32Cube/Repository/STM32Cube_FW_F4_V1.28.3/Middlewares/Third_Party/FreeRTOS/Source/portable/MemMang/heap_4.c
    C:/Users/97846/STM32Cube/Repository/STM32Cube_FW_F4_V1.28.3/Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F/port.c
)

set(MX_LINK_DIRS)
set(MX_LINK_LIBS STM32_Drivers ${TOOLCHAIN_LINK_LIBRARIES} FreeRTOS)

add_library(stm32cubemx INTERFACE)
target_include_directories(stm32cubemx INTERFACE ${MX_Include_Dirs})
target_compile_definitions(stm32cubemx INTERFACE ${MX_Defines_Syms})

add_library(STM32_Drivers OBJECT)
target_sources(STM32_Drivers PRIVATE ${STM32_Drivers_Src})
target_link_libraries(STM32_Drivers PUBLIC stm32cubemx)

add_library(FreeRTOS OBJECT)
target_sources(FreeRTOS PRIVATE ${FreeRTOS_Src})
target_link_libraries(FreeRTOS PUBLIC stm32cubemx)

target_sources(${CMAKE_PROJECT_NAME} PRIVATE ${MX_Application_Src})
target_link_directories(${CMAKE_PROJECT_NAME} PRIVATE ${MX_LINK_DIRS})
target_link_libraries(${CMAKE_PROJECT_NAME} ${MX_LINK_LIBS})
set_target_properties(${CMAKE_PROJECT_NAME} PROPERTIES ADDITIONAL_CLEAN_FILES ${CMAKE_PROJECT_NAME}.map)

if((CMAKE_C_STANDARD EQUAL 90) OR (CMAKE_C_STANDARD EQUAL 99))
    message(ERROR "Generated code requires C11 or higher")
endif()
