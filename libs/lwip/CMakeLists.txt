####################################################################################################
# LwIP Network Stack
#
# This takes advantage of the provided file lists to build static libraries of all the
# parts of the stack.
####################################################################################################
FetchContent_Declare(lwip
    GIT_REPOSITORY https://git.savannah.nongnu.org/git/lwip.git
    GIT_TAG STABLE-2_2_0_RC1
)
FetchContent_Populate(lwip)

# TODO: warning if EFWB_LWIP_CONFIG_DIR is empty

# include the file lists
set(LWIP_DIR ${lwip_SOURCE_DIR})
set(LWIP_CONTRIB_DIR ${lwip_SOURCE_DIR}/contrib)

set(LWIP_INCLUDE_DIRS
    "${LWIP_DIR}/src/include"
    "${LWIP_DIR}/contrib"
    "${LWIP_DIR}/contrib/ports/freertos/include"
    "${EFWB_LWIP_CONFIG_DIR}"
    "${CMAKE_CURRENT_LIST_DIR}/Includes"
)

# include file lists now
# FetchContent_MakeAvailable(lwip)
include(${LWIP_DIR}/src/Filelists.cmake)
include(${LWIP_CONTRIB_DIR}/Filelists.cmake)

# create target for base library
add_library(${PROJECT_NAME}::lwipcore ALIAS lwipcore)
target_link_libraries(lwipcore PUBLIC libc printf)

add_library(${PROJECT_NAME}::lwipallapps ALIAS lwipallapps)
target_link_libraries(lwipallapps PUBLIC libc printf)

# create a wrapper (including FreeRTOS platform glue)
add_library(lwip STATIC
    ${LWIP_CONTRIB_DIR}/ports/freertos/sys_arch.c
)
target_link_libraries(lwip PUBLIC ${PROJECT_NAME}::lwipcore ${PROJECT_NAME}::lwipallapps)
target_link_libraries(lwip PUBLIC ${PROJECT_NAME}::FreeRTOS)
target_include_directories(lwip PUBLIC ${LWIP_INCLUDE_DIRS})

# smtp uses strcpy() and doesn't compile cleanly, so ignore it
set_source_files_properties(${LWIP_DIR}/src/apps/smtp/smtp.c PROPERTIES HEADER_FILE_ONLY ON)

add_library(${PROJECT_NAME}::lwip ALIAS lwip)
