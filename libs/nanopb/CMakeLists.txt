####################################################################################################
# A portable, low resource implementation of Google Protocol Buffers
####################################################################################################
# get code from git
FetchContent_Declare(nanopb
    GIT_REPOSITORY https://github.com/nanopb/nanopb.git
    GIT_TAG nanopb-0.4.7
)
FetchContent_MakeAvailable(nanopb)

# target_link_libraries(protobuf-nanopb-static PRIVATE libc)
target_include_directories(protobuf-nanopb-static PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/../libc/Includes)

add_library(${PROJECT_NAME}::nanopb ALIAS protobuf-nanopb-static)

# export the path to the generator script
set(EFWB_NANOPB_GENERATOR ${nanopb_SOURCE_DIR}/generator/nanopb_generator.py)
