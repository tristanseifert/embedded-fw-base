####################################################################################################
# RAIL callbacks plugin
####################################################################################################
set(BASE        "${RAIL_BASE}/plugin/rail_util_callbacks")
set(LIBNAME     "efr32xg23-rail-callbacks")

add_library(${LIBNAME} INTERFACE)
add_library(${PROJECT_NAME}::${LIBNAME} ALIAS ${LIBNAME})

target_include_directories(${LIBNAME} INTERFACE ${BASE})
