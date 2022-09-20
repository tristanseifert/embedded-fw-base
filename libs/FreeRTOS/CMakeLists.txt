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
    # v10.5.0
    GIT_TAG 6f63da2
)
FetchContent_MakeAvailable(FreeRTOS-Kernel)

target_link_libraries(freertos_kernel ${PROJECT_NAME}::libc ${EFWB_TARGET_LIBS})
add_library(${PROJECT_NAME}::FreeRTOS ALIAS freertos_kernel)
