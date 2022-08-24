####################################################################################################
# TinyCBOR
#
# Intel's CBOR encoding library, specifically designed for embedded land.
####################################################################################################
# get code from git
FetchContent_Declare(tinycbor
    GIT_REPOSITORY https://github.com/intel/tinycbor.git
    GIT_TAG v0.6.0
)
FetchContent_MakeAvailable(tinycbor)

# create a static library
add_library(tinycbor STATIC
    ${tinycbor_SOURCE_DIR}/src/cborencoder.c
    ${tinycbor_SOURCE_DIR}/src/cborencoder_close_container_checked.c
    ${tinycbor_SOURCE_DIR}/src/cborencoder_float.c
    ${tinycbor_SOURCE_DIR}/src/cborerrorstrings.c
    ${tinycbor_SOURCE_DIR}/src/cborparser.c
    ${tinycbor_SOURCE_DIR}/src/cborparser_dup_string.c
    ${tinycbor_SOURCE_DIR}/src/cborparser_float.c
    ${tinycbor_SOURCE_DIR}/src/cborpretty.c
    #    ${tinycbor_SOURCE_DIR}/src/cborpretty_stdio.c
    #    ${tinycbor_SOURCE_DIR}/src/cbortojson.c
    ${tinycbor_SOURCE_DIR}/src/cborvalidation.c
)
add_library(${PROJECT_NAME}::tinycbor ALIAS tinycbor)

target_compile_options(tinycbor PRIVATE -Wno-implicit-fallthrough)

target_link_libraries(tinycbor PRIVATE libc)
target_include_directories(tinycbor PUBLIC ${tinycbor_SOURCE_DIR}/src)

# disable floating support, if needed
if(NOT ${EFWB_CBOR_HAS_FLOAT})
    target_compile_definitions(tinycbor PRIVATE -DCBOR_NO_FLOATING_POINT)
endif()

# work around the library not including assert.h for this definition
target_compile_definitions(tinycbor PRIVATE -Dstatic_assert=_Static_assert)
