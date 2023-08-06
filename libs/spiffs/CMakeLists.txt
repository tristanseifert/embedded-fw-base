####################################################################################################
# SPIFFS
####################################################################################################
set(LIBNAME     "spiffs")

# validate options
if(NOT DEFINED EFWB_SPIFFS_CONFIG_DIR)
    message(FATAL_ERROR "You must specify a SPIFFS config directory: `EFWB_SPIFFS_CONFIG_DIR`")
endif()

# fetch sources
FetchContent_Declare(spiffs
    GIT_REPOSITORY https://github.com/pellepl/spiffs.git
    # main branch
    GIT_TAG 0dbb3f7
)
FetchContent_MakeAvailable(spiffs)

# create library
add_library(${LIBNAME} STATIC
    ${spiffs_SOURCE_DIR}/src/spiffs_cache.c
    ${spiffs_SOURCE_DIR}/src/spiffs_check.c
    ${spiffs_SOURCE_DIR}/src/spiffs_gc.c
    ${spiffs_SOURCE_DIR}/src/spiffs_hydrogen.c
    ${spiffs_SOURCE_DIR}/src/spiffs_nucleus.c
)
add_library(${PROJECT_NAME}::${LIBNAME} ALIAS ${LIBNAME})

target_include_directories(${LIBNAME} PUBLIC ${EFWB_SPIFFS_CONFIG_DIR})
target_include_directories(${LIBNAME} PUBLIC ${spiffs_SOURCE_DIR}/src)

target_link_libraries(${LIBNAME} PUBLIC ${PROJECT_NAME}::libc)

# silence some warnings
# target_compile_options(${LIBNAME} PRIVATE -Wno-cast-qual -Wno-parentheses-equality)
