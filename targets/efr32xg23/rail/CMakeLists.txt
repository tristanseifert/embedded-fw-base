###################################################################################################
# RAIL radio abstraction layer
#
# This is distributed by Silicon Labs as a static library with some headers; there are also some
# additional plug-ins that can be added optionally.
#
# Currently, only the single protocol library is implemented and will be built.
###################################################################################################
set(RAIL_BASE   "${gecko_sdk_SOURCE_DIR}/platform/radio/rail_lib")

# resolve the name of the library (based on hardware type)
if(${EFWB_GECKO_DEVICE_CLASS} STREQUAL "EFR32xG23")
    set(RAIL_LIB_NAME "librail_efr32xg23_gcc_release.a")
else()
    message(FATAL_ERROR "Don't know RAIL binary for device `${EFWB_GECKO_DEVICE}`")
endif()

# base library (provided as a pre-built static library)
add_library(efr32xg23-rail INTERFACE)
add_library(${PROJECT_NAME}::efr32xg23-rail ALIAS efr32xg23-rail)

target_include_directories(efr32xg23-rail INTERFACE ${RAIL_BASE}/protocol/ble)
target_include_directories(efr32xg23-rail INTERFACE ${RAIL_BASE}/protocol/ieee802154)
target_include_directories(efr32xg23-rail INTERFACE ${RAIL_BASE}/protocol/zwave)
target_include_directories(efr32xg23-rail INTERFACE ${RAIL_BASE}/common)
target_link_libraries(efr32xg23-rail INTERFACE "${RAIL_BASE}/autogen/librail_release/${RAIL_LIB_NAME}")
target_link_libraries(efr32xg23-rail INTERFACE ${PROJECT_NAME}::efr32xg23-emlib)

# base library chip specific headers
if(${EFWB_GECKO_DEVICE_CLASS} STREQUAL "EFR32xG23")
    target_include_directories(efr32xg23-rail INTERFACE ${RAIL_BASE}/chip/efr32/efr32xg2x)
endif()

# build plugins
add_subdirectory(${CMAKE_CURRENT_LIST_DIR}/plugins EXCLUDE_FROM_ALL)

# then include a subset of them as default with RAIL
target_link_libraries(efr32xg23-rail INTERFACE ${PROJECT_NAME}::efr32xg23-rail-dma
    ${PROJECT_NAME}::efr32xg23-rail-pa ${PROJECT_NAME}::efr32xg23-rail-rfpath
    ${PROJECT_NAME}::efr32xg23-rail-callbacks ${PROJECT_NAME}::efr32xg23-rail-rssi
    ${PROJECT_NAME}::efr32xg23-rail-protocol)
