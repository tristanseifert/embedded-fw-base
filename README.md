# Embedded Firmware Base
This repo contains a set of common base libraries for writing bare-metal embedded firmware for a variety of targets.

## Supported Targets
While there's no real architectural concerns in most of the shared code provided, only the following architectures have been tested to work:

- ARM
    - Cortex-M4F: Atmel ATSAMD5x, STM32MP15x MCU core
    - Cortex-M33: Silicon Labs EFR32FG23

Support for RISC-V platforms is (eventually) planned.

# Integration
To use the libraries, you need to _somehow_ add this CMake project as a dependency on your embedded firmware's project. There are several ways to go about this, the easiest being automatically fetching it with [FetchContent](https://cmake.org/cmake/help/latest/module/FetchContent.html):

```cmake
# TODO: Add the example
```

Once integrated, you can link with the various targets:

** TODO: list of targets here **

## Configuration
Various CMake options can be set to determine how to build the library.

### Required
These options are required:

- EFWB_VENDOR_HAL: Which vendor's HAL/drivers should be built alongside the library?
    - Currently supported values are `stm32mp15x` and `efr32fg23`
