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

list(APPEND EFWB_TARGET_COMPILE_OPTS -Wall -Wmissing-declarations -Wformat=2
    -fdiagnostics-color=always -ftls-model=initial-exec -Wundef -Wcast-qual -Wwrite-strings)

if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
    list(APPEND EFWB_TARGET_COMPILE_OPTS -Wimplicit-fallthrough -Wno-deprecated-copy
        -Wno-address-of-packed-member -Wno-expansion-to-defined -Wno-undef
        -Wno-unused-private-field -Wno-deprecated-volatile)
endif()

# place functions into their own sections (for LTO)
list(APPEND EFWB_TARGET_COMPILE_OPTS -ffunction-sections -fdata-sections -fno-common)
# disable exceptions, stack unwinding
list(APPEND EFWB_TARGET_COMPILE_OPTS -ffreestanding -fno-exceptions -fno-unwind-tables -fno-rtti)
# no need for teardown code/destructors
list(APPEND EFWB_TARGET_COMPILE_OPTS -fno-use-cxa-atexit)
# enable stack guards
list(APPEND EFWB_TARGET_COMPILE_OPTS -fstack-protector-strong)

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

# apply the default compile options to all libraries
add_compile_options(${EFWB_TARGET_COMPILE_OPTS})

add_subdirectory(${CMAKE_CURRENT_LIST_DIR}/libs EXCLUDE_FROM_ALL)

###################################################################################################
# Save the compile options and target libraries that have so far been modified (by the target
# files) into a global variable. This wayu the add_firmware_executable function can locate them
# correctly.
set_property(GLOBAL PROPERTY EFWB_GLOBAL_LIBS "${EFWB_TARGET_LIBS}")
set_property(GLOBAL PROPERTY EFWB_GLOBAL_COMPILE_OPTS "${EFWB_TARGET_COMPILE_OPTS}")
set_property(GLOBAL PROPERTY EFWB_GLOBAL_COMPILE_DEFS "${EFWB_TARGET_COMPILE_DEFS}")

###################################################################################################
find_program(CMAKE_SIZE size)

# Define the wrapper to create a firmware image
#
# Arguments can be:
#
# - NAME: Name of the target, mandatory
# - FILENAME: Filename component (sans extension) for the built image
# - SOURCES: Source files to compile
#
# This is functionally identical to `add_executable` but has some shinies to make firmware type
# stuff (linker scripts, compile arguments, required libraries) easier.
#
# This ensures the C library, as well as a few other platform and target specific nicities are
# included. For C++ projects, the Embedded Template Library (ETL) will also be included
# automatically.
function(add_firmware_executable)
    # parse arguments
    cmake_parse_arguments(ADD_FWEXE "" "NAME;FILENAME;LDSCRIPT;LDMAP" "SOURCES" ${ARGN})

    if(NOT DEFINED ADD_FWEXE_SOURCES)
        message(FATAL_ERROR "specify sources for add_firmware_executable")
    endif()

    # fetch variables
    get_property(EFWB_TARGET_LIBS GLOBAL PROPERTY EFWB_GLOBAL_LIBS)
    get_property(EFWB_TARGET_COMPILE_OPTS GLOBAL PROPERTY EFWB_GLOBAL_COMPILE_OPTS)
    get_property(EFWB_TARGET_COMPILE_DEFS GLOBAL PROPERTY EFWB_GLOBAL_COMPILE_DEFS)

    # create the target
    add_executable(${ADD_FWEXE_NAME} ${ADD_FWEXE_SOURCES})

    # configure it to build a static image
    target_compile_options(${ADD_FWEXE_NAME} PUBLIC -ffreestanding -fno-exceptions
        -fno-unwind-tables -fno-rtti -fno-use-cxa-atexit -fstack-protector-strong)
    target_compile_options(${ADD_FWEXE_NAME} PUBLIC -flto ${EFWB_TARGET_COMPILE_OPTS})
    target_link_options(${ADD_FWEXE_NAME} PUBLIC --static -nostartfiles -nostdlib -ffreestanding
        -flto)

    # link required libraries
    target_link_libraries(${ADD_FWEXE_NAME} PUBLIC embedded-fw-base::libc embedded-fw-base::etl
        embedded-fw-base::util)
    target_link_libraries(${ADD_FWEXE_NAME} PUBLIC ${EFWB_TARGET_LIBS})
    target_compile_definitions(${ADD_FWEXE_NAME} PUBLIC ${EFWB_TARGET_COMPILE_DEFS})

    # specify output image name
    if(DEFINED ADD_FWEXE_FILENAME)
        set_target_properties(${ADD_FWEXE_NAME} PROPERTIES OUTPUT_NAME ${ADD_FWEXE_FILENAME})
        set_target_properties(${ADD_FWEXE_NAME} PROPERTIES SUFFIX ".elf")
    endif()

    # specify linker script and map output
    if(DEFINED ADD_FWEXE_LDSCRIPT)
        set_target_properties(firmware PROPERTIES LINK_DEPENDS ${ADD_FWEXE_LDSCRIPT})

        if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
            target_link_options(firmware PRIVATE "-Wl,-T${ADD_FWEXE_LDSCRIPT}")
        else()
            message(FATAL_ERROR "don't know how to set linker script for compiler '${CMAKE_CXX_COMPILER_ID}'")
        endif()
    else()
        message(FATAL_ERROR "Platform linker script not yet supported!")
    endif()

    if(DEFINED ADD_FWEXE_LDMAP)
        if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
            target_link_options(firmware PRIVATE "-Wl,-Map,${ADD_FWEXE_LDMAP}")
        else()
            message(AUTHOR_WARNING "don't know how to enable linker map for compiler '${CMAKE_CXX_COMPILER_ID}'")
        endif()
    endif()

    # print the size of the image once compiled
    add_custom_command(TARGET ${ADD_FWEXE_NAME} POST_BUILD
        COMMAND ${CMAKE_SIZE} $<TARGET_FILE:firmware>
    )
endfunction()
