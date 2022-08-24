# Embedded Firmware Base
This repo contains a set of common base libraries for writing bare-metal embedded firmware for a variety of targets.

## Supported Targets
While there's no real architectural concerns in most of the shared code provided, only the following architectures have been tested to work:

- ARM
    - Cortex-M4F: Atmel ATSAMD5x, STM32MP15x MCU core
    - Cortex-M33: Silicon Labs EFR32FG23

Support for RISC-V platforms is (eventually) planned.

### Additional Requirements
Only clang/llvm is supported to build the library code. You'll need to provide your own toolchain (and toolchain files) as well.

# Integration
To use the libraries, you need to _somehow_ add this CMake project as a dependency on your embedded firmware's project. There are several ways to go about this, the easiest being automatically fetching it with [FetchContent](https://cmake.org/cmake/help/latest/module/FetchContent.html):

```cmake
FetchContent_Declare(
    fw-base
       GIT_REPOSITORY https://github.com/tristanseifert/embedded-fw-base.git
    GIT_TAG main
)
FetchContent_MakeAvailable(fw-base)
link_libraries(embedded-fw-base::libc)
```

Once integrated, you can link with the various targets. Create a firmware image with the following command:

```cmake
add_firmware_executable(NAME firmware FILENAME "output-filename"
    LDSCRIPT ${CMAKE_CURRENT_LIST_DIR}/script.ld
    LDMAP ${CMAKE_CURRENT_BINARY_DIR}/output.map
    SOURCES
    Sources/Main.cpp
    )
```

## Configuration
Various CMake options can be set to determine how to build the library.

### Required
These options are required:

- EFWB_TARGET: Processor family to target. This automatically configures the applied HAL, libraries, etc.
    - Currently supported values are `stm32mp15x` and `efr32fg23`.

# Usage
Once the library has been configured for a particular target, you can define a new firmware image with the `add_firmware_executable` command exported by this library's build script. Its semantics are very similar to the basic [add_executable](https://cmake.org/cmake/help/latest/command/add_executable.html) command, but will configure compiler and linker options appropriately.
