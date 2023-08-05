####################################################################################################
# uzlib
#
# Small zlib/gzip/deflate compression and decompression library
####################################################################################################
FetchContent_Declare(uzlib
    GIT_REPOSITORY https://github.com/pfalcon/uzlib.git
    GIT_TAG v2.9.5
)
FetchContent_MakeAvailable(uzlib)

# Create target to build the library
add_library(uzlib STATIC
    ${uzlib_SOURCE_DIR}/src/tinflate.c
    ${uzlib_SOURCE_DIR}/src/tinfgzip.c
    ${uzlib_SOURCE_DIR}/src/tinfzlib.c
    ${uzlib_SOURCE_DIR}/src/adler32.c
    ${uzlib_SOURCE_DIR}/src/crc32.c
    ${uzlib_SOURCE_DIR}/src/defl_static.c
    ${uzlib_SOURCE_DIR}/src/genlz77.c
)

target_link_libraries(uzlib PRIVATE libc)
target_include_directories(uzlib PUBLIC ${uzlib_SOURCE_DIR}/src)

add_library(${PROJECT_NAME}::uzlib ALIAS uzlib)
