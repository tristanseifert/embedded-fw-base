####################################################################################################
# Peripheral driver library for EFM32, EZR32 and EFR32 series microcontrollers
#
# TODO: Move this to a common library, if we ever want to support targets other than the
# EFR32xG23 series.
####################################################################################################

# shared, support for drivers
add_subdirectory(${CMAKE_CURRENT_LIST_DIR}/common EXCLUDE_FROM_ALL)

# driver implementations
add_subdirectory(${CMAKE_CURRENT_LIST_DIR}/dmadrv EXCLUDE_FROM_ALL)
add_subdirectory(${CMAKE_CURRENT_LIST_DIR}/gpiointerrupt EXCLUDE_FROM_ALL)
add_subdirectory(${CMAKE_CURRENT_LIST_DIR}/spidrv EXCLUDE_FROM_ALL)
add_subdirectory(${CMAKE_CURRENT_LIST_DIR}/tempdrv EXCLUDE_FROM_ALL)
add_subdirectory(${CMAKE_CURRENT_LIST_DIR}/uartdrv EXCLUDE_FROM_ALL)
