###################################################################################################
# Utility library
###################################################################################################
set(LIBNAME     "util")

add_library(${LIBNAME} STATIC
    Sources/Hash.cpp
)
add_library(${PROJECT_NAME}::${LIBNAME} ALIAS ${LIBNAME})

target_include_directories(${LIBNAME} PRIVATE Sources)
target_include_directories(${LIBNAME} PUBLIC Includes)

target_link_libraries(${LIBNAME} PUBLIC ${PROJECT_NAME}::libc ${PROJECT_NAME}::etl)
