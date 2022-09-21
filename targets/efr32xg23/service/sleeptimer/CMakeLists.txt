####################################################################################################
# Low power sleep timer service
####################################################################################################
set(BASE        "${gecko_sdk_SOURCE_DIR}/platform/service/sleeptimer")
set(LIBNAME     "efr32xg23-service-sleeptimer")

file(GLOB SRC_FILES ${BASE}/src/*.c)
add_library(${LIBNAME} STATIC
    ${BASE}/src/sl_sleeptimer_hal_burtc.c
    ${BASE}/src/sl_sleeptimer_hal_sysrtc.c
    ${BASE}/src/sl_sleeptimer.c

    )
add_library(${PROJECT_NAME}::${LIBNAME} ALIAS ${LIBNAME})

target_include_directories(${LIBNAME} PUBLIC ${BASE}/inc)
target_include_directories(${LIBNAME} PRIVATE ${EFWB_GECKO_CONFIG_DIR})

target_link_libraries(${LIBNAME} PRIVATE ${PROJECT_NAME}::efr32xg23-device-headers
    ${PROJECT_NAME}::efr32xg23-emlib ${PROJECT_NAME}::efr32xg23-peripheral-sysrtc)

# silence some warnings
target_compile_options(${LIBNAME} PRIVATE -Wno-cast-qual)
