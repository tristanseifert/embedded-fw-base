####################################################################################################
# SPI driver
#
# Provides blocking and non-blocking (DMA driven) transfers. Supports EUSART peripherals.
####################################################################################################
set(BASE        "${gecko_sdk_SOURCE_DIR}/platform/emdrv/spidrv")
set(LIBNAME     "efr32xg23-emdrv-spidrv")

file(GLOB SRC_FILES ${BASE}/src/*.c)
add_library(${LIBNAME} STATIC ${SRC_FILES})
add_library(${PROJECT_NAME}::${LIBNAME} ALIAS ${LIBNAME})

target_include_directories(${LIBNAME} PUBLIC ${BASE}/inc)
target_include_directories(${LIBNAME} PRIVATE ${EFWB_GECKO_CONFIG_DIR})

target_link_libraries(${LIBNAME} PRIVATE ${PROJECT_NAME}::efr32xg23-device-headers
    ${PROJECT_NAME}::efr32xg23-emdrv-common)
target_link_libraries(${LIBNAME} PUBLIC ${PROJECT_NAME}::efr32xg23-emlib
    ${PROJECT_NAME}::efr32xg23-emdrv-dmadrv ${PROJECT_NAME}::efr32xg23-emdrv-gpiointerrupt
    ${PROJECT_NAME}::efr32xg23-service-sleeptimer)

# silence some warnings
target_compile_options(${LIBNAME} PRIVATE -Wno-cast-qual -Wno-parentheses-equality)
