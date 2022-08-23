###################################################################################################
# Libraries independent of architecture/platform we'll run on

###############
# Internal C library
add_subdirectory(${CMAKE_CURRENT_LIST_DIR}/libc)

###############
# Embedded template library
option(NO_STL "" ON)

FetchContent_Declare(etl
    GIT_REPOSITORY https://github.com/ETLCPP/etl.git
    GIT_TAG 20.32.1
)
FetchContent_MakeAvailable(etl)
target_compile_options(etl INTERFACE -DETL_NO_STL -DETL_NO_CPP_NAN_SUPPORT)

add_library(${PROJECT_NAME}::etl ALIAS etl)

###############
# printf
set(BUILD_STATIC_LIBRARY "" ON)
set(SUPPORT_WRITEBACK_SPECIFIER "" OFF)

set(SUPPORT_DECIMAL_SPECIFIERS "" OFF)
set(SUPPORT_EXPONENTIAL_SPECIFIERS "" OFF)

FetchContent_Declare(printf_library
    GIT_REPOSITORY https://github.com/eyalroz/printf.git
    GIT_TAG v6.0.0
)
FetchContent_MakeAvailable(printf_library)

target_compile_options(printf PRIVATE -Wno-implicit-int-float-conversion)

# TODO: integrate these flags into libc for consuming printf
#target_link_libraries(firmware PRIVATE printf)
#target_compile_definitions(firmware PUBLIC -DPRINTF_ALIAS_STANDARD_FUNCTION_NAMES=1)

###################################################################################################
# Architecture-dependent libraries

###################################################################################################
# Platform-dependent libraries will be defined by the platform code itself, so we have nothing
# more to do here.
