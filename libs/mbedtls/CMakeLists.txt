####################################################################################################
# mbedTLS
####################################################################################################
set(MBEDTLS_AS_SUBPROJECT ON)
set(ENABLE_TESTING OFF)
set(ENABLE_PROGRAMS OFF)
set(USE_STATIC_MBEDTLS_LIBRARY ON)

link_libraries(libc printf)

# specify config path
add_compile_options(-DMBEDTLS_CONFIG_FILE="${EFWB_MBEDTLS_CONFIG_FILE}" -Wno-documentation
    -Wno-cast-qual)

# include library
FetchContent_Declare(mbedTLS
    GIT_REPOSITORY https://github.com/Mbed-TLS/mbedtls.git
    GIT_TAG v3.4.1
)
FetchContent_MakeAvailable(mbedTLS)
