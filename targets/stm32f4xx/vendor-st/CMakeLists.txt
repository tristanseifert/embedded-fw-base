####################################################################################################
# ST vendor libraries
#
# Export a static library that builds all of the ST vendor code. This is mostly just used for the
# basic peripheral setup/configuration; we don't use their janky HAL layer.
####################################################################################################

add_library(vendor-st STATIC
    # system related routines (setup and clock calculation)
    Sources/Startup/system_stm32f4xx.c

    # low-level HAL drivers
    Sources/hal/stm32f4xx_ll_adc.c
    Sources/hal/stm32f4xx_ll_crc.c
    Sources/hal/stm32f4xx_ll_dac.c
    Sources/hal/stm32f4xx_ll_dma.c
    Sources/hal/stm32f4xx_ll_dma2d.c
    Sources/hal/stm32f4xx_ll_exti.c
    Sources/hal/stm32f4xx_ll_fmc.c
    Sources/hal/stm32f4xx_ll_fmpi2c.c
    Sources/hal/stm32f4xx_ll_fsmc.c
    Sources/hal/stm32f4xx_ll_gpio.c
    Sources/hal/stm32f4xx_ll_i2c.c
    Sources/hal/stm32f4xx_ll_lptim.c
    Sources/hal/stm32f4xx_ll_pwr.c
    Sources/hal/stm32f4xx_ll_rcc.c
    Sources/hal/stm32f4xx_ll_rng.c
    Sources/hal/stm32f4xx_ll_rtc.c
    Sources/hal/stm32f4xx_ll_sdmmc.c
    Sources/hal/stm32f4xx_ll_spi.c
    Sources/hal/stm32f4xx_ll_tim.c
    Sources/hal/stm32f4xx_ll_usart.c
    Sources/hal/stm32f4xx_ll_usb.c
    Sources/hal/stm32f4xx_ll_utils.c
)

# add the high level HAL functions if requested
option(EWFB_STM32_HAL_FULL "Use the full STM32 HAL drivers" OFF)
if(${EWFB_STM32_HAL_FULL})
    target_sources(vendor-st PUBLIC
        Sources/hal/stm32f4xx_hal_can.c
        Sources/hal/stm32f4xx_hal_adc_ex.c
        Sources/hal/stm32f4xx_hal_adc.c
        Sources/hal/stm32f4xx_hal_cec.c
        Sources/hal/stm32f4xx_hal_cortex.c
        Sources/hal/stm32f4xx_hal_crc.c
        Sources/hal/stm32f4xx_hal_cryp_ex.c
        Sources/hal/stm32f4xx_hal_cryp.c
        Sources/hal/stm32f4xx_hal_dac_ex.c
        Sources/hal/stm32f4xx_hal_dac.c
        Sources/hal/stm32f4xx_hal_dcmi_ex.c
        Sources/hal/stm32f4xx_hal_dcmi.c
        Sources/hal/stm32f4xx_hal_dfsdm.c
        Sources/hal/stm32f4xx_hal_dma_ex.c
        Sources/hal/stm32f4xx_hal_dma.c
        Sources/hal/stm32f4xx_hal_dma2d.c
        Sources/hal/stm32f4xx_hal_dsi.c
        Sources/hal/stm32f4xx_hal_eth.c
        Sources/hal/stm32f4xx_hal_exti.c
        Sources/hal/stm32f4xx_hal_flash_ex.c
        Sources/hal/stm32f4xx_hal_flash_ramfunc.c
        Sources/hal/stm32f4xx_hal_flash.c
        Sources/hal/stm32f4xx_hal_fmpi2c_ex.c
        Sources/hal/stm32f4xx_hal_fmpi2c.c
        Sources/hal/stm32f4xx_hal_fmpsmbus_ex.c
        Sources/hal/stm32f4xx_hal_fmpsmbus.c
        Sources/hal/stm32f4xx_hal_gpio.c
        Sources/hal/stm32f4xx_hal_hash_ex.c
        Sources/hal/stm32f4xx_hal_hash.c
        Sources/hal/stm32f4xx_hal_hcd.c
        Sources/hal/stm32f4xx_hal_i2c_ex.c
        Sources/hal/stm32f4xx_hal_i2c.c
        Sources/hal/stm32f4xx_hal_i2s_ex.c
        Sources/hal/stm32f4xx_hal_i2s.c
        Sources/hal/stm32f4xx_hal_irda.c
        Sources/hal/stm32f4xx_hal_iwdg.c
        Sources/hal/stm32f4xx_hal_lptim.c
        Sources/hal/stm32f4xx_hal_ltdc_ex.c
        Sources/hal/stm32f4xx_hal_ltdc.c
        Sources/hal/stm32f4xx_hal_mmc.c
        Sources/hal/stm32f4xx_hal_nand.c
        Sources/hal/stm32f4xx_hal_nor.c
        Sources/hal/stm32f4xx_hal_pccard.c
        Sources/hal/stm32f4xx_hal_pcd_ex.c
        Sources/hal/stm32f4xx_hal_pcd.c
        Sources/hal/stm32f4xx_hal_pwr_ex.c
        Sources/hal/stm32f4xx_hal_pwr.c
        Sources/hal/stm32f4xx_hal_qspi.c
        Sources/hal/stm32f4xx_hal_rcc_ex.c
        Sources/hal/stm32f4xx_hal_rcc.c
        Sources/hal/stm32f4xx_hal_rng.c
        Sources/hal/stm32f4xx_hal_rtc_ex.c
        Sources/hal/stm32f4xx_hal_rtc.c
        Sources/hal/stm32f4xx_hal_sai_ex.c
        Sources/hal/stm32f4xx_hal_sai.c
        Sources/hal/stm32f4xx_hal_sd.c
        Sources/hal/stm32f4xx_hal_sdram.c
        Sources/hal/stm32f4xx_hal_smartcard.c
        Sources/hal/stm32f4xx_hal_smbus.c
        Sources/hal/stm32f4xx_hal_spdifrx.c
        Sources/hal/stm32f4xx_hal_spi.c
        Sources/hal/stm32f4xx_hal_sram.c
        Sources/hal/stm32f4xx_hal_tim_ex.c
        Sources/hal/stm32f4xx_hal_tim.c
        Sources/hal/stm32f4xx_hal_uart.c
        Sources/hal/stm32f4xx_hal_usart.c
        Sources/hal/stm32f4xx_hal_wwdg.c
        Sources/hal/stm32f4xx_hal.c
    )
endif()

add_library(${PROJECT_NAME}::vendor-st-stm32f4 ALIAS vendor-st)

target_compile_definitions(vendor-st PUBLIC ${EFWB_TARGET_COMPILE_DEFS})
target_include_directories(vendor-st PUBLIC ${CMAKE_CURRENT_LIST_DIR}/Includes)

target_include_directories(vendor-st PUBLIC Includes/CMSIS-Device-ST/STM32F4xx/Include)
target_include_directories(vendor-st PUBLIC Includes/config)
target_include_directories(vendor-st PUBLIC Includes/hal)
target_include_directories(vendor-st PUBLIC Includes/Runtime)

target_link_libraries(vendor-st PUBLIC embedded-fw-base::cmsis)

# shut up some errors
target_compile_options(vendor-st PRIVATE -Wno-cast-qual -Wno-parentheses-equality -Wno-unused-but-set-variable)

# enable the low-level drivers
target_compile_definitions(vendor-st PUBLIC USE_FULL_LL_DRIVER)
