####################################################################################################
# UART driver
#
# Provides blocking and non-blocking (DMA driven) transfers. The underlying USART, LEUART, or
# ESUART peripherals can be used.
####################################################################################################
set(BASE        "${gecko_sdk_SOURCE_DIR}/platform/emdrv/uartdrv")
set(LIBNAME     "efr32xg23-emdrv-uartdrv")

file(GLOB SRC_FILES ${BASE}/src/*.c)
add_library(${LIBNAME} STATIC ${SRC_FILES})
add_library(${PROJECT_NAME}::${LIBNAME} ALIAS ${LIBNAME})

target_include_directories(${LIBNAME} PUBLIC ${BASE}/inc)

target_link_libraries(${LIBNAME} PRIVATE ${PROJECT_NAME}::efr32xg23-device-headers)
target_link_libraries(${LIBNAME} PUBLIC ${PROJECT_NAME}::efr32xg23-emlib
    ${PROJECT_NAME}::efr32xg23-emdrv-dmadrv ${PROJECT_NAME}::efr32xg23-emdrv-gpiointerrupt)

# TODO: handle the config directory
