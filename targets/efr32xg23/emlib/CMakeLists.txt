####################################################################################################
# Peripheral support library for EFM32, EZR32 and EFR32 series microcontrollers
#
# TODO: Move this to a common library, if we ever want to support targets other than the
# EFR32xG23 series.
####################################################################################################

# base path to emlib sources in gecko SDK
set(EMLIB_BASE "${gecko_sdk_SOURCE_DIR}/platform/emlib")

file(GLOB SRC_FILES ${EMLIB_BASE}/src/*.c)
add_library(efr32xg23-emlib STATIC ${SRC_FILES})

add_library(${PROJECT_NAME}::efr32xg23-emlib ALIAS efr32xg23-emlib)

target_compile_definitions(efr32xg23-emlib PUBLIC ${EFWB_TARGET_COMPILE_DEFS})
target_include_directories(efr32xg23-emlib PUBLIC ${EMLIB_BASE}/inc)

target_link_libraries(efr32xg23-emlib PUBLIC ${PROJECT_NAME}::cmsis
    ${PROJECT_NAME}::efr32xg23-device-headers ${PROJECT_NAME}::efr32xg23-common)

# silence some warnings
target_compile_options(efr32xg23-emlib PRIVATE -Wno-cast-qual)
