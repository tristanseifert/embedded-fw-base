####################################################################################################
# ARM CMSIS and various bonus libraries provided by it
#
# It provides several libraries:
#
# - cmsis: Base CMSIS library, required for ARM targets
# - cmsis-dsp: DSP and math routines optimized for ARM (used for C math functions)
####################################################################################################

####################################################################################################
# CMSIS 5
FetchContent_Declare(cmsis_5
    GIT_REPOSITORY https://github.com/ARM-software/CMSIS_5.git
    GIT_TAG 5.9.0
)
FetchContent_MakeAvailable(cmsis_5)

set(CMSIS_INCLUDE_DIR ${cmsis_5_SOURCE_DIR}/CMSIS/Core/Include)

# let everything we compile pull in the CMSIS headers
include_directories(${CMSIS_INCLUDE_DIR})

add_library(cmsis INTERFACE)
target_include_directories(cmsis INTERFACE ${CMSIS_INCLUDE_DIR})

add_library(${PROJECT_NAME}::cmsis ALIAS cmsis)

####################################################################################################
# CMSIS DSP
#
# This is primarily used for some fast math functions, which the C library then re-exports as
# builtin C library functions.
set(ROOT ${cmsis_5_SOURCE_DIR})
set(DSP ${cmsis_5_SOURCE_DIR}/CMSIS/DSP)

# hack to get cmake step to work
function(compilerSpecificCompileOptions PROJECTNAME ROOT)
endfunction()

# disable a lot of code
set(DISABLEFLOAT16 ON CACHE INTERNAL "" FORCE)
set(COMPLEXMATH OFF CACHE INTERNAL "" FORCE)
set(CONTROLLER OFF CACHE INTERNAL "" FORCE)
set(FILTERING OFF CACHE INTERNAL "" FORCE)
set(MATRIX OFF CACHE INTERNAL "" FORCE)
set(TRANSFORM OFF CACHE INTERNAL "" FORCE)
set(SVM OFF CACHE INTERNAL "" FORCE)
set(BAYES OFF CACHE INTERNAL "" FORCE)
set(DISTANCE OFF CACHE INTERNAL "" FORCE)
set(INTERPOLATION OFF CACHE INTERNAL "" FORCE)
set(QUATERNIONMATH OFF CACHE INTERNAL "" FORCE)

list(APPEND CMAKE_MODULE_PATH ${DSP})

# this is a disgusting hack, we should figure out how to change it out
add_compile_options(-Wno-error -Wno-cast-qual)
include_directories(${CMAKE_CURRENT_LIST_DIR}/../libc/Includes)

add_subdirectory(${DSP}/Source bin_dsp EXCLUDE_FROM_ALL)

target_link_libraries(libc PRIVATE CMSISDSP)
add_library(${PROJECT_NAME}::cmsis-dsp ALIAS CMSISDSP)
