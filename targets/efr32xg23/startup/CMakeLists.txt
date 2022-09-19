####################################################################################################
# Startup code for EFR32xG23 SoCs
#
# This provides the vector table, and the reset handler (which is responsible for initializing the
# C runtime) for the firmware.
####################################################################################################

add_library(efr32xg23-startup STATIC
    Sources/Vectors.c
    Sources/Startup.c
)
add_library(${PROJECT_NAME}::efr32xg23-startup ALIAS efr32xg23-startup)

target_compile_definitions(efr32xg23-startup PUBLIC ${EFWB_TARGET_COMPILE_DEFS})
target_include_directories(efr32xg23-startup PUBLIC ${CMAKE_CURRENT_LIST_DIR}/Includes)

target_link_libraries(efr32xg23-startup PUBLIC ${PROJECT_NAME}::cmsis ${PROJECT_NAME}::efr32xg23-device-headers)
