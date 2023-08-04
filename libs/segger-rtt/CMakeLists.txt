####################################################################################################
# Segger RTT runtime support library
#
# This provides the interface to the Segger RTT interface to create virtual "channels"
# to/from the host.
####################################################################################################
add_library(segger-rtt STATIC
    Sources/SEGGER_RTT.c
    Sources/SEGGER_RTT_ASM_ARMv7M.S
)

add_library(${PROJECT_NAME}::segger-rtt ALIAS segger-rtt)
target_include_directories(segger-rtt PUBLIC ${CMAKE_CURRENT_LIST_DIR}/Includes)
target_link_libraries(segger-rtt PUBLIC libc)

target_compile_options(segger-rtt PRIVATE -Wno-cast-qual)

# directory containing the RTT config file
if("${EFWB_SEGGER_RTT_CONFIG_DIR}" STREQUAL "")
    target_include_directories(segger-rtt PUBLIC ${CMAKE_CURRENT_LIST_DIR}/DefaultConfig)
else()
    target_include_directories(segger-rtt PUBLIC ${EFWB_SEGGER_RTT_CONFIG_DIR})
endif()
