###################################################################################################
# Libraries independent of architecture/platform we'll run on

###############
# Internal C library
add_subdirectory(${CMAKE_CURRENT_LIST_DIR}/libc)
add_library(${PROJECT_NAME}::libc ALIAS libc)

###############
# Embedded template library
option(NO_STL "" ON)

FetchContent_Declare(etl
    GIT_REPOSITORY https://github.com/ETLCPP/etl.git
    GIT_TAG 20.32.1
)
FetchContent_MakeAvailable(etl)
target_compile_options(etl INTERFACE -DETL_NO_STL -DETL_NO_CPP_NAN_SUPPORT)

add_library(${PROJECT_NAME}::etl ALIAS etl)

###############
# TinyCBOR (CBOR encode/decode library)
add_subdirectory(${CMAKE_CURRENT_LIST_DIR}/tinycbor)
add_library(${PROJECT_NAME}::tinycbor ALIAS tinycbor)

###################################################################################################
# Architecture-dependent libraries

# 32-bit ARM
if(${EFWB_TARGET_ARCH} STREQUAL "armv7")
    add_subdirectory(${CMAKE_CURRENT_LIST_DIR}/arm_cmsis)
endif()

###################################################################################################
# Platform-dependent libraries will be defined by the platform code itself, so we have nothing
# more to do here.
