###################################################################################################
# Libraries independent of architecture/platform we'll run on
add_subdirectory(${CMAKE_CURRENT_LIST_DIR}/libc)
add_subdirectory(${CMAKE_CURRENT_LIST_DIR}/etl)
add_subdirectory(${CMAKE_CURRENT_LIST_DIR}/spiffs EXCLUDE_FROM_ALL)
add_subdirectory(${CMAKE_CURRENT_LIST_DIR}/tinycbor EXCLUDE_FROM_ALL)
add_subdirectory(${CMAKE_CURRENT_LIST_DIR}/FreeRTOS EXCLUDE_FROM_ALL)

###################################################################################################
# Architecture-dependent libraries

# 32-bit ARM
if(${EFWB_TARGET_ARCH} STREQUAL "armv7")
    add_subdirectory(${CMAKE_CURRENT_LIST_DIR}/arm_cmsis)
endif()

###################################################################################################
# Platform-dependent libraries will be defined by the platform code itself, so we have nothing
# more to do here.
