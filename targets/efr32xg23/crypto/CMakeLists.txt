###################################################################################################
# Crypto library targets
#
# Imports the various cryptography-related libraries.
###################################################################################################

# low level drivers
add_subdirectory(${CMAKE_CURRENT_LIST_DIR}/se-manager EXCLUDE_FROM_ALL)

# high level APIs
# TODO: mbed TLS
# TODO: security engine PSA driver
