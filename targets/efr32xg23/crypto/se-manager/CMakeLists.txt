####################################################################################################
# Security engine manager
#
# Provides an interface to issue requests to the security manager.
####################################################################################################
set(BASE        "${gecko_sdk_SOURCE_DIR}/util/third_party/crypto/sl_component/se_manager")
set(LIBNAME     "efr32xg23-se-manager")

file(GLOB SRC_FILES ${BASE}/src/*.c)
add_library(${LIBNAME} STATIC ${SRC_FILES})
add_library(${PROJECT_NAME}::${LIBNAME} ALIAS ${LIBNAME})

target_include_directories(${LIBNAME} PUBLIC ${BASE}/inc)
target_compile_definitions(${LIBNAME} PRIVATE ${EFWB_TARGET_COMPILE_DEFS})
# target_include_directories(${LIBNAME} PRIVATE ${EFWB_GECKO_CONFIG_DIR})

target_link_libraries(${LIBNAME} PRIVATE ${PROJECT_NAME}::efr32xg23-device-headers
    ${PROJECT_NAME}::efr32xg23-emdrv-common ${PROJECT_NAME}::efr32xg23-emlib)
target_link_libraries(${LIBNAME} PUBLIC ${PROJECT_NAME}::cmsis)

# silence some warnings
target_compile_options(${LIBNAME} PRIVATE -Wno-cast-qual)
