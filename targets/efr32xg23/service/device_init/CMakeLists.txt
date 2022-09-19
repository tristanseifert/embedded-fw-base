####################################################################################################
# Device initialization service
####################################################################################################

set(SRC_BASE "${gecko_sdk_SOURCE_DIR}/platform/service/device_init")

add_library(efr32xg23-service-deviceinit STATIC
    ${SRC_BASE}/src/sl_device_init_dcdc_s2.c
    ${SRC_BASE}/src/sl_device_init_dpll_s2.c
    ${SRC_BASE}/src/sl_device_init_emu_s2.c
    ${SRC_BASE}/src/sl_device_init_hfxo_s2.c
    ${SRC_BASE}/src/sl_device_init_nvic.c
)

add_library(${PROJECT_NAME}::efr32xg23-service-deviceinit ALIAS efr32xg23-service-deviceinit)

target_compile_definitions(efr32xg23-service-deviceinit PUBLIC ${EFWB_TARGET_COMPILE_DEFS})
target_include_directories(efr32xg23-service-deviceinit PUBLIC ${SRC_BASE}/inc)

target_link_libraries(efr32xg23-service-deviceinit PRIVATE ${PROJECT_NAME}::efr32xg23-common)
target_link_libraries(efr32xg23-service-deviceinit PUBLIC ${PROJECT_NAME}::cmsis
    ${PROJECT_NAME}::efr32xg23-device-headers ${PROJECT_NAME}::efr32xg23-common
    ${PROJECT_NAME}::efr32xg23-emlib)

# determine the include directory for initialization
target_include_directories(efr32xg23-service-deviceinit PRIVATE ${EFWB_GECKO_CONFIG_DIR})
