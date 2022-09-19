####################################################################################################
# Silicon Labs common library
####################################################################################################
# base path to common sources in gecko SDK
set(COMMON_BASE "${gecko_sdk_SOURCE_DIR}/platform/common")

add_library(efr32xg23-common STATIC
    ${COMMON_BASE}/src/sl_assert.c
    ${COMMON_BASE}/src/sl_slist.c
    #    ${COMMON_BASE}/src/sl_status.c
)
add_library(${PROJECT_NAME}::efr32xg23-common ALIAS efr32xg23-common)

target_compile_definitions(efr32xg23-common PUBLIC ${EFWB_TARGET_COMPILE_DEFS})
target_include_directories(efr32xg23-common PUBLIC ${COMMON_BASE}/inc)

target_link_libraries(efr32xg23-common PUBLIC ${PROJECT_NAME}::cmsis
    ${PROJECT_NAME}::efr32xg23-device-headers ${PROJECT_NAME}::libc)
