###################################################################################################
# Embedded firmware base
#
# This CMake file defines various targets (under the `efwbase` namespace alias) for embedded
# projects to consume.
###################################################################################################
cmake_minimum_required(VERSION 3.18 FATAL_ERROR)
project(embedded-fw-base VERSION 0.1 LANGUAGES ASM C CXX)

include(ExternalProject)
include(FetchContent)

###################################################################################################
# Set warning levels and language version
# TODO: will these affect the upper level projects also?
set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_compile_options(-Wall -Wmissing-declarations -Wformat=2 -fdiagnostics-color=always
    -ftls-model=initial-exec -Wundef -Wcast-qual -Wwrite-strings)

if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
    add_compile_options(-Werror -Wimplicit-fallthrough -Wno-deprecated-copy -Wno-address-of-packed-member
        -Wno-expansion-to-defined -Wno-undef -Wno-unused-private-field -Wno-deprecated-volatile)
endif()



# place functions into their own sections (for LTO)
add_compile_options(-ffunction-sections -fdata-sections -fno-common)
# disable exceptions, stack unwinding
add_compile_options(-ffreestanding -fno-exceptions -fno-unwind-tables -fno-rtti)
# no need for teardown code/destructors
add_compile_options(-fno-use-cxa-atexit)
# enable stack guards
add_compile_options(-fstack-protector-strong)

# TODO: handle this
# # note that we can only support single precision float: warn when promoting to double
# add_compile_options(-Wdouble-promotion)

###################################################################################################
if(NOT DEFINED EFWB_TARGET)
    message(FATAL_ERROR "You must specify a target for the embedded firmware base "
        "(hint: set the `EFWB_TARGET` variable in your project)")
endif()

# Include the appropriate target file
include("${CMAKE_CURRENT_LIST_DIR}/targets/${EFWB_TARGET}/target.txt")

###################################################################################################
function(add_firmware_executable TargetName Sources)

endfunction()
