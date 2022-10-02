####################################################################################################
# Security engine manager
#
# Provides an interface to issue requests to the security manager. This assumes you're using
# FreeRTOS (for the OSAL layer)
####################################################################################################
set(BASE        "${gecko_sdk_SOURCE_DIR}/util/third_party/crypto/sl_component/se_manager")
set(LIBNAME     "efr32xg23-se-manager")

file(GLOB SRC_FILES ${BASE}/src/*.c)
add_library(${LIBNAME} STATIC ${SRC_FILES})
add_library(${PROJECT_NAME}::${LIBNAME} ALIAS ${LIBNAME})

target_include_directories(${LIBNAME} PUBLIC ${BASE}/inc)
target_compile_definitions(${LIBNAME} PRIVATE ${EFWB_TARGET_COMPILE_DEFS})

# force a custom config (to allow threading wrappers)
target_include_directories(${LIBNAME} PRIVATE ${EFWB_GECKO_CONFIG_DIR})
target_compile_definitions(${LIBNAME} PUBLIC SE_MANAGER_CONFIG_FILE="efwb_se_manager_config.h")
# then link with FreeRTOS (so we can use threading support)
target_link_libraries(${LIBNAME} PUBLIC ${PROJECT_NAME}::FreeRTOS-CMSIS)
target_include_directories(${LIBNAME} PRIVATE ${FREERTOS_CONFIG_FILE_DIRECTORY})

target_link_libraries(${LIBNAME} PRIVATE ${PROJECT_NAME}::efr32xg23-device-headers
    ${PROJECT_NAME}::efr32xg23-emdrv-common ${PROJECT_NAME}::efr32xg23-emlib)
target_link_libraries(${LIBNAME} PUBLIC ${PROJECT_NAME}::cmsis)

# silence some warnings
target_compile_options(${LIBNAME} PRIVATE -Wno-cast-qual)
