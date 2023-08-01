####################################################################################################
# FreeRTOS
#
# The FreeRTOS kernel, and a few additional bonus components.
#
# Note: To use this component, you must at least specify the `FREERTOS_CONFIG_FILE_DIRECTORY`
# configuration variable.
#
# Additional configuration is as default for the FreeRTOS CMake build.
####################################################################################################
# if no heap mode is specified, wrap the C library malloc/free calls
if(NOT DEFINED FREERTOS_HEAP)
    set(FREERTOS_HEAP "3" CACHE STRING "")
    message(AUTHOR_WARNING "No FREERTOS_HEAP variable specified, defaulting to wrapping C library")
endif()

FetchContent_Declare(FreeRTOS-Kernel
    GIT_REPOSITORY https://github.com/FreeRTOS/FreeRTOS-Kernel.git
    # v10.6.0
    GIT_TAG V10.6.0
)
FetchContent_MakeAvailable(FreeRTOS-Kernel)

target_link_libraries(freertos_kernel PUBLIC ${PROJECT_NAME}::libc ${EFWB_TARGET_LIBS})
add_library(${PROJECT_NAME}::FreeRTOS ALIAS freertos_kernel)

####################################################################################################
# Supporting library to provide a CMSIS-RTOS2 compliant interface to FreeRTOS
#
# This uses the ARM-provided wrappers around FreeRTOS. It's packaged as a library that contains all
# of the wrapper code, which will in turn pull in FreeRTOS and the CMSIS-RTOS2 headers into the
# project.
#
# Sources currently in the `cmsis-rtos2` directory correspond to the ARM release for FreeRTOS
# v10.4.3.
add_library(FreeRTOS-CMSIS STATIC
    ${CMAKE_CURRENT_LIST_DIR}/cmsis-rtos2/cmsis_os2.c
)
target_include_directories(FreeRTOS-CMSIS PUBLIC ${CMAKE_CURRENT_LIST_DIR}/cmsis-rtos2)
target_link_libraries(FreeRTOS-CMSIS PUBLIC ${PROJECT_NAME}::FreeRTOS
    ${PROJECT_NAME}::cmsis-rtos2)
add_library(${PROJECT_NAME}::FreeRTOS-CMSIS ALIAS FreeRTOS-CMSIS)
