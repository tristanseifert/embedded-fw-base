####################################################################################################
# RAIL DMA plugin
####################################################################################################
set(BASE        "${RAIL_BASE}/plugin/rail_util_dma")
set(LIBNAME     "efr32xg23-rail-dma")

file(GLOB SRC_FILES ${BASE}/*.c)
add_library(${LIBNAME} STATIC ${SRC_FILES})
add_library(${PROJECT_NAME}::${LIBNAME} ALIAS ${LIBNAME})

target_include_directories(${LIBNAME} PUBLIC ${BASE})
target_include_directories(${LIBNAME} PRIVATE ${EFWB_GECKO_CONFIG_DIR})

target_link_libraries(${LIBNAME} PRIVATE ${PROJECT_NAME}::efr32xg23-device-headers
    ${PROJECT_NAME}::efr32xg23-emdrv-dmadrv)
target_link_libraries(${LIBNAME} PUBLIC ${PROJECT_NAME}::efr32xg23-rail)
