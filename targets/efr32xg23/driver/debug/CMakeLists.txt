####################################################################################################
# Debug driver
#
# Implements support for the ITM/SWO tracing facilities in the Cortex core.
####################################################################################################
set(BASE        "${gecko_sdk_SOURCE_DIR}/platform/driver/debug")
set(LIBNAME     "efr32xg23-driver-debug")

file(GLOB SRC_FILES ${BASE}/src/*.c)
add_library(${LIBNAME} STATIC ${SRC_FILES})
add_library(${PROJECT_NAME}::${LIBNAME} ALIAS ${LIBNAME})

target_include_directories(${LIBNAME} PUBLIC ${BASE}/inc)
target_include_directories(${LIBNAME} PRIVATE ${EFWB_GECKO_CONFIG_DIR})

target_link_libraries(${LIBNAME} PRIVATE ${PROJECT_NAME}::efr32xg23-device-headers)
target_link_libraries(${LIBNAME} PUBLIC ${PROJECT_NAME}::efr32xg23-emlib)

# TODO: handle the config dir
