####################################################################################################
# Common driver code
####################################################################################################
set(BASE "${gecko_sdk_SOURCE_DIR}/platform/emdrv/common")

add_library(efr32xg23-emdrv-common INTERFACE)
add_library(${PROJECT_NAME}::efr32xg23-emdrv-common ALIAS efr32xg23-emdrv-common)

target_include_directories(efr32xg23-emdrv-common INTERFACE ${BASE}/inc)
