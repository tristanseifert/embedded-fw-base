####################################################################################################
# Embedded Template Library
#
# Provides an STL-analog for embedded context.
####################################################################################################
option(NO_STL "" ON)

FetchContent_Declare(etl
    GIT_REPOSITORY https://github.com/ETLCPP/etl.git
    GIT_TAG 20.32.1
)
FetchContent_MakeAvailable(etl)
target_compile_options(etl INTERFACE -DETL_NO_STL -DETL_NO_CPP_NAN_SUPPORT)

add_library(${PROJECT_NAME}::etl ALIAS etl)
