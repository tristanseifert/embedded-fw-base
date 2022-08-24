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

###################################################################################################
# Include the appropriate target configuration file
if(NOT DEFINED EFWB_TARGET)
    message(FATAL_ERROR "You must specify a target for the embedded firmware base "
        "(hint: set the `EFWB_TARGET` variable in your project)")
endif()

string(TOLOWER ${EFWB_TARGET} EFWB_TARGET)
include("${CMAKE_CURRENT_LIST_DIR}/targets/${EFWB_TARGET}/target.txt"
    RESULT_VARIABLE TARGET_CONF_PATH)

if(${TARGET_CONF_PATH} STREQUAL "NOTFOUND")
    message(FATAL_ERROR "Unknown embedded firmware target `${EFWB_TARGET}`")
endif()

###################################################################################################
# Pull in definitions for all of our libraries.
#
# These will be consumed either directly by the project integrating us, indirectly by one of the
# internal libraries, or as part of the magic in `add_firmware_executable` for platform support.
#
# Since some of these aren't necessary for all cases, save the trouble of building them all.
add_subdirectory(${CMAKE_CURRENT_LIST_DIR}/libs EXCLUDE_FROM_ALL)

###################################################################################################
find_program(CMAKE_SIZE size)

# Define the wrapper to create a firmware image
#
# This is functionally identical to `add_executable` but has some shinies to make firmware type
# stuff (linker scripts, compile arguments, required libraries) easier.
function(add_firmware_executable TargetName Sources)
    # print the size of the image once compiled
    add_custom_command(TARGET ${ARGV0} POST_BUILD
        COMMAND ${CMAKE_SIZE} $<TARGET_FILE:firmware>
    )
endfunction()
