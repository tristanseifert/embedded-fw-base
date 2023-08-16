####################################################################################################
# A shitty imitation "C library" to get a lot of common stuff covered. Most of the code for this
# is straight up copied from OpenBSD's libc.
####################################################################################################
add_library(libc STATIC
    Sources/stdlib/abort.cpp
    Sources/stdlib/atoi.c

    Sources/ctype/isalnum.c
    Sources/ctype/isalpha.c
    Sources/ctype/isascii.c
    Sources/ctype/isblank.c
    Sources/ctype/iscntrl.c
    Sources/ctype/isdigit.c
    Sources/ctype/isgraph.c
    Sources/ctype/islower.c
    Sources/ctype/isprint.c
    Sources/ctype/ispunct.c
    Sources/ctype/isspace.c
    Sources/ctype/isupper.c
    Sources/ctype/isxdigit.c
    Sources/ctype/toascii.c
    Sources/ctype/tolower.c
    Sources/ctype/toupper.c

    Sources/string/memchr.c
    Sources/string/memcmp.c
    Sources/string/memcpy.c
    Sources/string/memmove.c
    Sources/string/memset.c

    Sources/string/strcmp.c
    Sources/string/strncpy.c
    Sources/string/strncmp.c
    Sources/string/strcpy.c
    Sources/string/strcspn.c
    Sources/string/strlen.c
    Sources/string/strspn.c
    Sources/string/strcasecmp.c

    Sources/aeabi/aeabi_memcpy.c
    Sources/aeabi/aeabi_memcpy.S

    Sources/malloc/init.c
    Sources/malloc/malloc_api.c

    Sources/math/trig.c
    Sources/math/logf.c

    Sources/runtime/init.c
)
set_target_properties(libc PROPERTIES OUTPUT_NAME "c")

add_library(${PROJECT_NAME}::libc ALIAS libc)

target_include_directories(libc PUBLIC ${CMAKE_CURRENT_LIST_DIR}/Includes)

#########################
# fetch umm_malloc, used as a heap implementation
FetchContent_Declare(umm_malloc
    GIT_REPOSITORY https://github.com/rhempel/umm_malloc.git
    GIT_TAG v1.1.2
)
FetchContent_MakeAvailable(umm_malloc)

add_library(umm_malloc STATIC
    ${umm_malloc_SOURCE_DIR}/src/umm_info.c
    ${umm_malloc_SOURCE_DIR}/src/umm_integrity.c
    ${umm_malloc_SOURCE_DIR}/src/umm_malloc.c
    ${umm_malloc_SOURCE_DIR}/src/umm_poison.c
)

target_include_directories(umm_malloc PUBLIC ${umm_malloc_SOURCE_DIR}/src)
target_include_directories(umm_malloc PRIVATE ${CMAKE_CURRENT_LIST_DIR}/Includes)
target_include_directories(umm_malloc PRIVATE ${CMAKE_CURRENT_LIST_DIR}/Sources/malloc)

target_link_libraries(libc PRIVATE umm_malloc)

#########################
# fetch printf, which becomes integrated into libc
set(BUILD_STATIC_LIBRARY "" ON)
set(SUPPORT_WRITEBACK_SPECIFIER "" OFF)
set(ALIAS_STANDARD_FUNCTION_NAMES_HARD "" ON)
set(SUPPORT_DECIMAL_SPECIFIERS "" OFF)
set(SUPPORT_EXPONENTIAL_SPECIFIERS "" OFF)

FetchContent_Declare(printf_library
    GIT_REPOSITORY https://github.com/eyalroz/printf.git
    GIT_TAG v6.1.0
)
FetchContent_MakeAvailable(printf_library)

if(${EFWB_PRINTF_CONFIG_DIR})
    target_include_directories(printf_library PUBLIC ${EFWB_PRINTF_CONFIG_DIR})
endif()

target_compile_definitions(printf PRIVATE -DPRINTF_INCLUDE_CONFIG_H -DPRINTF_ALIAS_STANDARD_FUNCTION_NAMES)
target_compile_definitions(printf PUBLIC -DPRINTF_ALIAS_STANDARD_FUNCTION_NAMES_HARD)
target_compile_options(printf PRIVATE -Wno-implicit-int-float-conversion)
add_library(${PROJECT_NAME}::printf ALIAS printf)

# printf becomes a part of libc
target_link_libraries(libc PUBLIC ${PROJECT_NAME}::printf)
target_compile_definitions(libc PUBLIC -DPRINTF_ALIAS_STANDARD_FUNCTION_NAMES=1)
